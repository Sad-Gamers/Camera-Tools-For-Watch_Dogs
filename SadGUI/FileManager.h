#pragma once
#include "GlobalHeaders.h"

class FileManager
{
public:
	inline static uintptr_t Imagebase;
	static void Initialize();

	static uintptr_t GetFileManager();

	inline static std::string CustomWLU;
	inline static std::string RootPath;

	typedef uintptr_t(*FileOpen_t)(uintptr_t, const char*, int, bool);
	inline static FileOpen_t FileOpen;

	typedef uintptr_t(*FileClose_t)(uintptr_t, uintptr_t);
	inline static FileClose_t FileClose;

	typedef uintptr_t(*FileOpenFromPathId_t)(uintptr_t, uintptr_t, bool);
	inline static FileOpenFromPathId_t FileOpenFromPathId;

	static uintptr_t FileOpen_Detour(uintptr_t CFileManager, const char* FileName, int AccessMode, bool XCompress);

	static uintptr_t FileOpenFromPathId_Detour(uintptr_t CFileManager, uintptr_t CPathID, bool XCompress);

};