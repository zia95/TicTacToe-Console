#pragma once
#include"conhlpr.h"
#include<assert.h>

//HANDLE __hConOut;
void SetConsoleOutHandle(HANDLE hConOut);
void PrintAllColorsOnConsole();

//PVECTOR2 pCoordRestore = NULL;
void StorePos();
void RestorePos();

//WORD wColorRestore = 0;
void StoreColor();
void RestoreColor();


void StoreState();
void RestoreState();