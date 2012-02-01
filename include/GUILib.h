
#ifndef _GUI_LIB_H_
#define _GUI_LIB_H_

#ifdef BUILD_DLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT __declspec(dllimport)
#endif

#endif
