#pragma once
#include "GlobalHeaders.h"

class Player
{
public:
	static void Initialize();
	inline static const char* GraphicKitModel;
	inline static const char* Animation;
	inline static const char* HighlightColorStr;
	inline static int HighlightColor;
	inline static bool LoopAnimation;
	inline static bool IsImmortal;
	inline static bool NoClipMode;
	inline static float NoClipSens;
	inline static DirectX::XMFLOAT3 NoClipPosition;
	inline static DirectX::XMFLOAT3 WaypointPosition;
	inline static DirectX::XMFLOAT3 CamRotation;
	inline static DirectX::XMFLOAT3 CamDirectionVectorY, CamDirectionVectorX;
	inline static float NoClipRotation;
	inline static float PlayerDirectionX;
	inline static float PlayerDirectionY;

	static void BeginNoClip();
	static void UpdateNoClip();
	static void HandleNoClipInput();
	static void EndNoClip();
	static void UpdateNoClipCamDirectionVector();
	static void TeleportToWaypoint();
	static void TeleportToWillisTower();
	static void UpdateAnimation();
	static void StopAnimation();
	static void WearMask();
	static void UnMask();
	static void UpdateGraphicKitModel();
	static void StartHighlight();
	static void RemoveHighlight();
	static void Kill();
	static void Shove();
	static void MakeImmortal();
	static void RemoveImmortality();
};