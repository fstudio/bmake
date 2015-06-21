/*
*/
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif 
#include <Windows.h>
#include <stdio.h>

static char buffer[260 + 1] = { 0 };

static const char *PathTempGet()
{
	GetTempPathA(260, buffer);
	return buffer;
}

extern "C"{
	const char *path_tmp = PathTempGet();
}