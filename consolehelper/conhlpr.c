#include "stdafx.h"
//#include "../include/conhlpr.h"

/*
#include<stdio.h>
#include<stdlib.h>
#include <windows.h>

typedef COORD VECTOR2, *PVECTOR2;
typedef CONSOLE_SCREEN_BUFFER_INFO CON_SCRN_INFO, *PCON_SCRN_INFO;

typedef enum _BOOL_
{
	_false = 0,
	_true = 1,
}_BOOL, *_PBOOL, **_LPBOOL;


#define CHECK_HANDLE(handle) handle > 0//check con handle

#define IN_STD_HANDLE STD_INPUT_HANDLE
#define OUT_STD_HANDLE STD_OUTPUT_HANDLE
#define ERR_STD_HANDLE STD_ERROR_HANDLE
*/
_BOOL SetTitle(LPCSTR lpTitle)
{
	return SetConsoleTitleA(lpTitle);
}

HANDLE GetConsoleStdHandle(DWORD dwStdHandle)
{
	return GetStdHandle(dwStdHandle);
}
_BOOL CloseConStdHandle(HANDLE hConsole)
{
	return CloseHandle(hConsole);
}

HANDLE GetConsoleStdInHandle()
{
	return GetConsoleStdHandle(OUT_STD_HANDLE);
}
HANDLE GetConsoleStdOutHandle()
{
	return GetConsoleStdHandle(OUT_STD_HANDLE);
}
HANDLE GetConsoleStdErrHandle()
{
	return GetConsoleStdHandle(ERR_STD_HANDLE);
}

_BOOL GetConsoleInfo(HANDLE hConOut, PCON_SCRN_INFO pConsoleScreenInfo)
{
	if (CHECK_HANDLE(hConOut))
	{
		return GetConsoleScreenBufferInfo(hConOut, pConsoleScreenInfo);
	}
	return _false;
}

_BOOL GetConsolePosition(HANDLE hConOut, PVECTOR2 vec2ConPos)
{
	if (CHECK_HANDLE(hConOut))
	{
		CON_SCRN_INFO csbi = { 0 };

		if (GetConsoleInfo(hConOut, &csbi))
		{
			vec2ConPos->X = csbi.dwCursorPosition.X;
			vec2ConPos->Y = csbi.dwCursorPosition.Y;
			return _true;
		}
	}

	return _false;
}
_BOOL SetConsolePosition(HANDLE hConOut, VECTOR2 vec2ConPos)
{
	if (CHECK_HANDLE(hConOut))
	{
		return SetConsoleCursorPosition(hConOut, vec2ConPos);
	}
	return _false;
}

_BOOL SetConsoleColor(HANDLE hConOut, WORD wAttr)
{
	if (CHECK_HANDLE(hConOut))
	{
		return SetConsoleTextAttribute(hConOut, wAttr);
	}
	return _false;
}
_BOOL GetConsoleColor(HANDLE hConOut, LPWORD wAttr)
{
	if (CHECK_HANDLE(hConOut) && wAttr != NULL)
	{
		CON_SCRN_INFO csbi = { 0 };

		if (GetConsoleInfo(hConOut, &csbi))
		{
			*wAttr = csbi.wAttributes;
			return _true;
		}
	}

	return _false;
}

_BOOL SetConsoleWindowSize(HANDLE hConOut, BOOL bAbs, PSRECT lpConsoleWindow)
{
	if (CHECK_HANDLE(hConOut))
	{
		return SetConsoleWindowInfo(hConOut, bAbs, lpConsoleWindow);
	}
	return _false;
}