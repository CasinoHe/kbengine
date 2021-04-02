// Copyright 2008-2018 Yolo Technologies, Inc. All Rights Reserved. https://www.comblockengine.com
// Refactored: 2021.03.31
// Refactored by: CasinoHe
// Purpose: a singleton c++ template class implementation with app parameter constructor

// all modern c++ compiler supported pragma once
#pragma once

#include "common/common.h"

/*
	motivation:
		It's desinged to avoid creating two singleton instance

	usage:
		class A:public Singleton<A>
		{
			friend Singleton<A>;  // required, Singleton class need to create a static instance

		private:
			A();  // required, derived class need to declare a private constructor

	 	protected: (optinal, if not implement in derived class, the class factory will use singletonInit in base class)
			virtual void singletonInit() override { ... }
		};

		A::getSingleton(dispacher, interface, componenttype, componentid).xxx();

		There is no A instance outside, only static instance insdie class A
*/

namespace smallgames
{
  namespace Network
  {
    class EventDispatcher;
    class NetworkInterface;
  }

  template <typename T>
  class AppSingleton
  {
	private:
		inline static T *singleton_ = nullptr;

	protected:
		virtual void singletonInit() {}

	public:
    static T &getSingleton(Network::EventDispatcher &dispatcher,
                           Network::NetworkInterface &ninterface,
                           COMPONENT_TYPE componentType,
                           COMPONENT_ID componentID)
    {
      if (!singleton_)
      {
        singleton_ = new T(dispatcher, ninterface, componentType, componentID);
        singleton_->singletonInit();
      }

      return (*singleton_);
    }

    static T *getSingletonPtr(void)
		{
			return singleton_;
		}

    static T &getSingleton(void)
		{
			return *singleton_;
		}

		~AppSingleton(void)
		{
			if (singleton_)
			{
				delete singleton_;
			}
			singleton_ = nullptr;
		}

	protected:
    AppSingleton() {}
  };
}
