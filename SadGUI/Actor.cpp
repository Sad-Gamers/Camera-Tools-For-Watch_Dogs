#include "Actor.h"
#include "CameraToolMonitor.h"
#include "EntityManager.h"

void Actor::Initialize() {
	ID = 0;
	Position = { 0, 0, 0 };
	Rotation = { 0, 0, 0 };
	GraphicKitModel = "A_MainCharacters.char01_Aiden";
	Animation = "07_pills/alone/07_alonegenerator";
	LoopAnimation = false;
	NoCollision = false;
}

void Actor::Place() 
{
	if (ID)
		Remove();
		uint64_t LocalPlayerEntityId = EntityManager::GetLocalPlayerEntityId();
		Position = {
			EntityManager::GetEntityPosition(LocalPlayerEntityId, 0),
			EntityManager::GetEntityPosition(LocalPlayerEntityId, 1),
			EntityManager::GetEntityPosition(LocalPlayerEntityId, 2)
		};
		Rotation = { 0, 0, 0 };
		EntityManager::SpawnEntity(&ID, "{B62A7643-AE95-4F94-BAEE-35224C45C373}", Position, Rotation);
		UpdatePosition();
		UpdateRotation();
		EntityManager::SetPhysicsEnabled(ID, 1);
}

void Actor::Remove()
{
	Position = { 0, 0, 0 };
	Rotation = { 0, 0, 0 };
	EntityManager::DeleteEntity(ID);
	ID = 0;
	NoCollision = false;
	Monitor::ActorNoCollission = false;
	UpdatePosition();
	UpdateRotation();
}

bool Actor::IsPresent()
{
	if (ID == 0)
		return false;
	else
		return true;
}

void Actor::UpdatePosition()
{
	if(!Release)
		EntityManager::SetEntityPosition(ID, Position.x, Position.y, Position.z);
}

void Actor::UpdateRotation()
{
	if (!Release)
		EntityManager::SetEntityRotation(ID, Rotation.x, Rotation.y, Rotation.z);
}

void Actor::Draw()
{
	EntityManager::AgentDrawWeapon(ID, 1);
}

void Actor::Holster()
{
	EntityManager::AgentDrawWeapon(ID, 0);
}

void Actor::UpdateAnimation()
{
	EntityManager::PlayAnimation(ID, Animation, LoopAnimation);
}

void Actor::StopAnimation()
{
	EntityManager::PlayAnimation(ID,
		"move/decisiontrees/vehicles/pawn_generic_vehicle_approach.move.bin", false);
}


void Actor::WearMask()
{
	EntityManager::PlayerActiveScriptMaskControl(ID, 1, 1);
}

void Actor::UnMask()
{
	EntityManager::PlayerActiveScriptMaskControl(ID, 1, 0);
}

void Actor::UpdateGraphicKitModel() {
	EntityManager::ChangeGraphicKit(ID, GraphicKitModel);
}
