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
	MilitaryTimeHour = 0;
	MilitaryTimeMinute = 0;
}

uintptr_t EnvironmentManager::GetEnvironmentEventsManager() {
	return ((*(uintptr_t*)((Imagebase + Offsets::CEnvironmentEventsManager)) + 0x0));
}

uintptr_t EnvironmentManager::GetDynamicEnvironmentManager() {
	return ((*(uintptr_t*)((*(uintptr_t*)(Imagebase + Offsets::CDynamicEnvironmentManager)) + 0x8) + 0x0));
}

void EnvironmentManager::SetTimeOfDay() {
	if (GetDynamicEnvironmentManager()) {
		SetScriptedTimeOfDay(GetDynamicEnvironmentManager(), MilitaryTimeHour, MilitaryTimeMinute);
	}
}

void EnvironmentManager::UpdateTimeOfDay() {
	if (GetDynamicEnvironmentManager()) {
		float Time = *(float*)(GetDynamicEnvironmentManager() + 0x758) / 3600.0f;
		float Hour = std::floor(Time);
		float Minute = (Time - Hour) * 60.0f;
		MilitaryTimeHour = Hour;
		MilitaryTimeMinute = Minute;
	}
}

void EnvironmentManager::IncreaseTimeOfDay(float DeltaTime) {
	if (GetDynamicEnvironmentManager()) {
		float Time = *(float*)(GetDynamicEnvironmentManager() + 0x758);
		Time += 600.0f * DeltaTime;
		*(float*)(GetDynamicEnvironmentManager() + 0x758) = Time;
	}
	UpdateTimeOfDay();
}

void EnvironmentManager::DecreaseTimeOfDay(float DeltaTime) {
	if (GetDynamicEnvironmentManager()) {
		float Time = *(float*)(GetDynamicEnvironmentManager() + 0x758);
		Time -= 600.0f * DeltaTime;
		*(float*)(GetDynamicEnvironmentManager() + 0x758) = Time;
	}
	UpdateTimeOfDay();
}

void EnvironmentManager::SetWeatherPreset() {
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


