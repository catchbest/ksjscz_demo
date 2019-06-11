#pragma once
#pragma execution_character_set("utf-8")

// ����ļ�����Ҫ�����û���������ͷ�ļ��У�һЩwindows�¶�������ͣ���Ҫ��linux�¶���һ�£�
// ֻ����ͷ�ļ����޷���linux��ʶ�����������

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