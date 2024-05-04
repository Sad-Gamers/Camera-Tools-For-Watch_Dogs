#pragma once
#include "GlobalHeaders.h"

class ResourceManager
{
public:
	inline static uintptr_t Imagebase;
	static void Initialize();
	static uintptr_t GetResourceManager();

	inline static bool DeploadLoaded;
	inline static std::string CustomDepload;

	typedef uintptr_t(*LoadDep_t)(uintptr_t, uintptr_t, bool);
	inline static LoadDep_t LoadDep;

	static uintptr_t LoadDep_Detour(uintptr_t CResourceManager, uintptr_t IFile, bool XCompress);
};