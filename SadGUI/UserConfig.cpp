#include "Databases.h"
#include "UserConfig.h"
#include "HotKeys.h"
#include "SadGUI.h"
#include "SlideAnimations.h"
#include "CameraToolMonitor.h"
#include "CameraManager.h"
#include "GridShadingManager.h"
#include "RenderConfig.h"

void UserConfig::SaveRenderConfig() {
    FILE* UserRenderConfig = fopen(RenderConfigPath.c_str(), "wb");
    fwrite(&RenderConfig::UserRenderConfig, sizeof(RenderConfig::UserRenderConfig), 1, UserRenderConfig);
    fclose(UserRenderConfig);
}

void UserConfig::LoadRenderConfig() {
    FILE* UserRenderConfig = fopen(RenderConfigPath.c_str(), "rb");
    if (UserRenderConfig) {
        fread(&RenderConfig::UserRenderConfig, sizeof(RenderConfig::UserRenderConfig), 1, UserRenderConfig);
        fclose(UserRenderConfig);
    }
}

void UserConfig::LoadHotKeys() {
	FILE* UserHotkeys = fopen(HotKeyConfigPath.c_str(), "rb");
	if (UserHotkeys) {
		fread(&HotKeyFile, sizeof(HotKeyFile), 1, UserHotkeys);
		fclose(UserHotkeys);
        HotKeyFileToSave = HotKeyFile;
        HotKeys::EditorGUI = Databases::HotKeys[HotKeyFile.GUI];
        HotKeys::EditorFreeCam = Databases::HotKeys[HotKeyFile.FreeCam];
        HotKeys::EditorTimeStop = Databases::HotKeys[HotKeyFile.TimeStop];
        HotKeys::EditorSlowMo = Databases::HotKeys[HotKeyFile.SlowMo];
        HotKeys::EditorHUD = Databases::HotKeys[HotKeyFile.HUD];
        HotKeys::EditorGridShading = Databases::HotKeys[HotKeyFile.GridShading];
        HotKeys::EditorTransition = Databases::HotKeys[HotKeyFile.Transition];
        HotKeys::GUI = Databases::HotKeyCodes[HotKeyFile.GUI];
        HotKeys::FreeCam = Databases::HotKeyCodes[HotKeyFile.FreeCam];
        HotKeys::TimeStop = Databases::HotKeyCodes[HotKeyFile.TimeStop];
        HotKeys::SlowMo = Databases::HotKeyCodes[HotKeyFile.SlowMo];
        HotKeys::HUD = Databases::HotKeyCodes[HotKeyFile.HUD];
        HotKeys::GridShading = Databases::HotKeyCodes[HotKeyFile.GridShading];
        HotKeys::Transition = Databases::HotKeyCodes[HotKeyFile.Transition];
	}
	else
	{
        HotKeys::EditorGUI = Databases::HotKeys[1];
        HotKeys::EditorFreeCam = Databases::HotKeys[2];
        HotKeys::EditorSlowMo = Databases::HotKeys[11];
        HotKeys::EditorTimeStop = Databases::HotKeys[10];
        HotKeys::EditorHUD = Databases::HotKeys[9];
        HotKeys::EditorGridShading = Databases::HotKeys[13];
        HotKeys::EditorTransition = Databases::HotKeys[7];
        HotKeys::GUI = Databases::HotKeyCodes[1];
        HotKeys::FreeCam = Databases::HotKeyCodes[2];
        HotKeys::TimeStop = Databases::HotKeyCodes[11];
        HotKeys::SlowMo = Databases::HotKeyCodes[10];
        HotKeys::HUD = Databases::HotKeyCodes[9];
        HotKeys::Transition = Databases::HotKeyCodes[7];
        HotKeyFileToSave = {1, 2, 9, 10, 8, 13, 7};
	}
}

void UserConfig::LoadGUIConfig() {
    FILE* GUIConfig = fopen(GUIConfigPath.c_str(), "rb");
    if (GUIConfig) {
        fread(&GUIFile, sizeof(GUIFile), 1, GUIConfig);
        fclose(GUIConfig);
        if (GUIFile.FontSize > 30.0f) {
            GUIFile.FontSize = 30.0f;
        }
        if (GUIFile.FontSize < 15.0f) {
            GUIFile.FontSize = 15.0f;
        }
        GUIFileToSave = GUIFile;
        SadGUI::FontSize = GUIFile.FontSize;
    }
    else
    {
        GUIFile.FontSize = 18.0f;
        GUIFileToSave = GUIFile;
        SadGUI::FontSize = GUIFile.FontSize;
    }
    SadGUI::ReloadFont = true;
}

void UserConfig::SaveAndReloadGUIConfig() {
    FILE* UserGUIConfig = fopen(GUIConfigPath.c_str(), "wb");
    fwrite(&GUIFileToSave, sizeof(GUIFileToSave), 1, UserGUIConfig);
    fclose(UserGUIConfig);
    LoadGUIConfig();
}

void UserConfig::LoadHotFixConfig() {
    FILE* UserHotFixConfig = fopen(HotFixConfigPath.c_str(), "rb");
    if (UserHotFixConfig) {
        fread(&HotFixesFile, sizeof(HotFixesFile), 1, UserHotFixConfig);
        fclose(UserHotFixConfig);
        if (HotFixesFile.FOVMultiplier > 1.45f) {
            HotFixesFile.FOVMultiplier = 1.45f;
        }
        if (HotFixesFile.FOVMultiplier < 0.75f) {
            HotFixesFile.FOVMultiplier = 0.75f;
        }
        HotFixesFileToSave = HotFixesFile;
        SlideAnimations::PatchBlowBack = HotFixesFile.BlowBack;
        SlideAnimations::SlideLocking = HotFixesFile.SlideLocking;
        GridShadingManager::DisableMenuGridShading(HotFixesFile.NoMenuGridShading);
        CameraManager::FOVMultiplier = HotFixesFile.FOVMultiplier;
        Misc::DisableMouseAcceleration = HotFixesFile.DisableMouseAcceleration;
        Misc::DisableRotSpeedCap = HotFixesFile.DisableRotSpeedCap;
    }
    else
    {
        HotFixesFile.BlowBack = true;
        HotFixesFile.SlideLocking = true;
        HotFixesFile.NoMenuGridShading = false;
        HotFixesFile.DisableMouseAcceleration = true;
        HotFixesFile.DisableRotSpeedCap = true;
        HotFixesFile.FOVMultiplier = 1.0;
        HotFixesFileToSave = HotFixesFile;
        SlideAnimations::PatchBlowBack = HotFixesFile.BlowBack;
        SlideAnimations::SlideLocking = HotFixesFile.SlideLocking;
        CameraManager::FOVMultiplier = HotFixesFile.FOVMultiplier;
        GridShadingManager::DisableMenuGridShading(HotFixesFile.NoMenuGridShading);
        Misc::DisableMouseAcceleration = HotFixesFile.DisableMouseAcceleration;
        Misc::DisableRotSpeedCap = HotFixesFile.DisableRotSpeedCap;
    }
}
void UserConfig::SaveAndReloadHotkeys() {
    FILE* UserHotkeys = fopen(HotKeyConfigPath.c_str(), "wb");
    fwrite(&HotKeyFileToSave, sizeof(HotKeyFileToSave), 1, UserHotkeys);
    fclose(UserHotkeys); 
    LoadHotKeys();
}

void UserConfig::SaveAndReloadHotFixConfig() {
    FILE* UserHotFixConfig = fopen(HotFixConfigPath.c_str(), "wb");
    if (HotFixesFileToSave.FOVMultiplier > 1.45f) {
        HotFixesFileToSave.FOVMultiplier = 1.45f;
    }
    if (HotFixesFileToSave.FOVMultiplier < 0.75f) {
        HotFixesFileToSave.FOVMultiplier = 0.75f;
    }
    fwrite(&HotFixesFileToSave, sizeof(HotFixesFileToSave), 1, UserHotFixConfig);
    fclose(UserHotFixConfig);
    LoadHotFixConfig();
}
void UserConfig::SanatizeHotKeySelection(BYTE SelectedHkey) {

    if (HotKeyFileToSave.FreeCam == SelectedHkey) {
        HotKeyFileToSave.FreeCam = 0;
        HotKeys::EditorFreeCam = "None";
    }
    if (HotKeyFileToSave.TimeStop == SelectedHkey) {
        HotKeyFileToSave.TimeStop = 0;
        HotKeys::EditorTimeStop = "None";
    }
    if (HotKeyFileToSave.SlowMo == SelectedHkey) {
        HotKeyFileToSave.SlowMo = 0;
        HotKeys::EditorSlowMo = "None";
    }
    if (HotKeyFileToSave.HUD == SelectedHkey) {
        HotKeyFileToSave.HUD = 0;
        HotKeys::EditorHUD = "None";
    }
    if (HotKeyFileToSave.GridShading == SelectedHkey) {
        HotKeyFileToSave.GridShading = 0;
        HotKeys::EditorGridShading = "None";
    }
    if (HotKeyFileToSave.Transition == SelectedHkey) {
        HotKeyFileToSave.Transition = 0;
        HotKeys::EditorTransition = "None";
    }
}

void UserConfig::LoadAnimationBookmarks() {
    std::fstream BookmarksFile(AnimationBookmarksPath);
    Databases::BookmarkedDecisionTrees = {};
    if (BookmarksFile.is_open()) {
        while (!BookmarksFile.eof())
        {
            std::string CurrIn;
            getline(BookmarksFile, CurrIn);
            CurrIn.erase(std::remove(CurrIn.begin(), CurrIn.end(), '\n'), CurrIn.cend());
            if(CurrIn != "")
                Databases::BookmarkedDecisionTrees.push_back(CurrIn);
        }
        BookmarksFile.close();
    }
        
}

void UserConfig::RemoveAnimationBookmark(const char* MoveFileName) {
    std::vector<std::string> Temp = {};
    for (int i = 0; i < Databases::BookmarkedDecisionTrees.size(); i++) {
        if (Databases::BookmarkedDecisionTrees[i].c_str() != MoveFileName)
            Temp.push_back(Databases::BookmarkedDecisionTrees[i]);
    }
    remove(AnimationBookmarksPath.c_str());
    std::fstream BookmarksFile;
    BookmarksFile.open(AnimationBookmarksPath, std::ios::app);
    for (int i = 0; i < Temp.size(); i++) {
        BookmarksFile << Temp[i];
        BookmarksFile << "\n";
    }
    BookmarksFile.close();
    Databases::BookmarkedDecisionTrees = Temp;
}

void UserConfig::SaveCameraData(int index, DirectX::XMFLOAT3 Position,
    DirectX::XMFLOAT3 Rotation,
    float FieldOfView,
    float FocusDistance,
    float FocalLength,
    float FStop,
    float NearDOF,
    float FarDOF){
    CameraData SaveFile;
    SaveFile.HasData = true;
    SaveFile.Position = Position;
    SaveFile.Rotation = Rotation;
    SaveFile.FieldOfView = FieldOfView;
    SaveFile.FocusDistance = FocusDistance;
    SaveFile.FocalLength = FocalLength;
    SaveFile.FStop = FStop;
    SaveFile.NearDOF = NearDOF;
    SaveFile.FarDOF = FarDOF;
    if (index == 0) {
        FILE* CameraDataFile = fopen(CameraData1Path.c_str(), "wb");
        fwrite(&SaveFile, sizeof(SaveFile), 1, CameraDataFile);
        fclose(CameraDataFile);
    }
    if (index == 1) {
        FILE* CameraDataFile = fopen(CameraData2Path.c_str(), "wb");
        fwrite(&SaveFile, sizeof(SaveFile), 1, CameraDataFile);
        fclose(CameraDataFile);
    }
}
void UserConfig::LoadCameraData(int index) {
    if (index == 0) {
        FILE* CameraDataFile = fopen(CameraData1Path.c_str(), "rb");
        if (CameraDataFile) {
            fread(&CameraData1, sizeof(CameraData1), 1, CameraDataFile);
            fclose(CameraDataFile);
        }
    }
    if (index == 1) {
        FILE* CameraDataFile = fopen(CameraData2Path.c_str(), "rb");
        if (CameraDataFile) {
            fread(&CameraData2, sizeof(CameraData2), 1, CameraDataFile);
            fclose(CameraDataFile);
        }
    }

}
void UserConfig::AddAnimationBookmark(const char* MoveFileName){
    bool BookMarkExists = false;
    for (int i = 0; i < Databases::BookmarkedDecisionTrees.size(); i++) {
        if (Databases::BookmarkedDecisionTrees[i].c_str() == MoveFileName)
            BookMarkExists = true;
    }
    if (!BookMarkExists) {
        std::fstream BookmarksFile;
        BookmarksFile.open(AnimationBookmarksPath, std::ios::app);
        BookmarksFile << MoveFileName;
        BookmarksFile << "\n";
        BookmarksFile.close();
    }
}

void UserConfig::LoadGraphicKitBookmarks() {
    std::fstream BookmarksFile(GraphicKitBookmarksPath);
    Databases::BookmarkedGraphicKitModels = {};
    if (BookmarksFile.is_open()) {
        while (!BookmarksFile.eof())
        {
            std::string CurrIn;
            getline(BookmarksFile, CurrIn);
            CurrIn.erase(std::remove(CurrIn.begin(), CurrIn.end(), '\n'), CurrIn.cend());
            if (CurrIn != "")
                Databases::BookmarkedGraphicKitModels.push_back(CurrIn);
        }
        BookmarksFile.close();
    }

}

void UserConfig::RemoveGraphicKitBookmark(const char* GraphicKitName) {
    std::vector<std::string> Temp = {};
    for (int i = 0; i < Databases::BookmarkedGraphicKitModels.size(); i++) {
        if (Databases::BookmarkedGraphicKitModels[i].c_str() != GraphicKitName)
            Temp.push_back(Databases::BookmarkedGraphicKitModels[i]);
    }
    remove(GraphicKitBookmarksPath.c_str());
    std::fstream BookmarksFile;
    BookmarksFile.open(GraphicKitBookmarksPath, std::ios::app);
    for (int i = 0; i < Temp.size(); i++) {
        BookmarksFile << Temp[i];
        BookmarksFile << "\n";
    }
    BookmarksFile.close();
    Databases::BookmarkedGraphicKitModels = Temp;
}


void UserConfig::AddGraphicKitBookmark(const char* GraphicKitName) {
    bool BookMarkExists = false;
    std::fstream BookmarksFile;
    BookmarksFile.open(GraphicKitBookmarksPath, std::fstream::in);
    if (BookmarksFile.is_open()) {
        while (!BookmarksFile.eof())
        {
            std::string CurrIn;
            getline(BookmarksFile, CurrIn);
            CurrIn.erase(std::remove(CurrIn.begin(), CurrIn.end(), '\n'), CurrIn.cend());
            std::string MoveFileNameCmp = GraphicKitName;
            if (CurrIn == MoveFileNameCmp)
            {
                BookMarkExists = true;
                break;
            }
        }
        BookmarksFile.close();
    }
    if (!BookMarkExists) {
        BookmarksFile.open(GraphicKitBookmarksPath, std::ios::app);
        BookmarksFile << GraphicKitName;
        BookmarksFile << "\n";
        BookmarksFile.close();
    }
}

