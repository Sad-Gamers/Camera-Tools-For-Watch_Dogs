#include "CinematicLight.h"
#include "EntityManager.h"
#include "CinematicLightingManager.h"
#include "CameraManager.h"


void CinematicLight::Place(DirectX::XMFLOAT3 *ManagerPosition, 
	DirectX::XMFLOAT3* ManagerRotation, bool MaintainPosition)
{
	if (!MaintainPosition) {
		DirectX::XMFLOAT3 Position = {
			CameraManager::CamPosition.x,
			CameraManager::CamPosition.y,
			CameraManager::CamPosition.z
		};

		DirectX::XMFLOAT3 Rotation = {
		CameraManager::RadiansToDegree(CameraManager::CamRotation.x),
		CameraManager::RadiansToDegree(CameraManager::CamRotation.y),
		CameraManager::RadiansToDegree(CameraManager::CamRotation.z)
		};
		*(DirectX::XMFLOAT3*)(ManagerPosition) = UpdatePosition(Position);
		*(DirectX::XMFLOAT3*)(ManagerRotation) = UpdateRotation(Rotation);
	}
	else 
	{
		DirectX::XMFLOAT3 Position = *(DirectX::XMFLOAT3*)(ManagerPosition);
		DirectX::XMFLOAT3 Rotation = *(DirectX::XMFLOAT3*)(ManagerRotation);
		UpdatePosition(Position);
		UpdateRotation(Rotation);
	}

}


bool CinematicLight::IsPresent(DirectX::XMFLOAT3 Position)
{
	if (Position.z == 0)
		return false;
	else
		return true;
}

DirectX::XMFLOAT3 CinematicLight::UpdatePosition(DirectX::XMFLOAT3 Position)
{
	EntityManager::SetEntityPosition(EntityID, Position.x, Position.y, Position.z);
	return Position;
}

DirectX::XMFLOAT3 CinematicLight::UpdateRotation(DirectX::XMFLOAT3 Rotation)
{
	EntityManager::SetEntityRotation(EntityID, Rotation.x, Rotation.y, Rotation.z);
	return Rotation;
}

void CinematicLight::GetEntityID()
{
	std::cout << EntityID << std::endl;
}
