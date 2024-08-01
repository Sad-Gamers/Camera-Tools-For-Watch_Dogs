#pragma once
#include "GlobalHeaders.h"


class CinematicLight
{
public:
	uint64_t EntityID;
	bool IsPresent(DirectX::XMFLOAT3 Position);
	void Place(DirectX::XMFLOAT3* ManagerPosition,
		DirectX::XMFLOAT3* ManagerRotation, bool MaintainPosition);
	DirectX::XMFLOAT3 UpdatePosition(DirectX::XMFLOAT3 Position);
	DirectX::XMFLOAT3 UpdateRotation(DirectX::XMFLOAT3 Position);
	CinematicLight() {
		EntityID = 0;
	}
	CinematicLight(uint64_t ID) {
		EntityID = ID;
	}
};