// dllmain.cpp : Defines the entry point for the DLL application.
#include "GlobalHeaders.h"
#include "Main.h"
#include "FileManager.h"
#include "ResourceManager.h"
#include "SadGUI.h"
#include "UserConfig.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    static Main* main = NULL;
    char dllFilePath[MAX_PATH] = { 0 };   
    std::string temp = "";
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        GetModuleFileNameA(hModule, dllFilePath, MAX_PATH);
        temp = dllFilePath;
        FileManager::RootPath = temp.substr(0, temp.find_last_of("\\/"));
        ResourceManager::CustomDepload = FileManager::RootPath + "\\Dependencies\\CameraTool\\MoveDepload.dat";
        FileManager::CustomWLU = FileManager::RootPath + "\\Dependencies\\CameraTool\\CinematicLights.xml.data.fcb";
        SadGUI::Font = FileManager::RootPath + "\\Dependencies\\ImGui\\BlenderPro-Book.ttf";
        UserConfig::HotKeyConfigPath = FileManager::RootPath + "\\Dependencies\\User\\Hotkeys.bin";
        UserConfig::GUIConfigPath = FileManager::RootPath + "\\Dependencies\\User\\GUI.bin";
        UserConfig::HotFixConfigPath = FileManager::RootPath + "\\Dependencies\\User\\HotFixes.bin";
        UserConfig::RenderConfigPath = FileManager::RootPath + "\\Dependencies\\User\\RenderConfig.bin";
        UserConfig::AnimationBookmarksPath = FileManager::RootPath + "\\Dependencies\\User\\AnimationBookmarks.txt";
        UserConfig::GraphicKitBookmarksPath = FileManager::RootPath + "\\Dependencies\\User\\GraphicKitBookmarks.txt";
        UserConfig::CameraData1Path = FileManager::RootPath + "\\Dependencies\\User\\CameraData1.bin";
        UserConfig::CameraData2Path = FileManager::RootPath + "\\Dependencies\\User\\CameraData2.bin";
        DisableThreadLibraryCalls(hModule);
        main = new Main();
        main->Initialize();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return true;
}