#include "GlobalHeaders.h"

class Monitor
{
public:
	static void MonitorChanges();
	static void ProccessInput();
	inline static ULONGLONG TickCountOnUIHide;
	inline static bool FreeCam;
	inline static bool TimeStop;
	inline static bool SlowMo;
	inline static bool CustomSpeed;
	inline static bool FreezeRain;
	inline static bool GridShading;
	inline static bool HideUI;
	inline static bool UpdateWeatherPreset;
	inline static bool UpdateTimeOfDay;
	inline static bool UpdatePlayerGraphicKit;
	inline static bool UpdatePlayerAnimation;
	inline static bool StopPlayerAnimation;
	inline static bool MakePlayerImmortal;
	inline static bool KillPlayer;
	inline static bool ShovePlayer;
	inline static bool MaskPlayer;
	inline static bool StaticAngle;
	inline static bool UnMaskPlayer;
	inline static bool PlaceActor;
	inline static bool RemoveActor;
	inline static bool UpdateActorGraphicKit;
	inline static bool UpdateActorAnimation;
	inline static bool StopActorAnimation;
	inline static bool ActorNoCollission;
	inline static bool ActorDrawWeapon;
	inline static bool ActorConcealWeapon;
	inline static bool MaskActor;
	inline static bool UnMaskActor;
	inline static bool ReleaseActor;


	inline static bool PlaceFaceLight;
	inline static bool RemoveFaceLight;

	inline static bool PlaceSpotlight;
	inline static bool RemoveSpotlight;

	inline static bool SuperRender;


	inline static bool PlaceAreaLight;
	inline static bool RemoveAreaLight;

	inline static bool PlaceMuzzleFlash;
	inline static bool RemoveMuzzleFlash;

	inline static bool RemoveAllLights;

	inline static bool StartPlayerHighlight;
	inline static bool RemovePlayerHighlight;
	inline static bool UpdateRenderConfig;
	inline static bool RevertRenderConfig;

	inline static bool RestoreControl;
	inline static bool RemoveControl;
	inline static bool RestoreControlEvent;

	inline static bool NoClip;
	inline static bool TeleportToWaypoint;
	inline static bool TeleportToWillisTower;
	inline static bool EnableFelony;
	inline static bool DisableFelony;

};