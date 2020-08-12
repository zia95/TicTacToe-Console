#pragma once

#include<stdio.h>
#include<stdlib.h>
#include <windows.h>

typedef COORD VECTOR2, *PVECTOR2;
typedef CONSOLE_SCREEN_BUFFER_INFO CON_SCRN_INFO, *PCON_SCRN_INFO;
typedef SMALL_RECT SRECT, *PSRECT;
typedef enum _BOOL_
{
	_false = 0,
	_true = 1,
}_BOOL, *_PBOOL, **_LPBOOL;


#define CHECK_HANDLE(handle) handle > 0//check con handle

#define IN_STD_HANDLE STD_INPUT_HANDLE
#define OUT_STD_HANDLE STD_OUTPUT_HANDLE
#define ERR_STD_HANDLE STD_ERROR_HANDLE

_BOOL SetTitle(LPCSTR lpTitle);

HANDLE GetConsoleStdHandle(DWORD dwStdHandle);
_BOOL CloseConStdHandle(HANDLE hConsole);

HANDLE GetConsoleStdInHandle();
HANDLE GetConsoleStdOutHandle();
HANDLE GetConsoleStdErrHandle();

_BOOL GetConsoleInfo(HANDLE hConOut, PCON_SCRN_INFO pConsoleScreenInfo);

_BOOL GetConsolePosition(HANDLE hConOut, PVECTOR2 vec2ConPos);
_BOOL SetConsolePosition(HANDLE hConOut, VECTOR2 vec2ConPos);

_BOOL SetConsoleColor(HANDLE hConOut, WORD wAttr);
_BOOL GetConsoleColor(HANDLE hConOut, LPWORD wAttr);

_BOOL SetConsoleWindowSize(HANDLE hConOut, BOOL bAbs, PSRECT lpConsoleWindow);