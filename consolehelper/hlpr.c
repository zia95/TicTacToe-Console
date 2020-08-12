#include "stdafx.h"
//#include"../include/hlpr.h"


static HANDLE __hConOut;
void SetConsoleOutHandle(HANDLE hConOut)
{
	_BOOL bHndl = CHECK_HANDLE(hConOut);
	assert(bHndl);
	if (bHndl)
	{
		__hConOut = hConOut;
	}
}
void PrintAllColorsOnConsole()
{
	for (WORD k = 0; k < 256; k++)
	{
		_BOOL bColorEnabled = SetConsoleColor(__hConOut, k);
		assert(bColorEnabled);
		if (bColorEnabled)
			printf("%d console color!!\n", k);
	}
}

static VECTOR2 __pCoordRestore = {0,0};
void StorePos()
{
	_BOOL bStored = GetConsolePosition(__hConOut, &__pCoordRestore);
	assert(bStored);//"get c pos failed!!"
}
void RestorePos()
{
	_BOOL bRestored = SetConsolePosition(__hConOut, __pCoordRestore);
	assert(bRestored);
}

static WORD __wColorRestore = 0;
void StoreColor()
{
	_BOOL bRes = GetConsoleColor(__hConOut, &__wColorRestore);
	assert(bRes);
}
void RestoreColor()
{
	_BOOL bRes = SetConsoleColor(__hConOut, __wColorRestore);
	assert(bRes);
}


void StoreState()
{
	StorePos();
	StoreColor();
}
void RestoreState()
{
	RestorePos();
	RestoreColor();
}