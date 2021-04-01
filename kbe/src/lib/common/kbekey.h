// Copyright 2008-2018 Yolo Technologies, Inc. All Rights Reserved. https://www.comblockengine.com

#ifndef KBENGINE_KEY_H
#define KBENGINE_KEY_H

#include "rsa.h"

namespace KBEngine
{


/**
 *	引擎的key管理
 */
class KBEKey : public KBE_RSA
{

private:
	KBEKey(const std::string& pubkeyname, 
		const std::string& prikeyname);

	virtual ~KBEKey();

	KBEKey(KBEKey &) = delete;
	void operator=(KBEKey &) = delete;

	inline static KBEKey *singleton_ = nullptr;

public:
	virtual bool isGood() const;

	static KBEKey &getSingleton(const std::string &pubkeyname,
															const std::string &prikeyname)
	{
		if (!singleton_)
		{
			singleton_ = new KBEKey(pubkeyname, prikeyname);
		}
		return *singleton_;
	}

	static KBEKey &getSingleton()
	{
		return *singleton_;
	}

	static KBEKey *getSingletonPtr()
	{
		return singleton_;
	}
};
}

#endif // KBENGINE_KEY_H
