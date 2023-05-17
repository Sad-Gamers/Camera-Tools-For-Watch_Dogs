#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>

class SadHook
{
public:
	inline static bool bFreeCamMode;
	static void Initialize();
	static void SadHookUpdate();
	static void ShowConsole();
	static DWORD64 GetImagebase();
};