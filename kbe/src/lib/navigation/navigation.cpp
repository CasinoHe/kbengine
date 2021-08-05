// Copyright 2008-2018 Yolo Technologies, Inc. All Rights Reserved. https://www.comblockengine.com

#include "navigation.h"
#include "resmgr/resmgr.h"
#include "thread/threadguard.h"

#include "navigation_tile_handle.h"
#include "navigation_mesh_handle.h"

namespace KBEngine{

//-------------------------------------------------------------------------------------
Navigation::Navigation():
navhandles_(),
mutex_()
{
}

//-------------------------------------------------------------------------------------
Navigation::~Navigation()
{
	finalise();
}

//-------------------------------------------------------------------------------------
void Navigation::finalise()
{
	KBEngine::thread::ThreadGuard tg(&mutex_);
	navhandles_.clear();
}

//-------------------------------------------------------------------------------------
bool Navigation::removeNavigation(std::string resPath)
{
	KBEngine::thread::ThreadGuard tg(&mutex_); 
	KBEUnordered_map<std::string, NavigationHandlePtr>::iterator iter = navhandles_.find(resPath);
	if(navhandles_.find(resPath) != navhandles_.end())
	{
		iter->second->decRef();
		navhandles_.erase(iter);

		DEBUG_MSG(fmt::format("Navigation::removeNavigation: ({}) is destroyed!\n", resPath));
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------
NavigationHandlePtr Navigation::findNavigation(std::string resPath)
{
	KBEngine::thread::ThreadGuard tg(&mutex_); 
	KBEUnordered_map<std::string, NavigationHandlePtr>::iterator iter = navhandles_.find(resPath);
	if(navhandles_.find(resPath) != navhandles_.end())
	{
		if(iter->second == NULL)
			return NULL;

		if(iter->second->type() == NavigationHandle::NAV_MESH)
		{
			return iter->second;
		}
		else if (iter->second->type() == NavigationHandle::NAV_TILE)
		{
			// 由于tile需要做碰撞， 每一个space都需要一份新的数据， 我们这里采用拷贝的方式来增加构造速度
			NavTileHandle* pNavTileHandle = new NavTileHandle(*(KBEngine::NavTileHandle*)iter->second.get());
			DEBUG_MSG(fmt::format("Navigation::findNavigation: copy NavTileHandle({:p})!\n", (void*)pNavTileHandle));
			return NavigationHandlePtr(pNavTileHandle);
		}

		return iter->second;
	}

	return NULL;
}

//-------------------------------------------------------------------------------------
bool Navigation::hasNavigation(std::string resPath)
{
	KBEngine::thread::ThreadGuard tg(&mutex_); 
	return navhandles_.find(resPath) != navhandles_.end();
}

//-------------------------------------------------------------------------------------
NavigationHandlePtr Navigation::loadNavigation(std::string resPath, const std::map< int, std::string >& params)
{
	KBEngine::thread::ThreadGuard tg(&mutex_); 
	if(resPath == "")
		return NULL;
	
	KBEUnordered_map<std::string, NavigationHandlePtr>::iterator iter = navhandles_.find(resPath);
	if(iter != navhandles_.end())
	{
		return iter->second;
	}

	NavigationHandle* pNavigationHandle_ = NULL;

	std::string path = resPath;
	path = smallgames::GetPathMgr().get_full_path(path);
	if (path.size() == 0)
		return nullptr;
		
	std::vector<std::string> results;
	smallgames::GetPathMgr().list_res(path, "tmx", results);

	if(results.size() > 0)
	{
		pNavigationHandle_ = NavTileHandle::create(resPath, params);
	}
	else 	
	{
		results.clear();
		smallgames::GetPathMgr().list_res(path, "navmesh", results);

		if(results.size() == 0)
		{
			return nullptr;
		}

		pNavigationHandle_ = NavMeshHandle::create(resPath, params);
	}


	navhandles_[resPath] = NavigationHandlePtr(pNavigationHandle_);
	return pNavigationHandle_;
}

//-------------------------------------------------------------------------------------		
}
