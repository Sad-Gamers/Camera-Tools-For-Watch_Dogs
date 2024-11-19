#pragma once
#include "GlobalHeaders.h"
#define o_TimeOfDay 0x758

class EnvironmentManager
{
public:
	inline static uintptr_t Imagebase;
	static void Initialize();
	static uintptr_t GetEnvironmentEventsManager();
	static uintptr_t GetDynamicEnvironmentManager();

	inline static bool FreezeRain;
	inline static const char* CurrentWeatherPreset;
	inline static int MilitaryTimeHour;
	inline static int MilitaryTimeMinute;
	inline static float TimeOfDay;

	static void IncreaseTimeOfDay(float DeltaTime);
	static void DecreaseTimeOfDay(float DeltaTime);
	static void UpdateTimeOfDay();
	static void SetTimeOfDay();
	static void SetWeatherPreset();
	static uintptr_t ApplySceneParticlePostFx_Detour(uintptr_t a1);

	typedef uintptr_t(*BeginEnvironmentEvent_t)(uintptr_t CEnvironmentEventsManager, int* PresetHash, float Fadein, bool NoTransition);
	inline static BeginEnvironmentEvent_t BeginEnvironmentEvent;

	typedef uintptr_t (*ApplySceneParticlePostFx_t)(uintptr_t);
	inline static ApplySceneParticlePostFx_t ApplySceneParticlePostFx;

	typedef uintptr_t(*CParticleRendererPostFX_t)();
	inline static CParticleRendererPostFX_t CParticleRendererPostFX;

	typedef uintptr_t(*SetScriptedTimeOfDay_t)(uintptr_t CDynamicEnvironmentManager, int Hour, int Minute);
	inline static SetScriptedTimeOfDay_t SetScriptedTimeOfDay;
};