// Copyright 2008-2018 Yolo Technologies, Inc. All Rights Reserved. https://www.comblockengine.com

#include "kbcmd.h"
#include "server_assets.h"
#include "entitydef/entitydef.h"
#include "entitydef/scriptdef_module.h"
#include "entitydef/property.h"
#include "entitydef/method.h"
#include "entitydef/datatypes.h"
#include "entitydef/datatype.h"
#include "resmgr/resmgr.h"
#include "server/common.h"
#include "server/serverconfig.h"
#include "common/kbeversion.h"
#include "network/fixed_messages.h"

#include "client_lib/client_interface.h"
#include "baseapp/baseapp_interface.h"
#include "baseappmgr/baseappmgr_interface.h"
#include "dbmgr/dbmgr_interface.h"
#include "loginapp/loginapp_interface.h"

namespace KBEngine {	

//-------------------------------------------------------------------------------------
ServerAssets::ServerAssets():
	basepath_()
{

}

//-------------------------------------------------------------------------------------
ServerAssets::~ServerAssets()
{

}

//-------------------------------------------------------------------------------------
ServerAssets* ServerAssets::createServerAssets(const std::string& type)
{
	//std::string lowerType = type;
	//std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), tolower);

	return new ServerAssets();
}

//-------------------------------------------------------------------------------------
bool ServerAssets::good() const
{
	return true;
}

//-------------------------------------------------------------------------------------
bool ServerAssets::create(const std::string& path)
{
	basepath_ = path;

	if (basepath_[basepath_.size() - 1] != '\\' && basepath_[basepath_.size() - 1] != '/')
		basepath_ += "/";

	std::string findpath = "sdk_templates/server/" + name();

	std::string getpath = smallgames::GetPathMgr().get_full_path(findpath);

	if (getpath.size() == 0 || findpath == getpath)
	{
		ERROR_MSG(fmt::format("ServerAssets::create(): not found path({})\n",
			findpath));

		return false;
	}

	if (!copyAssetsSourceToPath(getpath))
		return false;

	return true;
}

//-------------------------------------------------------------------------------------
bool ServerAssets::copyAssetsSourceToPath(const std::string& path)
{
	std::vector<std::string> results;
	if (!smallgames::GetPathMgr().list_res(path, "*", results))
		return false;

	std::string findpath("sdk_templates/server/" + name());

	auto iter = results.cbegin();
	for (; iter != results.cend(); ++iter)
	{
		std::string::size_type fpos = (*iter).find(findpath);

		std::string currpath((*iter).c_str());

		if (fpos == std::wstring::npos)
		{
			ERROR_MSG(fmt::format("ServerAssets::copyAssetsSourceToPath(): split path({}) error!\n",
				currpath));

			return false;
		}

		std::string targetFile = (*iter);
		targetFile.erase(0, fpos + findpath.size() + 1);
		targetFile = (basepath_ + targetFile);

		std::string basepath(targetFile);
		fpos = targetFile.rfind("/");

		if (fpos == std::wstring::npos)
		{
			ERROR_MSG(fmt::format("ServerAssets::copyAssetsSourceToPath(): split basepath({}) error!\n", targetFile));

			return false;
		}

		basepath.erase(fpos, basepath.size() - fpos);

		if (KBCMD::creatDir(basepath.c_str()) == -1)
		{
			ERROR_MSG(fmt::format("ServerAssets::copyAssetsSourceToPath(): creating directory error! path={}\n", basepath));
			return false;
		}

		std::ifstream input(currpath, std::ios::binary);
		std::ofstream output(targetFile, std::ios::binary);

		std::stringstream ss;
		std::string filebody;

		ss << input.rdbuf();
		filebody = ss.str();

		output << filebody;

		output.close();
		input.close();
	}

	return true;
}

//-------------------------------------------------------------------------------------
}
