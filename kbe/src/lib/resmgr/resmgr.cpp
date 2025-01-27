// Copyright 2008-2018 Yolo Technologies, Inc. All Rights Reserved. https://www.comblockengine.com
// Refactored: 2021.04.01
// Refactored by: CasinoHe
// Purpose: Manager all resource paths, redesign res manager by c++ 11/14/17 features

#include "resmgr.h"
#include "helper/watcher.h"
#include "helper/debug_helper.h"
#include "thread/threadguard.h"

#include <map>

namespace smallgames
{
	PathMgr &GetPathMgr()
	{
		static PathMgr &g_pathmgr = PathMgr::getSingleton();
		return g_pathmgr;
	}

	namespace fs = std::filesystem;

	PathMgr::PathMgr() : smg_paths_{}, is_inited_{false}
	{
	}

	void PathMgr::singleton_init()
	{
		set_default_paths();
		set_env_paths();

		is_inited_ = true;
	}

	void PathMgr::set_env_paths()
	{
		// get environment paths
		fs::path root_path{getenv(ROOT_PATH_VAR) == NULL ? "" : getenv(ROOT_PATH_VAR)};
		fs::path bin_path{getenv(BIN_PATH_VAR) == NULL ? "" : getenv(BIN_PATH_VAR)};
		fs::path script_path{getenv(SCRIPT_PATH_VAR) == NULL ? "" : getenv(SCRIPT_PATH_VAR)};
		std::string res_path_str{getenv(RES_PATH_VAR) == NULL ? "" : getenv(RES_PATH_VAR)};

		if (!root_path.empty())
		{
			smg_paths_.root_path = fs::absolute(root_path);
		}

		if (!bin_path.empty())
		{
			smg_paths_.bin_path = fs::absolute(bin_path);
		}

		if (!script_path.empty())
		{
			smg_paths_.script_path = fs::absolute(script_path);
		}

		// parse all res path
		if (!res_path_str.empty())
		{
			smg_paths_.res_paths.clear();

			std::string res_path{""};
			for (auto &item : res_path_str)
			{
				if (item != ';')
				{
					res_path += item;
				}
				else
				{
					fs::path abs_path{res_path};
					smg_paths_.res_paths.push_back(fs::absolute(abs_path));
					res_path.clear();
				}
			}
		}

		print("Set environemtn variable defined paths:");
	}

	void PathMgr::set_default_paths()
	{
		fs::path cwd = fs::current_path();

		smg_paths_.root_path = cwd;
		smg_paths_.bin_path = cwd / PathMgr::DEFAULT_BIN_PATH;
		smg_paths_.script_path = cwd / PathMgr::DEFAULT_SCRIPT_PATH;

		smg_paths_.res_paths.push_back(cwd / PathMgr::DEFAULT_RES_PATH);

		print("Set default paths:");
	}

	void PathMgr::print(const char *extra_msg)
	{
		if (extra_msg)
		{
			KBEngine::INFO_MSG(fmt::format("{}\n", extra_msg));
		}
		KBEngine::INFO_MSG(fmt::format("Root path {}\n", smg_paths_.root_path.c_str()));
		KBEngine::INFO_MSG(fmt::format("Bin path {}\n", smg_paths_.bin_path.c_str()));
		KBEngine::INFO_MSG("Res path: ");

		for (auto &path : smg_paths_.res_paths)
		{
			KBEngine::INFO_MSG(fmt::format("{};", path.c_str()));
		}
		KBEngine::INFO_MSG("\n");
	}

	// return the full path
	// if not exists, return the parameter
	std::string PathMgr::get_full_path(const std::initializer_list<std::string> path_nodes)
	{
		// join the path node, if exists, get the full path
		fs::path res_path("");
		for (auto &item : path_nodes)
		{
			res_path /= item;
		}

		return get_full_path(res_path);
	}

	std::string PathMgr::get_full_path(const std::string &path)
	{
		for (auto &res_dir : smg_paths_.res_paths)
		{
			fs::path fpath = res_dir / path;

			if (fs::exists(fpath))
			{
				return fpath.c_str();
			}
		}

		return path;
	}

	bool PathMgr::exists(const std::initializer_list<std::string> path_nodes)
	{
		// join the path node, if exists, return true
		fs::path res_path("");
		for (auto &item : path_nodes)
		{
			res_path /= item;
		}

		return exists(res_path);
	}

	bool PathMgr::exists(const std::string &path)
	{
		for (auto &res_dir : smg_paths_.res_paths)
		{
			fs::path fpath = res_dir / path;

			if (fs::exists(fpath))
			{
				return true;
			}
		}

		return false;
	}

	bool PathMgr::list_res(const std::string &path, const std::string &extensions, std::vector<std::string> &results)
	{
		if (path.empty())
		{
			KBEngine::ERROR_MSG("PathMgr: open dir [NULL] error!\n");
			return false;
		}

		std::vector<std::string> extend_names;
		if (extensions.size() <= 0 || extensions == "*" || extensions == ".")
		{
			extend_names.emplace_back("*");
		}
		else
		{
			KBEngine::strutil::kbe_split<char>(extensions, '|', extend_names);
		}

		fs::path dir_path(get_full_path(path));

		return walk_path(dir_path, extend_names, results);
	}

	bool PathMgr::walk_path(const std::filesystem::path &path, const std::vector<std::string> &extensions, std::vector<std::string> &results)
	{
		for (const auto &entry : fs::directory_iterator(path))
		{
			if (entry.is_directory())
			{
				walk_path(entry.path(), extensions, results);
			}
			else if (entry.is_regular_file())
			{
				if (extensions.size() == 1 && extensions[0] == "*")
				{
					results.emplace_back(entry.path().c_str());
				}
				else
				{
					for (auto &ext : extensions)
					{
						std::string file_ext(entry.path().extension().c_str());
						if (ext.compare(file_ext) == 0)
						{
							results.emplace_back(entry.path().c_str());
						}
					}
				}
			}
		}
		return true;
	}

	std::string PathMgr::get_file_content(const std::initializer_list<std::string> path_notes)
	{
		std::string path = get_full_path(path_notes);
		if (!path.empty())
		{
			return get_file_content(path);
		}
		else
		{
			return {};
		}
	}

	std::string PathMgr::get_file_content(const std::string &file_path)
	{
		if (!fs::exists(file_path) || !fs::is_regular_file(file_path))
		{
			KBEngine::ERROR_MSG(fmt::format("Cannot open file: {}", file_path.c_str()));
			return {};
		}

		std::ifstream ifs;
		ifs.open(file_path, std::ios::in);
		if (ifs.is_open())
		{
			ifs.seekg(0, std::ios::end);
			uint64_t file_size = ifs.tellg();
			ifs.seekg(0, std::ios::beg);

			std::vector<char> buffer(file_size);
			ifs.read(&buffer[0], file_size);
			ifs.close();
			return {buffer.cbegin(), buffer.cend()};
		}
		else
		{
			return {};
		}
	}

	const std::string PathMgr::get_res_path()
	{
		if (smg_paths_.res_paths.empty())
		{
			return {};
		}

		return smg_paths_.res_paths[0];
	}

	const std::string PathMgr::get_script_path()
	{
		return smg_paths_.script_path;
	}

	const std::string PathMgr::get_component_script_path(KBEngine::COMPONENT_TYPE component_type)
	{
		std::map<KBEngine::COMPONENT_TYPE, std::string> type_2_path{
			{KBEngine::CELLAPP_TYPE, "cell"},
			{KBEngine::BASEAPP_TYPE, "base"},
			{KBEngine::BOTS_TYPE, "bots"},
			{KBEngine::CLIENT_TYPE, "client"},
		};

		fs::path script_temp_path{""};
		fs::path *path = nullptr;

		if (component_type == KBEngine::g_componentType)
		{
			static fs::path script_path;
			path = &script_path;
		}
		else
		{
			path = &script_temp_path;
		}

		if (!path->empty())
		{
			return path->c_str();
		}
		else
		{
			*path = get_script_path();

			auto iter = type_2_path.find(component_type);
			if (iter != type_2_path.end())
			{
				*path = *path / iter->second;
			}
		}

		return path->c_str();
	}

	//-------------------------------------------------------------------------------------
	Resmgr::Resmgr() : is_inited_(false),
										 respool_(),
										 mutex_()
	{
	}

	//-------------------------------------------------------------------------------------
	Resmgr::~Resmgr()
	{
		respool_.clear();
	}

	//-------------------------------------------------------------------------------------
	bool Resmgr::initialize_watcher()
	{
		// WATCH_OBJECT("syspaths/KBE_ROOT", kb_env_.root_path);
		// WATCH_OBJECT("syspaths/KBE_RES_PATH", kb_env_.res_path);
		// WATCH_OBJECT("syspaths/KBE_BIN_PATH", kb_env_.bin_path);
		return true;
	}

	//-------------------------------------------------------------------------------------
	void Resmgr::singleton_init()
	{
		respool_.clear();
		is_inited_ = true;
	}

	//-------------------------------------------------------------------------------------
	KBEngine::ResourceObjectPtr Resmgr::open_resource(std::initializer_list<std::string> path_list, std::ios::openmode mode, std::uint32_t flags)
	{
		if (!GetPathMgr().exists(path_list))
		{
			KBEngine::ERROR_MSG(fmt::format("Cannot find resource file: {}", GetPathMgr().get_full_path(path_list)));
			return {};
		}

		std::string full_path = GetPathMgr().get_full_path(path_list);

		return open_resource(full_path, mode, flags);
	}

	KBEngine::ResourceObjectPtr Resmgr::open_resource(const std::string &full_path, std::ios::openmode mode, std::uint32_t flags)
	{
		if (Resmgr::respool_checktick == 0)
		{
			return new KBEngine::FileObject(full_path.c_str(), flags, "rb");
		}

		std::lock_guard lock(mutex_);
		std::unordered_map<std::string, KBEngine::ResourceObjectPtr>::iterator iter = respool_.find(full_path);
		if (iter == respool_.end())
		{
			KBEngine::FileObject *fobj = new KBEngine::FileObject(full_path.c_str(), flags, "r");
			respool_[full_path] = fobj;
			fobj->update();
			return fobj;
		}

		iter->second->update();
		return iter->second;
	}

	//-------------------------------------------------------------------------------------
	void Resmgr::update()
	{
		std::lock_guard lock(mutex_);
		std::unordered_map<std::string, KBEngine::ResourceObjectPtr>::iterator iter = respool_.begin();
		for (; iter != respool_.end();)
		{
			if (!iter->second->valid())
			{
				respool_.erase(iter++);
			}
			else
			{
				iter++;
			}
		}
	}

	//-------------------------------------------------------------------------------------
	void Resmgr::handleTimeout(KBEngine::TimerHandle handle, void *arg)
	{
		update();
	}

	//-------------------------------------------------------------------------------------
}
