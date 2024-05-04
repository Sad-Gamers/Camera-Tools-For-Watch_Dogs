#include "FileManager.h"
#include "ResourceManager.h"

void ResourceManager::Initialize() {
    Imagebase = Misc::Imagebase;
    LoadDep = (LoadDep_t)(Imagebase + Offsets::LoadDep);
	MH_CreateHook((LPVOID)(Imagebase + Offsets::LoadDep), &LoadDep_Detour, reinterpret_cast<LPVOID*>(&LoadDep));
	MH_EnableHook((LPVOID)(Imagebase + Offsets::LoadDep));
    DeploadLoaded = false;
}

uintptr_t ResourceManager::GetResourceManager() {
    return ((*(uintptr_t*)((*(uintptr_t*)(Imagebase + Offsets::CResourceManager)) + 0x88) + 0x0));
}

uintptr_t ResourceManager::LoadDep_Detour(uintptr_t CResourceManager, uintptr_t IFile, bool XCompress) {
    uintptr_t FilePtr = FileManager::FileOpen(FileManager::GetFileManager(), 
        CustomDepload.c_str(), 1, false);
    if (FilePtr) {
        LoadDep(GetResourceManager(), FilePtr, true);
        FileManager::FileClose(FileManager::GetFileManager(), FilePtr);
        DeploadLoaded = true;
    }
    return LoadDep(CResourceManager, IFile, XCompress);
}