#pragma once
#include "GlobalHeaders.h"

class Player
{
public:
	static void Initialize();
	inline static const char* GraphicKitModel;
	inline static const char* Animation;
	inline static const char* HighlightColorStr;
	inline static int HighlightColor;
	inline static bool LoopAnimation;
	inline static bool IsImmortal;

	static void UpdateAnimation();
	static void StopAnimation();
	static void WearMask();
	static void UnMask();
	static void UpdateGraphicKitModel();
	static void StartHighlight();
	static void RemoveHighlight();
	static void Kill();
	static void Shove();
	static void MakeImmortal();
	static void RemoveImmortality();
};