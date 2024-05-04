#pragma once
#include "GlobalHeaders.h"

class Actor
{
public:
	static void Initialize();

	inline static DirectX::XMFLOAT3 Position;
	inline static DirectX::XMFLOAT3 Rotation;
	inline static uint64_t ID;
	inline static const char* GraphicKitModel;
	inline static const char* Animation;
	inline static bool LoopAnimation;
	inline static bool NoCollision;
	inline static bool Release;

	static void Place();
	static void Remove();
	static bool IsPresent();
	static void UpdatePosition();
	static void UpdateRotation();
	static void UpdateGraphicKitModel();
	static void Draw();
	static void Holster();
	static void UpdateAnimation();
	static void StopAnimation();
	static void WearMask();
	static void UnMask();
};