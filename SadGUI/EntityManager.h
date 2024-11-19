#pragma once
#include "GlobalHeaders.h"


class EntityManager
{
public:
	inline static uintptr_t Imagebase;
	static void Initialize();
	static uint64_t GetLocalPlayerEntityId();
	static uint64_t GetEntitySystem();
	static uint64_t GetCurrentPlayerVehicleEntityId();

	static void PlayAnimation(uint64_t TargetEntity, const char* Anim, bool Looping);
	static void StopAnimation(uint64_t TargetEntity);
	static void ChangeGraphicKit(uint64_t TargetEntity, const char* Model);
	static uint64_t SpawnEntity(uint64_t* ReturnID, const char* Archetype,  DirectX::XMFLOAT3 Position, DirectX::XMFLOAT3 Rotation);
	static void DeleteEntity(uint64_t TargetEntity);
	static void KillEntity(uint64_t TargetEntity);

	typedef uintptr_t (*SetEntityRotation_t)(uintptr_t EntityId, float RotX, float RotY, float RotZ);
	inline static SetEntityRotation_t SetEntityRotation;

	typedef uintptr_t (*GetCurrentVehicleEntityId_t)(uintptr_t*, uintptr_t PawnId);
	inline static GetCurrentVehicleEntityId_t GetCurrentVehicleEntityId;

	typedef uintptr_t(*SetEntityPosition_t)(uintptr_t EntityId, float PosX, float PosY, float PosZ);
	inline static SetEntityPosition_t SetEntityPosition;

	typedef float (*GetEntityPosition_t)(uintptr_t TargetEntity, int Axis);
	inline static GetEntityPosition_t GetEntityPosition;

	typedef float (*SetPhysicsEnabled_t)(uintptr_t TargetEntity, bool Collisionable);
	inline static SetPhysicsEnabled_t SetPhysicsEnabled;

	typedef float (*AgentDrawWeapon_t)(uintptr_t TargetEntity, int);
	inline static AgentDrawWeapon_t AgentDrawWeapon;

	typedef float (*SendDamageToEntity_t)(uintptr_t TargetEntity, uintptr_t DamageSource, int DamageType, float DamageLevel, int DamageLocation);
	inline static SendDamageToEntity_t SendDamageToEntity;

	typedef float (*PlayerActiveScriptMaskControl_t)(uintptr_t TargetEntity, int, int);
	inline static PlayerActiveScriptMaskControl_t PlayerActiveScriptMaskControl;

	typedef uint64_t (*RequestDominoAnimationState_t)(uint64_t TargetEntity, const char* Anim, bool Looping, int Index, uint64_t anchorEntity);
	inline static RequestDominoAnimationState_t RequestDominoAnimationState;

	typedef uint64_t (*ActivateInvincibility_t)(uint64_t TargetEntity);
	inline static ActivateInvincibility_t ActivateInvincibility;

	typedef uint64_t(*RemoveInvincibility_t)(uint64_t TargetEntity);
	inline static RemoveInvincibility_t RemoveInvincibility;

	typedef uint64_t(*RemoveEntity_t)(uint64_t CEntitySystem, uint64_t TargetEntity);
	inline static RemoveEntity_t RemoveEntity;

	typedef uint64_t (*ChangeGraphicKitModel_t)(uint64_t*, uint64_t Entity, uint64_t* Collection, uint64_t* Model);
	inline static ChangeGraphicKitModel_t ChangeGraphicKitModel;

	typedef uint64_t(*StartEntityHighlight_t)(uint64_t TargetEntity, int ColorID, int);
	inline static StartEntityHighlight_t StartEntityHighlight;

	typedef uint64_t(*StopEntityHighlight_t)(uint64_t TargetEntity, int, int);
	inline static StopEntityHighlight_t StopEntityHighlight;

	typedef uint64_t (*SpawnEntityFromArchetype_t)(uint64_t*, uint64_t* Arcchetype, 
		float PosX, float PosY, float PosZ, float RotX, float RotY, float RotZ);
	inline static SpawnEntityFromArchetype_t SpawnEntityFromArchetype;

};