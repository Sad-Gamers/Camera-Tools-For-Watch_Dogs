#include "CameraManager.h"
#include "EntityManager.h"
#include "CameraToolMonitor.h"

void CameraManager::Initialize() {
	Imagebase = Misc::Imagebase;
	UpdateCamera = (UpdateCamera_t)(Imagebase + Offsets::UpdateCamera);
	ProccessDepthOfField = (ProccessDepthOfField_t)(Imagebase + Offsets::ProccessDepthOfField);
	GetSceneObjectHandle = (GetSceneObjectHandle_t)(Imagebase + Offsets::GetSceneObjectHandle);
	MH_CreateHook((LPVOID)(Imagebase + Offsets::UpdateCamera), &UpdateCamera_Detour, reinterpret_cast<LPVOID*>(&UpdateCamera));
	MH_CreateHook((LPVOID)(Imagebase + Offsets::ProccessDepthOfField), &ProccessDepthOfField_detour,
		reinterpret_cast<LPVOID*>(&ProccessDepthOfField));
	MH_EnableHook((LPVOID)(Imagebase + Offsets::UpdateCamera));
	MH_EnableHook((LPVOID)(Imagebase + Offsets::ProccessDepthOfField));
	FreeCamInit = false;
	CameraSpeed = 1;
	FieldOfView = 75;
	FocusDistance = 30;
	FocalLength = 300;
	FStop = 40;
	FieldOfView = 75;
	Roll = 0;
	TranSlope = 5;
	FreeCamMode = "Unbounded";
	DOFMode = "Blur Far";
	TransitionCurve = "Linear";
	PI = DirectX::XM_PI;
}

DirectX::XMFLOAT3 CameraManager::GetLookAtCameraAngles(DirectX::XMFLOAT3 oAngles) {
	if (Misc::GetMinStepTime(Misc::GetCPhysWorld()) > 0) {
		if (StaticAngles) {
			DirectX::XMFLOAT3 IdealAngles = {
				(0 + DegreeToRadian(CameraIdealAngles.x)),
				(0 + DegreeToRadian(CameraIdealAngles.y)),
				(0 + DegreeToRadian(CameraIdealAngles.z))
			};
			return IdealAngles;
		}
		else {
			DirectX::XMFLOAT3 IdealAngles = {
				(oAngles.x + DegreeToRadian(CameraIdealAngles.x)),
				(oAngles.y + DegreeToRadian(CameraIdealAngles.y)),
				(oAngles.z + DegreeToRadian(CameraIdealAngles.z))
			};
			return IdealAngles;
		}
	}
	else {
		return oAngles;
	}
}

DirectX::XMFLOAT3 CameraManager::GetLookAtCameraPosition() {

	uint64_t LocalPlayerEntityId = EntityManager::GetLocalPlayerEntityId();
	uint64_t VehicleId = EntityManager::GetCurrentPlayerVehicleEntityId();

	DirectX::XMFLOAT3 CameraPosition;

	if (VehicleId == -1) {
		CameraPosition = {
			EntityManager::GetEntityPosition(LocalPlayerEntityId, 0),
			EntityManager::GetEntityPosition(LocalPlayerEntityId, 1),
			EntityManager::GetEntityPosition(LocalPlayerEntityId, 2)
		};
	}
	else {
		CameraPosition = {
			EntityManager::GetEntityPosition(VehicleId, 0),
			EntityManager::GetEntityPosition(VehicleId, 1),
			EntityManager::GetEntityPosition(VehicleId, 2)
		};
	}

	float uVectorYMagnitude =
		sqrtf(CamDirectionVectorY.x * CamDirectionVectorY.x +
			CamDirectionVectorY.y * CamDirectionVectorY.y +
			CamDirectionVectorY.z * CamDirectionVectorY.z
		);

	float uVectorXMagnitude =
		sqrtf(CamDirectionVectorX.x * CamDirectionVectorX.x +
			CamDirectionVectorX.y * CamDirectionVectorX.y
		);

	DirectX::XMFLOAT3 Ideal2Offset = {
		CamDirectionVectorY.x / uVectorYMagnitude,
		CamDirectionVectorY.y / uVectorYMagnitude,
		CamDirectionVectorY.z / uVectorYMagnitude
	};

	DirectX::XMFLOAT2 Ideal1Offset = {
		CamDirectionVectorX.x / uVectorXMagnitude,
		CamDirectionVectorX.y / uVectorXMagnitude
	};

	CameraPosition.x += (Ideal2Offset.x * CameraIdeal.y)
		+ (Ideal1Offset.x * CameraIdeal.x);

	CameraPosition.y += (Ideal2Offset.y * CameraIdeal.y) +
		(Ideal1Offset.y * CameraIdeal.x);

	CameraPosition.z += (Ideal2Offset.z * CameraIdeal.y) +
		+CameraIdeal.z;

	return CameraPosition;
}

void CameraManager::InitializeLookAtCam() {
	*(BYTE*)(Misc::Imagebase + Offsets::UpdatePlayerLook) = Offsets::oUpdatePlayerLook;
	CameraIdeal = {
		0.0f, -3.5f, 1.1f
	};
	CameraIdealAngles = {
		0.0f, 0.0f, 0.0f
	};
	StaticAngles = false;
	FocusDistance = 50;
	FocalLength = 300;
	FStop = 40;
	FieldOfView = 70;
	FieldOfViewOnActivation = 70;
	Roll = 0;
	DOFMode = "Blur Far";
	NearDOF = false;
	FarDOF = true;
}
void CameraManager::InitializeFreeCam(DirectX::XMFLOAT3 OCamPosition,
	DirectX::XMFLOAT3 OCamRotation, float oFieldOfView) {
	CamPosition = OCamPosition;
	CamRotation = OCamRotation;
	UpdateFreeCamDirectionVector(CamRotation);
	FocusDistance = 30;
	FocalLength = 300;
	FStop = 40;
	TranSlope = 5;
	FieldOfView = RadiansToDegree(oFieldOfView);
	FieldOfViewOnActivation = RadiansToDegree(oFieldOfView);
	Roll = 0;
	DOFMode = "Blur Far";
	NearDOF = false;
	FarDOF = true;
	FreeCamInit = true;
}

uintptr_t CameraManager::UpdateCamera_Detour(uintptr_t CCameraManager, uintptr_t TargetView) {
	if (*(BYTE*)(CCameraManager + 48))
	{
		Monitor::MonitorChanges();


		if (!FreeCam) {
			if (Misc::GetMinStepTime(Misc::GetCPhysWorld()) > 0) {
				float AdjustedFOV = *(float*)(CCameraManager + 108) * FOVMultiplier;
				PreviousAdjustedFOV = *(float*)(CCameraManager + 108);
				*(float*)(CCameraManager + 108) = AdjustedFOV;
			}
			else {
				*(float*)(CCameraManager + 108) = PreviousAdjustedFOV;
			}
		}


		if (FreeCam) {

			if (FieldOfView > 160)
				FieldOfView = 160;

			if (FieldOfView < 0)
				FieldOfView = 0;

			if (Roll >= 180)
				Roll = 180;

			if (Roll <= -180)
				Roll = -180;

			if (CinematicTransition) {
				ProgressCinematicTransition();
				*(float*)(CCameraManager + 84) = CamPosition.x;
				*(float*)(CCameraManager + 88) = CamPosition.y;
				*(float*)(CCameraManager + 92) = CamPosition.z;
				*(float*)(CCameraManager + 96) = CamRotation.x;
				*(float*)(CCameraManager + 100) = CamRotation.y;
				*(float*)(CCameraManager + 104) = CamRotation.z;
				*(float*)(CCameraManager + 108) = DegreeToRadian(FieldOfView);
			}
			else {
				if (FreeCamMode == "Unbounded") {
					if (!FreeCamInit) {
						DirectX::XMFLOAT3 oCamPosition;
						DirectX::XMFLOAT3 oCamRotation;
						float oFieldOfView = *(float*)(CCameraManager + 108) / FOVMultiplier;
						oCamPosition.x = *(float*)(CCameraManager + 84);
						oCamPosition.y = *(float*)(CCameraManager + 88);
						oCamPosition.z = *(float*)(CCameraManager + 92);
						oCamRotation.x = *(float*)(CCameraManager + 96);
						oCamRotation.y = *(float*)(CCameraManager + 100);
						oCamRotation.z = *(float*)(CCameraManager + 104);
						InitializeFreeCam(oCamPosition, oCamRotation, oFieldOfView);
					}
					UpdateFreeCamDirectionVector(CamRotation);
					*(float*)(CCameraManager + 84) = CamPosition.x;
					*(float*)(CCameraManager + 88) = CamPosition.y;
					*(float*)(CCameraManager + 92) = CamPosition.z;
					*(float*)(CCameraManager + 96) = CamRotation.x;
					*(float*)(CCameraManager + 100) = DegreeToRadian(Roll);
					*(float*)(CCameraManager + 104) = CamRotation.z;
					*(float*)(CCameraManager + 108) = DegreeToRadian(FieldOfView);
				}
				else {
					DirectX::XMFLOAT3 oAngles = { *(float*)(CCameraManager + 96), *(float*)(CCameraManager + 100), *(float*)(CCameraManager + 104) };
					DirectX::XMFLOAT3 LookAtAngles = GetLookAtCameraAngles(oAngles);
					UpdateFreeCamDirectionVector(LookAtAngles);
					DirectX::XMFLOAT3 LookAtPosition = GetLookAtCameraPosition();
					*(float*)(CCameraManager + 84) = LookAtPosition.x;
					*(float*)(CCameraManager + 88) = LookAtPosition.y;
					*(float*)(CCameraManager + 92) = LookAtPosition.z;
					*(float*)(CCameraManager + 96) = LookAtAngles.x;
					*(float*)(CCameraManager + 100) = LookAtAngles.y;
					*(float*)(CCameraManager + 104) = LookAtAngles.z;
					*(float*)(CCameraManager + 108) = DegreeToRadian(FieldOfView);
				}
			}

		}
	}
	return UpdateCamera(CCameraManager, TargetView);
}

bool CameraManager::ProccessDepthOfField_detour(uintptr_t* a1, uintptr_t* a2, uintptr_t* a3, uintptr_t a4, uintptr_t a5)
{
	uintptr_t CSceneObjectHandle = GetSceneObjectHandle((Imagebase + Offsets::PostFXDepthOfField), a3 + 10);
	if (FreeCam) {
		*(BYTE*)(CSceneObjectHandle + 16) = 1;
		*(float*)(CSceneObjectHandle + 40) = FocusDistance;
		*(float*)(CSceneObjectHandle + 44) = FocalLength;
		*(float*)(CSceneObjectHandle + 48) = FStop;
		if (NearDOF)
			*(float*)(CSceneObjectHandle + 32) = 1;
		else
			*(float*)(CSceneObjectHandle + 32) = 0;
		if (FarDOF)
			*(float*)(CSceneObjectHandle + 36) = 1;
		else
			*(float*)(CSceneObjectHandle + 36) = 0;
	}

	return ProccessDepthOfField(a1, a2, a3, a4, a5);
}

void CameraManager::UpdateFreeCamDirectionVector(DirectX::XMFLOAT3 Rotations) {
	CamDirectionVectorY.x =
		(-cosf(Rotations.z) * sinf(Rotations.x) * sinf(Rotations.y) -
			sinf(Rotations.z) * cosf(Rotations.y));

	CamDirectionVectorY.y =
		(-sinf(Rotations.z) * sinf(Rotations.x) * sinf(Rotations.y) +
			cosf(Rotations.z) * cosf(Rotations.y));

	CamDirectionVectorY.z = sinf(Rotations.x);

	CamDirectionVectorX.x = (cosf(Rotations.z) * cosf(Rotations.x));
	CamDirectionVectorX.y = (sinf(Rotations.z) * cosf(Rotations.x));
}

void CameraManager::StartCinematicTransition(std::vector<UserConfig::CameraData> CameraDataVector) {
	if (!CameraDataVector[0].HasData || !CameraDataVector[1].HasData) {
		return;
	}
	TranPosDelta = {
		CameraDataVector[0].Position.x - CameraDataVector[1].Position.x,
		CameraDataVector[0].Position.y - CameraDataVector[1].Position.y,
		CameraDataVector[0].Position.z - CameraDataVector[1].Position.z
	};
	TranRotDelta = {
		CameraDataVector[0].Rotation.x - CameraDataVector[1].Rotation.x,
		CameraDataVector[0].Rotation.y - CameraDataVector[1].Rotation.y,
		CameraDataVector[0].Rotation.z - CameraDataVector[1].Rotation.z
	};

	TranDOFDelta = {
		CameraDataVector[0].FocusDistance - CameraDataVector[1].FocusDistance,
		CameraDataVector[0].FocalLength - CameraDataVector[1].FocalLength,
		CameraDataVector[0].FStop - CameraDataVector[1].FStop
	};

	TranFOVDelta = CameraDataVector[0].FieldOfView - CameraDataVector[1].FieldOfView;

	CubicAcceleration = 0;
	CamPosition = CameraDataVector[0].Position;
	CamRotation = CameraDataVector[0].Rotation;
	FocusDistance = CameraDataVector[0].FocusDistance;
	FocalLength = CameraDataVector[0].FocalLength;
	FStop = CameraDataVector[0].FStop;
	FieldOfView = CameraDataVector[0].FieldOfView;
	DestinationCameraPos = CameraDataVector[1].Position;
	DestinationCameraRot = CameraDataVector[1].Rotation;
	DestinationCameraFOV = CameraDataVector[1].FieldOfView;
	DestinationCameraDOF = { CameraDataVector[1].FocusDistance,
		CameraDataVector[1].FocalLength 
	, CameraDataVector[1].FStop };
	CinematicTransition = true;
}

void CameraManager::ProgressCinematicTransition() {

	bool Finished = true;
	float FrameDelta = ImGui::GetIO().DeltaTime;

	if (TransitionCurve == "Cubic") {
		if (!TranslateCinematicTransition_Cubic(CamPosition.x, DestinationCameraPos.x,
			TranPosDelta.x, &CamPosition.x, CubicAcceleration, false, FrameDelta))
			Finished = false;
		if (!TranslateCinematicTransition_Cubic(CamPosition.y, DestinationCameraPos.y,
			TranPosDelta.y, &CamPosition.y, CubicAcceleration, false, FrameDelta))
			Finished = false;
		if (!TranslateCinematicTransition_Cubic(CamPosition.z, DestinationCameraPos.z,
			TranPosDelta.z, &CamPosition.z, CubicAcceleration, false, FrameDelta))
			Finished = false;
		if (!TranslateCinematicTransition_Cubic(CamRotation.x, DestinationCameraRot.x,
			TranRotDelta.x, &CamRotation.x, CubicAcceleration, true, FrameDelta))
			Finished = false;
		if (!TranslateCinematicTransition_Cubic(CamRotation.y, DestinationCameraRot.y,
			TranRotDelta.y, &CamRotation.y, CubicAcceleration, true, FrameDelta))
			Finished = false;
		if (!TranslateCinematicTransition_Cubic(CamRotation.z, DestinationCameraRot.z,
			TranRotDelta.z, &CamRotation.z, CubicAcceleration, true, FrameDelta))
			Finished = false;
		if (!TranslateCinematicTransition_Cubic(FocusDistance, DestinationCameraDOF.x,
			TranDOFDelta.x, &FocusDistance, CubicAcceleration, false, FrameDelta))
			Finished = false;
		if (!TranslateCinematicTransition_Cubic(FocalLength, DestinationCameraDOF.y,
			TranDOFDelta.y, &FocalLength, CubicAcceleration, false, FrameDelta))
			Finished = false;
		if (!TranslateCinematicTransition_Cubic(FStop, DestinationCameraDOF.z,
			TranDOFDelta.z, &FStop, CubicAcceleration, false, FrameDelta))
			Finished = false;
		if (!TranslateCinematicTransition_Cubic(FieldOfView, DestinationCameraFOV,
			TranFOVDelta, &FieldOfView, CubicAcceleration, false, FrameDelta))
			Finished = false;

		CubicAcceleration += (TranSlope / 500 * FrameDelta);

	}
	else
	{
		if (!TranslateCinematicTransition_Linear(CamPosition.x, DestinationCameraPos.x,
			TranPosDelta.x, &CamPosition.x, false, FrameDelta))
				Finished = false;
		if (!TranslateCinematicTransition_Linear(CamPosition.y, DestinationCameraPos.y,
			TranPosDelta.y, &CamPosition.y, false, FrameDelta))
				Finished = false;
		if (!TranslateCinematicTransition_Linear(CamPosition.z, DestinationCameraPos.z,
			TranPosDelta.z, &CamPosition.z, false, FrameDelta))
				Finished = false;
		if (!TranslateCinematicTransition_Linear(CamRotation.x, DestinationCameraRot.x,
			TranRotDelta.x, &CamRotation.x, true, FrameDelta))
				Finished = false;
		if (!TranslateCinematicTransition_Linear(CamRotation.y, DestinationCameraRot.y,
			TranRotDelta.y, &CamRotation.y, true, FrameDelta))
				Finished = false;
		if (!TranslateCinematicTransition_Linear(CamRotation.z, DestinationCameraRot.z,
			TranRotDelta.z, &CamRotation.z, true, FrameDelta))
				Finished = false;
		if (!TranslateCinematicTransition_Linear(FocusDistance, DestinationCameraDOF.x,
			TranDOFDelta.x, &FocusDistance, false, FrameDelta))
				Finished = false;
		if (!TranslateCinematicTransition_Linear(FocalLength, DestinationCameraDOF.y,
			TranDOFDelta.y, &FocalLength, false, FrameDelta))
				Finished = false;
		if (!TranslateCinematicTransition_Linear(FStop, DestinationCameraDOF.z,
			TranDOFDelta.z, &FStop, false, FrameDelta))
				Finished = false;
		if (!TranslateCinematicTransition_Linear(FieldOfView, DestinationCameraFOV,
			TranFOVDelta, &FieldOfView, false, FrameDelta))
			Finished = false;
	}

	CinematicTransition = !Finished;
}


bool CameraManager::TranslateCinematicTransition_Linear(float Origin,
	float Destination, float Delta, float* OriginPtr, bool Angle, float FrameDelta) {

	if (!Angle) {
		if (ComparePositionFp(Origin, Destination))
			return true;
	}
	else
	{
		if (CompareAngleFp(Origin, Destination))
			return true;
	}

	if (Origin > Destination) {
		*OriginPtr -= (TranSlope / 150 * FrameDelta) * abs(Delta);
		return false;
	}
	else if (Origin < Destination) {
		*OriginPtr += (TranSlope / 150 * FrameDelta) * abs(Delta);
		return false;
	}

	return true;

}

bool CameraManager::TranslateCinematicTransition_Cubic(float Origin,
	float Destination, float Delta, float* OriginPtr,
	float Delta2, bool Angle, float FrameDelta) {

	if (!Angle) {
		if (ComparePositionFp(Origin, Destination))
			return true;
	}
	else
	{
		if (CompareAngleFp(Origin, Destination))
			return true;
	}

	if (Origin > Destination) {
		*OriginPtr -= (TranSlope / 150 * FrameDelta) * abs(Delta) + pow(Delta2, 3) * abs(Delta);
		return false;
	}
	else if (Origin < Destination) {
		*OriginPtr += (TranSlope / 150 * FrameDelta) * abs(Delta) + pow(Delta2, 3) * abs(Delta);
		return false;
	}

	return true;
}

void CameraManager::LoadCameraData(int index) {
	if (index == 0) {
		if (!UserConfig::CameraData1.HasData)
			return;
		CamPosition = UserConfig::CameraData1.Position;
		CamRotation = UserConfig::CameraData1.Rotation;
		FocusDistance = UserConfig::CameraData1.FocusDistance;
		FocalLength = UserConfig::CameraData1.FocalLength;
		FStop = UserConfig::CameraData1.FStop;
		FieldOfView = UserConfig::CameraData1.FieldOfView;
	}
	if (index == 1) {
		if (!UserConfig::CameraData2.HasData)
			return;
		CamPosition = UserConfig::CameraData2.Position;
		CamRotation = UserConfig::CameraData2.Rotation;
		FocusDistance = UserConfig::CameraData2.FocusDistance;
		FocalLength = UserConfig::CameraData2.FocalLength;
		FStop = UserConfig::CameraData2.FStop;
		FieldOfView = UserConfig::CameraData2.FieldOfView;
	}
}

float CameraManager::DegreeToRadian(float Degrees) {
	return (Degrees * (PI / 180));
}

float CameraManager::RadiansToDegree(float Radians) {
	return (Radians * (180 / PI));
}

bool CameraManager::ComparePositionFp(float a, float b) {
	float RoundedA = std::round(a / 0.01f) * 0.01f;
	float RoundedB = std::round(b / 0.01f) * 0.01f;
	return (RoundedA == RoundedB);
}

bool CameraManager::CompareAngleFp(float a, float b) {
	float RoundedA = std::round(a / 0.05f) * 0.05f;
	float RoundedB = std::round(b / 0.05f) * 0.05f;
	return (RoundedA == RoundedB);
}