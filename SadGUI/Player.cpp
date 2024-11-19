#include "Player.h"
#include "EntityManager.h"

void Player::Initialize() {
	GraphicKitModel = "A_MainCharacters.char01_Aiden";
	Animation = "07_pills/alone/07_alonegenerator";
	LoopAnimation = false;
	HighlightColorStr = "Purple";
	HighlightColor = 5;
	IsImmortal = false;
}

void Player::UpdateAnimation()
{
	uint64_t PlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	EntityManager::PlayAnimation(PlayerEntityId, Animation, LoopAnimation);
}

void Player::StopAnimation()
{
	uint64_t PlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	EntityManager::PlayAnimation(PlayerEntityId,
		"move/decisiontrees/vehicles/pawn_generic_vehicle_approach.move.bin", false);
}

void Player::WearMask()
{
	uint64_t PlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	EntityManager::PlayerActiveScriptMaskControl(PlayerEntityId, 1, 1);
}

void Player::UnMask()
{
	uint64_t PlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	EntityManager::PlayerActiveScriptMaskControl(PlayerEntityId, 1, 0);
}

void Player::UpdateGraphicKitModel() {
	uint64_t PlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	EntityManager::ChangeGraphicKit(PlayerEntityId, GraphicKitModel);
}

void Player::Kill()
{
	uint64_t PlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	EntityManager::KillEntity(PlayerEntityId);
}

void Player::MakeImmortal()
{
	uint64_t PlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	EntityManager::ActivateInvincibility(PlayerEntityId);
}

void Player::RemoveImmortality()
{
	uint64_t PlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	EntityManager::RemoveInvincibility(PlayerEntityId);
}

void Player::Shove()
{
	uint64_t PlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	EntityManager::PlayAnimation(PlayerEntityId,
		"hurt/drvr_ragdoll_collisionhit", false);
}

void Player::StartHighlight()
{
	uint64_t PlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	EntityManager::StopEntityHighlight(PlayerEntityId, 0, 0);
	EntityManager::StartEntityHighlight(PlayerEntityId, HighlightColor, 1);
}

void Player::RemoveHighlight()
{
	uint64_t PlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	EntityManager::StopEntityHighlight(PlayerEntityId, 0, 0);
}