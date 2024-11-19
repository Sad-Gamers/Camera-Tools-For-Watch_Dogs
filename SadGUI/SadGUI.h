#include "GlobalHeaders.h"

class SadGUI
{
public:
	static void ShowCameraTool();
	static void LoadImguiTheme();
	inline static std::string Font;
	inline static bool WindowOpen = true;
	inline static bool ReloadFont;
	inline static const char* AnimationSelectionMode = "Full List";
	inline static const char* GraphicKitSelectionMode = "Full List";
	inline static const char* PointOne = "A";
	inline static const char* PointTwo = "B";
	inline static float MinFOV = 0;
	inline static float MinRoll = -180;
	inline static float MinFocusDistance = 0;
	inline static float MinFStop = 0;
	inline static float MinFocalLength = 0;
	inline static float MaxRoll = 180;
	inline static float MaxFOV = 160;
	inline static float MaxFocusDistance = 100;
	inline static float MaxFStop = 200;
	inline static float MaxFocalLength = 300;
	inline static float MinCameraSpeed = 0;
	inline static float MaxCameraSpeed = 20;
	inline static float MinSlope = 1;
	inline static float MaxSlope = 75;
	inline static float MinSpeed = 0.05f;
	inline static float MaxSpeed = 8;
	inline static float FontSize = 17;
};