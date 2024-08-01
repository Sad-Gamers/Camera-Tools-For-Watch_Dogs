#include "FileManager.h"
#include "RenderConfig.h"

void FileManager::Initialize() {
    Imagebase = Misc::Imagebase;
	FileOpen = (FileOpen_t)(Imagebase + Offsets::FileOpen);
	FileOpenFromPathId = (FileOpenFromPathId_t)(Imagebase + Offsets::FileOpenFromPathId);
	FileClose = (FileClose_t)(Imagebase + Offsets::FileClose);
    MH_CreateHook((LPVOID)(Imagebase + Offsets::FileOpen), &FileOpen_Detour, reinterpret_cast<LPVOID*>(&FileOpen));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::FileOpenFromPathId), &FileOpenFromPathId_Detour, reinterpret_cast<LPVOID*>(&FileOpenFromPathId));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::FileOpen));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::FileOpenFromPathId));
}

uintptr_t FileManager::GetFileManager() {
    return ((*(uintptr_t*)((Imagebase + Offsets::CFileManager)) + 0x0));
}


uintptr_t FileManager::FileOpenFromPathId_Detour(uintptr_t CFileManager, uintptr_t CPathID, bool XCompress) {
    uintptr_t OriginalOpen = FileOpenFromPathId(CFileManager, CPathID, XCompress);
    if (*(uint32_t*)CPathID == Misc::FNV32("worlds\\windy_city\\generated\\wlu\\wlu_data_sk_m03.xml.data.fcb")) {
        return FileOpen(CFileManager, CustomWLU.c_str(), 1, false);;
    }
    return OriginalOpen;
}

uintptr_t FileManager::FileOpen_Detour(uintptr_t CFileManager, const char* FileName, int AccessMode, bool XCompress) {
    std::string FilePathStr = FileName;
    if (FilePathStr.substr(FilePathStr.find_last_of("/\\") + 1) == "GamerProfile.xml") {
        RenderConfig::Initialized = false;
    }
    return FileOpen(CFileManager, FileName, AccessMode, XCompress);
}



