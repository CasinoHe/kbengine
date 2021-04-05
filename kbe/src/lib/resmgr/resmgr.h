// Copyright 2008-2018 Yolo Technologies, Inc. All Rights Reserved. https://www.comblockengine.com
// Refactored: 2021.04.01
// Refactored by: CasinoHe
// Purpose: Manager all resource paths, redesign res manager by c++ 11/14/17 features

// all modern c++ compiler supported pragma once
#pragma once

#include "resourceobject.h"
#include "common/common.h"
#include "common/singleton.h"
#include "xml/xml.h"	
#include "common/timer.h"

#include <filesystem>
#include <vector>
#include <unordered_map>
#include <string>
#include <initializer_list>
#include <thread>
#include <mutex>
	
namespace smallgames
{

#define RESOURCE_NORMAL	0x00000000
#define RESOURCE_RESIDENT 0x00000001
#define RESOURCE_READ 0x00000002
#define RESOURCE_WRITE 0x00000004
#define RESOURCE_APPEND 0x00000008

	class PathMgr final: public Singleton<PathMgr>
	{
		friend Singleton<PathMgr>;

	private:
		PathMgr();
		~PathMgr() = default;

		PathMgr(PathMgr &) = delete;
		void operator=(PathMgr &) = delete;

	public:
		inline static const std::filesystem::path DEFAULT_BIN_PATH{"bin"};
		inline static const std::filesystem::path DEFAULT_ASSETS_PATH{"assets"};
		inline static const std::filesystem::path DEFAULT_RES_PATH{"assets/res"};
		inline static const std::filesystem::path DEFAULT_SCRIPT_PATH{"assets/res/scripts"};
		inline static const char *const ROOT_PATH_VAR{"SMG_ROOT"};
		inline static const char *const BIN_PATH_VAR{"SMG_BIN_PATH"};
		inline static const char *const RES_PATH_VAR{"SMG_RES_PATH"};
		inline static const char *const SCRIPT_PATH_VAR{"SMG_SCRIPT_PATH"};

	private:
		void set_env_paths();
		void set_default_paths();

	protected:
		virtual void singleton_init() override;

	// interface
	public:
		void print(const char *extra_msg = nullptr);
		inline bool is_inited() { return is_inited_; }

		std::string get_full_path(const std::initializer_list<std::string> path_nodes);
		std::string get_full_path(const std::string &path);
		bool exists(const std::initializer_list<std::string> path_nodes);
		bool exists(const std::string &path);

		bool list_res(const std::string &path, const std::string &extensions, std::vector<std::string> &results);
		bool walk_path(const std::filesystem::path &path, const std::vector<std::string> &extensions, std::vector<std::string> &results);

		std::string get_file_content(const std::initializer_list<std::string> path_notes);
		std::string get_file_content(const std::string &file_path);

		const std::string get_res_path();
		const std::string get_script_path();
		const std::string get_component_script_path(KBEngine::COMPONENT_TYPE component_type);

		const std::string get_bin_path() { return smg_paths_.bin_path; }
		const std::string get_root_path() { return smg_paths_.root_path; }

	public:
		struct SMGPaths
		{
			std::filesystem::path root_path;
			std::filesystem::path bin_path;
			std::filesystem::path script_path;
			std::vector<std::filesystem::path> res_paths;
		};

	private:
		SMGPaths smg_paths_;
		bool is_inited_;
	};

	class Resmgr : public Singleton<Resmgr>, public KBEngine::TimerHandler
	{
	public:
		inline static std::uint64_t respool_timeout{0};
		inline static std::uint32_t respool_buffersize{0};
		inline static std::uint32_t respool_checktick{0};

	private:
		friend Singleton<Resmgr>;
		Resmgr();
		~Resmgr();

		virtual void singleton_init() override;

	public:
		inline bool is_inited() { return is_inited_; }

		KBEngine::ResourceObjectPtr open_resource(std::initializer_list<std::string> path_list, std::ios::openmode mode = std::ios::in,
																	 std::uint32_t flags = RESOURCE_NORMAL);
		KBEngine::ResourceObjectPtr open_resource(const std::string &full_path, std::ios::openmode mode = std::ios::in,
																	 std::uint32_t flags = RESOURCE_NORMAL);

		bool initialize_watcher();

		void update();

	private:
		virtual void handleTimeout(KBEngine::TimerHandle handle, void *arg);

	private:
		bool is_inited_;
		std::unordered_map<std::string, KBEngine::ResourceObjectPtr> respool_;
		std::mutex mutex_;
	};

	extern PathMgr &g_pathmgr;
}
