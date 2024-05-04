#pragma once
#include "GlobalHeaders.h"

class GridShadingManager
{
public:
	static void Initialize();
	inline static bool GridShading;

	typedef uintptr_t(*SetGridShading_t)(uintptr_t CGridShadingManager, int CStringID, bool, float);
	inline static SetGridShading_t SetGridShading;

	static uintptr_t GetGridShadingManager();
	static void DisableMenuGridShading(bool State);
	static void EnableGridShading(bool EnabledState);
};