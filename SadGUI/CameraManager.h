#pragma once
#include "GlobalHeaders.h"
#include "UserConfig.h"


class CameraManager
{
public:
	inline static uintptr_t Imagebase;
	static void Initialize();

	inline static DirectX::XMFLOAT3 CamPosition;
	inline static DirectX::XMFLOAT3 CamDirectionVectorX;
	inline static DirectX::XMFLOAT3 CamDirectionVectorY;
	inline static DirectX::XMFLOAT3 CamRotation;
	inline static DirectX::XMFLOAT3 CameraIdeal;
	inline static DirectX::XMFLOAT3 CameraIdealAngles;
	inline static DirectX::XMFLOAT3 DestinationCameraPos;
	inline static DirectX::XMFLOAT3 DestinationCameraDOF;
	inline static DirectX::XMFLOAT3 DestinationCameraRot;
	inline static DirectX::XMFLOAT3 TranPosDelta;
	inline static DirectX::XMFLOAT3 TranRotDelta;
	inline static DirectX::XMFLOAT3 TranDOFDelta;
	inline static float TranFOVDelta;
	inline static float DestinationCameraFOV;
	inline static float TranSlope;
	inline static float CubicAcceleration;
	inline static bool CinematicTransition;
	inline static bool StaticAngles;
	inline static float FieldOfView, Roll;
	inline static float FocusDistance, FocalLength, FStop;
	inline static bool NearDOF, FarDOF; 
	inline static bool FreeCam, FreeCamInit, FollowCam;
	inline static float PI;
	inline static float FOVMultiplier;
	inline static float PreviousAdjustedFOV;
	inline static float CameraSpeed;
	inline static const char* FreeCamMode;
	inline static const char* DOFMode;
	inline static const char* TransitionCurve;

	typedef uintptr_t(*UpdateCamera_t)(uintptr_t CCameraManager, uintptr_t TargetView);
	inline static UpdateCamera_t UpdateCamera;

	typedef uintptr_t(*GetSceneObjectHandle_t)(uintptr_t, uintptr_t* CSceneObjectContainer);
	inline static GetSceneObjectHandle_t GetSceneObjectHandle;
	
	typedef bool (*ProccessDepthOfField_t)(uintptr_t*, uintptr_t*, uintptr_t*, uintptr_t, uintptr_t);
	inline static ProccessDepthOfField_t ProccessDepthOfField;

	static void InitializeFreeCam(DirectX::XMFLOAT3 OCamPosition, 
		DirectX::XMFLOAT3 OCamRotation, float oFieldOfView);

	static void UpdateFreeCamDirectionVector(DirectX::XMFLOAT3 Rotations);

	static void InitializeLookAtCam();

	static DirectX::XMFLOAT3 GetLookAtCameraPosition();
	static DirectX::XMFLOAT3 GetLookAtCameraAngles(DirectX::XMFLOAT3 oAngles);

	static bool ProccessDepthOfField_detour(uintptr_t* a1, uintptr_t* a2, uintptr_t* a3, uintptr_t a4, uintptr_t a5);

	static uintptr_t UpdateCamera_Detour(uintptr_t CCameraManager, uintptr_t TargetView);

	static void ProgressCinematicTransition();
	static bool TranslateCinematicTransition_Cubic(float Origin,
		float Destination, float Delta, float* OriginPtr, float Delta2, bool Angle, float FrameDelta);
	static bool TranslateCinematicTransition_Linear(float Origin,
		float Destination, float Delta, float* OriginPtr, bool Angle, float FrameDelta);
	static bool ComparePositionFp(float a, float b);
	static bool CompareAngleFp(float a, float b);
	static void StartCinematicTransition(std::vector<UserConfig::CameraData> CameraDataVector);
	static float DegreeToRadian(float Degrees);
	static float RadiansToDegree(float Radians);
	static void LoadCameraData(int index);
};