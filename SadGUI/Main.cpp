#include "Main.h"
#include "DXHook.h"
#include "Actor.h"
#include "Player.h"
#include "RenderConfig.h"
#include "Databases.h"
#include "CameraManager.h"
#include "EntityManager.h"
#include "EnvironmentManager.h"
#include "FileManager.h"
#include "GridShadingManager.h"
#include "ResourceManager.h"
#include "CameraToolMonitor.h"
#include "CinematicLightingManager.h"
#include "SlideAnimations.h"
#include "UserConfig.h"
#include "Offsets.h"

void Main::Initialize() {
	Misc::Imagebase = (uintptr_t)GetModuleHandleA("Disrupt_b64.dll");
	HMODULE hModule = GetModuleHandleA("Disrupt_b64.dll");
	DWORD WINAPI InstMainThread(LPVOID lpParam);
	CreateThread(0, 0, InstMainThread, hModule, 0, 0);

}

DWORD WINAPI InstMainThread(LPVOID lpParam)
{
	Main* inst = (Main*)lpParam;
	inst->MainThread();
	return 0;
}

void Main::MainThread() {
	bool KnownVersion = Offsets::Initialize();
	if (!KnownVersion)
		return;
	Misc::Initialize();
	DXHook::Initialize();
	Databases::Initialize();
	CameraManager::Initialize();
	EntityManager::Initialize();
	EnvironmentManager::Initialize();
	FileManager::Initialize();
	GridShadingManager::Initialize();
	ResourceManager::Initialize();
	RenderConfig::InitializeSuperRenderingPreset();
	Actor::Initialize();
	Player::Initialize();
	Player::Initialize();
	SlideAnimations::Initialize();
	CinematicLightingManager::InitializeCinematicLights();
	UserConfig::LoadHotKeys();
	UserConfig::LoadHotFixConfig();
}