#pragma once
#include "GlobalHeaders.h"

class Offsets
{
public:
	static int CheckGameVersion();
	static bool Initialize();
	inline static uintptr_t UpdateCamera;
	inline static uintptr_t ProccessDepthOfField;
	inline static uintptr_t PostFXDepthOfField;
	inline static uintptr_t GetSceneObjectHandle;
	inline static uintptr_t DepthOfFieldCondition;
	inline static uintptr_t SetEntityRotation;
	inline static uintptr_t SetEntityPosition;
	inline static uintptr_t GetEntityPosition;
	inline static uintptr_t RequestDominoAnimationState;
	inline static uintptr_t ActivateInvincibility;
	inline static uintptr_t RemoveInvincibility;
	inline static uintptr_t ChangeGraphicKitModel;
	inline static uintptr_t SetPhysicsEnabled;
	inline static uintptr_t AgentDrawWeapon;
	inline static uintptr_t PlayerActiveScriptMaskControl;
	inline static uintptr_t PlayerIdHelpers;
	inline static uintptr_t SendDamageToEntity;
	inline static uintptr_t SpawnEntityFromArcheType;
	inline static uintptr_t RemoveEntity;
	inline static uintptr_t EntitySystem;
	inline static uintptr_t StartEntityHighlight;
	inline static uintptr_t StopEntityHighlight;
	inline static uintptr_t GetCurrentVehicleEntityId;
	inline static uintptr_t SetScriptedTimeOfDay;
	inline static uintptr_t BeginEnvironmentEvent;
	inline static uintptr_t CEnvironmentEventsManager;
	inline static uintptr_t CDynamicEnvironmentManager;
	inline static uintptr_t ApplySceneParticlePostFx;
	inline static uintptr_t FileOpen;
	inline static uintptr_t FileClose;
	inline static uintptr_t FileOpenFromPathId;
	inline static uintptr_t CFileManager;
	inline static uintptr_t GridShadingManager;
	inline static uintptr_t GridShadingOnPause;
	inline static uintptr_t SetGridShading;
	inline static uintptr_t BuildNomadString;
	inline static uintptr_t UpdateAnimations;
	inline static uintptr_t LoadingState;
	inline static uintptr_t GetMinStepTime;
	inline static uintptr_t SendShowOrHideAllUIEvent;
	inline static uintptr_t GetCRCFromString;
	inline static uintptr_t CPhysWorld;
	inline static uintptr_t InputListener;
	inline static uintptr_t GPSConfigInit;
	inline static uintptr_t OnlineState;
	inline static uintptr_t CResourceManager;
	inline static uintptr_t LoadDep;
	inline static uintptr_t RenderConfig;
	inline static uintptr_t PostAnimUpdateWrapper;
	inline static uintptr_t UnkPhysComponentWrapper;
	inline static uintptr_t PostAnimUpdate;
	inline static uintptr_t GetBulletsInClip;
	inline static uintptr_t UpdateWeaponStatus;
	inline static uintptr_t HasItemInMainHand;
	inline static uintptr_t GetEquippedWeaponGrip;
	inline static uintptr_t WeaponMechanicComponent;
	inline static uintptr_t PopPlayerActionMap;
	inline static uintptr_t GetNumberOfPlayers;
	inline static uintptr_t UpdateMouseCameraLook;
	inline static uintptr_t UpdatePlayerLook;
	inline static BYTE oUpdatePlayerLook;
	inline static BYTE StopPlayerAnimation;
	inline static BYTE ResumePlayerAnimation;
	inline static BYTE ForceDOF;
	inline static BYTE ReleaseDOF;
};