// Created by ËÕÔªº£ on 09/19/2016.
// Copyright (c) 2016 amoylel. All rights reserved.

#ifndef IME_SYSTEM_HPP__
#define IME_SYSTEM_HPP__

#include <amo/config.hpp>
namespace amo
{
	class system
	{
	public:

		int get_cup_core_num()
		{
		#if defined(WIN32) 
			SYSTEM_INFO info;
			GetSystemInfo(&info);
			return info.dwNumberOfProcessors;
		#elif defined(LINUX) || defined(SOLARIS) || defined(AIX) || defined(__linux__)|| defined(__LINUX__)
			return get_nprocs();   //GNU fuction 
		#else 
		#error  invalid system 
		#endif 
		}
	};
}

#endif // IME_SYSTEM_HPP__
