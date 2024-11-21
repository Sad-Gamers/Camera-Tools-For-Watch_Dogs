#include "Player.h"
#include "EntityManager.h"
#include "CameraToolMonitor.h"

void Player::Initialize() {
	GraphicKitModel = "A_MainCharacters.char01_Aiden";
	Animation = "07_pills/alone/07_alonegenerator";
	LoopAnimation = false;
	HighlightColorStr = "Purple";
	HighlightColor = 5;
	IsImmortal = false;
	NoClipSens = 1.0f;
}

void Player::TeleportToWaypoint() {
	if (WaypointPosition.x != 0 && WaypointPosition.y != 0 && WaypointPosition.z != 0) {
		uint64_t LocalPlayerEntityId = EntityManager::GetLocalPlayerEntityId();
		EntityManager::SetEntityPosition(LocalPlayerEntityId, WaypointPosition.x, WaypointPosition.y, WaypointPosition.z);
	}
}

void Player::TeleportToWillisTower() {
	uint64_t LocalPlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	EntityManager::SetEntityPosition(LocalPlayerEntityId, 255.0f, -97.0f, 511.0f);
	EntityManager::SetEntityRotation(LocalPlayerEntityId, 0.0f, 0.0f, 180.0f);
}

void Player::BeginNoClip() {
	uint64_t LocalPlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	MakeImmortal();
	EntityManager::SetPhysicsEnabled(LocalPlayerEntityId, false);
	NoClipPosition.x = EntityManager::GetEntityPosition(LocalPlayerEntityId, 0);
	NoClipPosition.y = EntityManager::GetEntityPosition(LocalPlayerEntityId, 1);
	NoClipPosition.z = EntityManager::GetEntityPosition(LocalPlayerEntityId, 2);
	NoClipMode = true;
	EntityManager::PlayAnimation(LocalPlayerEntityId, "locomotion/drvr_swimming_idle", true);
}

void Player::EndNoClip() {
	uint64_t LocalPlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	if(!Monitor::MakePlayerImmortal)
		RemoveImmortality();
	EntityManager::SetPhysicsEnabled(LocalPlayerEntityId, true);
	NoClipMode = false;
	Player::StopAnimation();
}

void Player::UpdateNoClip() {
	HandleNoClipInput();
	uint64_t LocalPlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	EntityManager::SetEntityPosition(LocalPlayerEntityId, NoClipPosition.x, NoClipPosition.y, NoClipPosition.z);
	EntityManager::SetEntityRotation(LocalPlayerEntityId, 0, 0, NoClipRotation);
}

void Player::HandleNoClipInput() {
	UpdateNoClipCamDirectionVector();
	NoClipRotation = CamRotation.z * (180 / DirectX::XM_PI);
	NoClipPosition.x += 0.075f * NoClipSens *  CamDirectionVectorY.x * PlayerDirectionY;
	NoClipPosition.y += 0.075f * NoClipSens * CamDirectionVectorY.y * PlayerDirectionY;
	NoClipPosition.z += 0.075f * NoClipSens * CamDirectionVectorY.z * PlayerDirectionY;
	NoClipPosition.x += 0.075f * NoClipSens * CamDirectionVectorX.x * PlayerDirectionX;
	NoClipPosition.y += 0.075f * NoClipSens * CamDirectionVectorX.y * PlayerDirectionX;
	NoClipPosition.z += 0.075f * NoClipSens * CamDirectionVectorX.z * PlayerDirectionX;
}

void Player::UpdateNoClipCamDirectionVector() {
	CamDirectionVectorY.x =
		(-cosf(CamRotation.z) * sinf(CamRotation.x) * sinf(CamRotation.y) -
			sinf(CamRotation.z) * cosf(CamRotation.y));

	CamDirectionVectorY.y =
		(-sinf(CamRotation.z) * sinf(CamRotation.x) * sinf(CamRotation.y) +
			cosf(CamRotation.z) * cosf(CamRotation.y));

	CamDirectionVectorY.z = sinf(CamRotation.x);

	CamDirectionVectorX.x = (cosf(CamRotation.z) * cosf(CamRotation.x));
	CamDirectionVectorX.y = (sinf(CamRotation.z) * cosf(CamRotation.x));
}

void Player::UpdateAnimation()
{
	uint64_t PlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	EntityManager::PlayAnimation(PlayerEntityId, Animation, LoopAnimation);
}

void Player::StopAnimation()
{
	uint64_t PlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	EntityManager::StopAnimation(PlayerEntityId);
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