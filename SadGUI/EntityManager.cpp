#include "EntityManager.h"

void EntityManager::Initialize() {
	Imagebase = Misc::Imagebase;
	GetCurrentVehicleEntityId = (GetCurrentVehicleEntityId_t)(Imagebase + Offsets::GetCurrentVehicleEntityId);
	GetEntityPosition = (GetEntityPosition_t)(Imagebase + Offsets::GetEntityPosition);
	SetEntityRotation = (SetEntityRotation_t)(Imagebase + Offsets::SetEntityRotation);
	SetEntityPosition = (SetEntityPosition_t)(Imagebase + Offsets::SetEntityPosition);
	SetPhysicsEnabled = (SetPhysicsEnabled_t)(Imagebase + Offsets::SetPhysicsEnabled);
	RemoveEntity = (RemoveEntity_t)(Imagebase + Offsets::RemoveEntity);
	AgentDrawWeapon = (AgentDrawWeapon_t)(Imagebase + Offsets::AgentDrawWeapon);
	StartEntityHighlight = (StartEntityHighlight_t)(Imagebase + Offsets::StartEntityHighlight);
	StopEntityHighlight = (StopEntityHighlight_t)(Imagebase + Offsets::StopEntityHighlight);
	SpawnEntityFromArchetype = (SpawnEntityFromArchetype_t)(Imagebase + Offsets::SpawnEntityFromArcheType);
	SendDamageToEntity = (SendDamageToEntity_t)(Imagebase + Offsets::SendDamageToEntity);
	PlayerActiveScriptMaskControl = (PlayerActiveScriptMaskControl_t)(Imagebase + Offsets::PlayerActiveScriptMaskControl);
	RequestDominoAnimationState = (RequestDominoAnimationState_t)(Imagebase + Offsets::RequestDominoAnimationState);
	ActivateInvincibility = (ActivateInvincibility_t)(Imagebase + Offsets::ActivateInvincibility);
	RemoveInvincibility = (ActivateInvincibility_t)(Imagebase + Offsets::RemoveInvincibility);
	ChangeGraphicKitModel = (ChangeGraphicKitModel_t)(Imagebase + Offsets::ChangeGraphicKitModel);
}

uint64_t EntityManager::GetCurrentPlayerVehicleEntityId() {
	uint64_t VehicleId = 0;
	uint64_t PlayerId = GetLocalPlayerEntityId();
	GetCurrentVehicleEntityId(&VehicleId, PlayerId);
	return VehicleId;
}

uint64_t EntityManager::GetLocalPlayerEntityId() {

	uintptr_t PlayerIdHelpers = **(uintptr_t**)*(uintptr_t*)(Imagebase + Offsets::PlayerIdHelpers);
	if (PlayerIdHelpers)
		return **(uintptr_t**)(*(uintptr_t*)(PlayerIdHelpers + 8) + 16);
	else
		return 0;
}

void EntityManager::PlayAnimation(uint64_t TargetEntity, const char* Anim, bool Looping) {
	if (TargetEntity) {
		std::string AnimationName = Anim;
		std::string FullPath = "move/decisiontrees/" + AnimationName + ".move.bin";
		RequestDominoAnimationState(TargetEntity, FullPath.c_str(), Looping, 0, -1);
	}
}

void EntityManager::StopAnimation(uint64_t TargetEntity) {
	if (TargetEntity) 
		RequestDominoAnimationState(TargetEntity, "move/decisiontrees/07_pills/alone/07_alonepickup.move.bin", false, 0, -1);
}

void EntityManager::ChangeGraphicKit(uint64_t TargetEntity, const char* Model) {
	if (TargetEntity) {
		uint64_t ModelNomadStringPtr = 0;
		uint64_t Dummy = 0;
		Misc::MakeNomadString(&ModelNomadStringPtr, Model);
		ChangeGraphicKitModel(&Dummy, TargetEntity, &Dummy, &ModelNomadStringPtr);
	}
}

void EntityManager::KillEntity(uint64_t TargetEntity) {
	if (TargetEntity)
		SendDamageToEntity(TargetEntity, 0, 16, 100, 0);
}

void EntityManager::DeleteEntity(uint64_t TargetEntity) {
	if (TargetEntity)
		RemoveEntity(GetEntitySystem(), TargetEntity);
}

uint64_t EntityManager::SpawnEntity(uint64_t* ReturnID, const char* Archetype, DirectX::XMFLOAT3 Position, DirectX::XMFLOAT3 Rotation) {
	uint64_t ArchetypeNomadStringPtr = 0;
	Misc::MakeNomadString(&ArchetypeNomadStringPtr, Archetype);
	return SpawnEntityFromArchetype(ReturnID, &ArchetypeNomadStringPtr,
		Position.x, Position.y, Position.z,
		Rotation.x, Rotation.y, Rotation.z);
}

uintptr_t EntityManager::GetEntitySystem() {
	return ((*(uintptr_t*)((Imagebase + Offsets::EntitySystem)) + 0x0));
}