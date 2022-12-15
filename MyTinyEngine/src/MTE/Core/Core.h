#pragma once

#ifdef MTE_PLATFORM_WINDOWS
	#ifdef MTE_BUILD_DLL
		#define MTE_API __declspec(dllexport)
	#else
		#define MTE_API __declspec(dllimport)
	#endif
#else
	#error MTE only suppoirt windows!
#endif