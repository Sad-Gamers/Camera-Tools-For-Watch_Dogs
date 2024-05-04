#pragma once
#include "GlobalHeaders.h"

class Databases
{
public:
	static void Initialize();
	inline static std::vector<const char*> GraphicKitModels;
	inline static std::vector<const char*> SelectionModes;
	inline static std::vector<const char*> DecisionTrees;
	inline static std::vector<std::string> BookmarkedDecisionTrees;
	inline static std::vector<std::string> BookmarkedGraphicKitModels;
	inline static std::vector<const char*> EnvironmentPresets;
	inline static std::vector<const char*> HighlightColors;
	inline static std::vector<const char*> FreeCamModes;
	inline static std::vector<const char*> DepthOfFieldModes;
	inline static std::vector<const char*> StandardTimes;
	inline static std::vector<const char*> CinematicLightTypes;
	inline static std::vector<const char*> HotKeys;
	inline static std::vector<const char*> CameraPoints;
	inline static std::vector<const char*> TransitionCurves;
	inline static std::vector<BYTE> HotKeyCodes;
};