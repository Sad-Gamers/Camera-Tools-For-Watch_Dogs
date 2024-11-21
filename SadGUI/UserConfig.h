#pragma once
#include "GlobalHeaders.h"

class UserConfig
{
public:
	inline static std::string HotKeyConfigPath;
	inline static std::string HotFixConfigPath;
	inline static std::string RenderConfigPath;
	inline static std::string GUIConfigPath;
	inline static std::string AnimationBookmarksPath;
	inline static std::string GraphicKitBookmarksPath;
	inline static std::string CameraData1Path;
	inline static std::string CameraData2Path;

	static void LoadHotKeys();
	static void LoadGUIConfig();
	static void LoadHotFixConfig();
	static void LoadRenderConfig();
    static void SanatizeHotKeySelection(BYTE SelectedHkey);
    static void SaveAndReloadHotkeys();
    static void SaveRenderConfig();
    static void SaveAndReloadHotFixConfig();
    static void SaveAndReloadGUIConfig();

    static void AddAnimationBookmark(const char* MoveFileName);
    static void RemoveAnimationBookmark(const char* MoveFileName);
    static void LoadAnimationBookmarks();


    static void AddGraphicKitBookmark(const char* GraphicKitName);
    static void RemoveGraphicKitBookmark(const char* GraphicKitName);
    static void LoadGraphicKitBookmarks();

    static void SaveCameraData(int index, DirectX::XMFLOAT3 Position,
    DirectX::XMFLOAT3 Rotation,
    float FieldOfView,
    float FocusDistance,
    float FocalLength,
    float FStop,
    float NearDOF,
    float FarDOF);
    static void LoadCameraData(int index);

    inline static struct HotFixFile {
        bool NoMenuGridShading;
        bool BlowBack;
        bool SlideLocking;
        bool DisableMouseAcceleration;
        bool DisableRotSpeedCap;
        float FOVMultiplier;
    } HotFixesFile, HotFixesFileToSave;

    inline static struct CameraData {
        bool HasData;
        DirectX::XMFLOAT3 Position;
        DirectX::XMFLOAT3 Rotation;
        float FieldOfView;
        float FocusDistance;
        float FocalLength;
        float FStop;
        float NearDOF;
        float FarDOF;
    } CameraData1, CameraData2;

    inline static struct HotKeyFile {
        BYTE GUI;
        BYTE FreeCam;
        BYTE TimeStop;
        BYTE SlowMo;
        BYTE HUD;
        BYTE NoClip;
        BYTE GridShading;
        BYTE Transition;
        BYTE PlayAnim;
    } HotKeyFile, HotKeyFileToSave;

    inline static struct GUIFile {
        float FontSize;
    } GUIFile, GUIFileToSave;
};