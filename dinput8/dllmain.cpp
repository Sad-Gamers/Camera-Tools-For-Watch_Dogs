// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include "dinput8.h"


extern "C" __declspec(dllexport) HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, LPUNKNOWN punkOuter)
{
	char path[MAX_PATH];
	GetSystemDirectoryA(path, MAX_PATH);
	strcat_s(path, "\\dinput8.dll");
	HMODULE dinput8dll = LoadLibraryA(path);
	if (!dinput8dll) return E_FAIL;
	FARPROC originalProc = GetProcAddress(dinput8dll, "DirectInput8Create");
	LoadLibraryA("SadHook.dll");
	return ((HRESULT(WINAPI*)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN))originalProc)(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}


bool WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return true;
}
