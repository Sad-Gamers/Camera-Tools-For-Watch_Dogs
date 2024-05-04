#include "Databases.h"
#include "EnvironmentManager.h"

void EnvironmentManager::Initialize() {
	Imagebase = Misc::Imagebase;
	BeginEnvironmentEvent = (BeginEnvironmentEvent_t)(Imagebase + Offsets::BeginEnvironmentEvent);
	SetScriptedTimeOfDay = (SetScriptedTimeOfDay_t)(Imagebase + Offsets::SetScriptedTimeOfDay);
	ApplySceneParticlePostFx = (ApplySceneParticlePostFx_t)(Imagebase + Offsets::ApplySceneParticlePostFx);
	MH_CreateHook((LPVOID)(Imagebase + Offsets::ApplySceneParticlePostFx), &ApplySceneParticlePostFx_Detour,
		reinterpret_cast<LPVOID*>(&ApplySceneParticlePostFx));
	MH_EnableHook((LPVOID)(Imagebase + Offsets::ApplySceneParticlePostFx));
	FreezeRain = false;
	CurrentWeatherPreset = "Clear";
	StandardTimeHour = 7;
	StandardTimeMinute = 45;
	MilitaryTimeHour = 7;
	MilitaryTimeMinute = 45;
	StandardTimeFormat = "AM";
}

uintptr_t EnvironmentManager::GetEnvironmentEventsManager() {
	return ((*(uintptr_t*)((Imagebase + Offsets::CEnvironmentEventsManager)) + 0x0));
}

uintptr_t EnvironmentManager::GetDynamicEnvironmentManager() {
	return ((*(uintptr_t*)((*(uintptr_t*)(Imagebase + Offsets::CDynamicEnvironmentManager)) + 0x8) + 0x0));
}

void EnvironmentManager::UpdateTimeOfDay() {
	if (GetDynamicEnvironmentManager()) {
		SetScriptedTimeOfDay(GetDynamicEnvironmentManager(), MilitaryTimeHour, MilitaryTimeMinute);
	}
}

void EnvironmentManager::UpdateWeatherPreset() {
	int PresetHash = Misc::GetCRCFromString(CurrentWeatherPreset);
	if (GetEnvironmentEventsManager()) {
		BeginEnvironmentEvent(GetEnvironmentEventsManager(), &PresetHash, 0, true);
	}
}

uintptr_t EnvironmentManager::ApplySceneParticlePostFx_Detour(uintptr_t a1) {
	uintptr_t Return = ApplySceneParticlePostFx(a1);
	if (FreezeRain) {
		float* v3; 
		v3 = *(float**)(a1 + 480);
		*((float*)v3 + 418) = 0.0f;
	}
	return Return;
}


