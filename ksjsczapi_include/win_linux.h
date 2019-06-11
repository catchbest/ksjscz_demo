#pragma once
#pragma execution_character_set("utf-8")

// 这个文件里需要定义用户所包含的头文件中，一些windows下定义的类型，需要在linux下定义一下，
// 只定义头文件中无法在linux下识别的数据类型

#ifdef _WIN32
#include <Windows.h>
#include <tchar.h>
#endif


#ifdef linux

typedef void                *HWND;

#ifdef _UNICODE
#    ifndef _TCHAR_DEFINED
typedef wchar_t TCHAR, *PTCHAR;
#    define _TCHAR_DEFINED
#    endif /* !_TCHAR_DEFINED */
#else  /* _UNICODE */
#    ifndef _TCHAR_DEFINED
typedef char TCHAR, *PTCHAR;
#    define _TCHAR_DEFINED
#    endif /* !_TCHAR_DEFINED */
#endif

#endif