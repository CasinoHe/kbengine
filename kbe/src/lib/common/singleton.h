// Copyright 2008-2018 Yolo Technologies, Inc. All Rights Reserved. https://www.comblockengine.com
// Refactored: 2021.03.31
// Refactored by: CasinoHe
// Purpose: a singleton c++ template class implementation with no parameter constructor

// all modern c++ compiler supported pragma once
#pragma once

/*
	motivation:
		It's desinged to avoid creating two singleton instance

	usage:
		class A:public Singleton<A>
		{
			friend Singleton<A>;  // required, Singleton class need to create a static instance
		private:
			A();  // required, derived class need to declare a private constructor
			~A();

	 	protected: (optinal, if not implement in derived class, the class factory will use singletonInit in base class)
			virtual void singletonInit() override { ... }
		};

		A::getSingleton().xxx();

		There is no A instance outside, only static instance insdie class A
*/

namespace smallgames
{

	template <typename T>
	class Singleton
	{
	private:
		inline static T *singleton_ = nullptr;

	protected:
		virtual void singleton_init() {}

	public:
		static T &getSingleton(void)
		{
			if (!singleton_)
			{
				singleton_ = new T;
				singleton_->singleton_init();
			}

			return (*singleton_);
		}

		static T *getSingletonPtr(void)
		{
			return singleton_;
		}

		~Singleton(void)
		{
			if (singleton_)
			{
				delete singleton_;
			}
			singleton_ = nullptr;
		}

	protected:
		Singleton(void) {}
	};
}
