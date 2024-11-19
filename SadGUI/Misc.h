#pragma once
#include "GlobalHeaders.h"

#define o_MouseDeltaY 0x90
#define o_MouseDeltaX 0x94
#define o_MouseSensY 0x124
#define o_MouseSensX 0x120

class Misc
{
public:
	inline static uintptr_t Imagebase;
	inline static bool SlowMo, TimeStop, CustomSpeed;
	inline static bool HideUI;
	static void Initialize();
	static void RemoveVMProtect();
	static void DummyReturn();
	static float GetMinStepTimeMacro();
	inline static float MouseDeltaX;
	inline static float MouseDeltaY;
	inline static float SpeedMultiplier;
	inline static bool StopFrameJobs;
	inline static bool DisableMouseAcceleration;
	inline static bool DisableRotSpeedCap;
	inline static ULONGLONG TickCountOnFrameJobStop;

	static void DisableInputListening(bool State);

	typedef uintptr_t (*LoadMissionData_t)(int, uintptr_t*, uintptr_t*, uintptr_t*);
	inline static LoadMissionData_t LoadMissionData;

	typedef uintptr_t (*MakeNomadString_t)(uint64_t* DstStringPtr, const char* srcString);
	inline static MakeNomadString_t MakeNomadString;

	typedef bool (*GPSConfigInit_t)(uintptr_t CGPSConfig, uintptr_t PawnPlayer);
	inline static GPSConfigInit_t GPSConfigInit;

	typedef float (*GetMinStepTime_t)(uintptr_t CPhysWorld);
	inline static GetMinStepTime_t GetMinStepTime;

	typedef uint32_t (*GetCRCFromString_t)(const char* oString);
	inline static GetCRCFromString_t GetCRCFromString;

	typedef void (*SendShowOrHideAllUIEvent_t)(bool);
	inline static SendShowOrHideAllUIEvent_t SendShowOrHideAllUIEvent;

	typedef void (*PopPlayerActionMap_t)(const char*);
	inline static PopPlayerActionMap_t PopPlayerActionMap;

	typedef void (*PushPlayerActionMap_t)(const char*);
	inline static PushPlayerActionMap_t PushPlayerActionMap;

	typedef uint64_t (*GetNumberOfPlayers_t)(uintptr_t*, uintptr_t*, uintptr_t*);
	inline static GetNumberOfPlayers_t GetNumberOfPlayers;

	typedef uintptr_t(*ExecuteFrameJob_t)(uintptr_t, uintptr_t, uintptr_t);
	inline static ExecuteFrameJob_t ExecuteFrameJob;

	typedef uintptr_t(*ProcessMouseSmoothing_t)(uintptr_t, int*);
	inline static ProcessMouseSmoothing_t ProcessMouseSmoothing;

	typedef uintptr_t (*ProcessMouseInput_t)(uintptr_t a1, uintptr_t a2);
	inline static ProcessMouseInput_t ProcessMouseInput;

	typedef uintptr_t(*LoadCameraContext_t)(uintptr_t a1, uintptr_t a2);
	inline static LoadCameraContext_t LoadCameraContext;

	static uintptr_t ExecuteFrameJob_Detour(uintptr_t a1, uintptr_t a2, uintptr_t a3);

	static uint32_t FNV32(const char* path);
	static float GetMinStepTime_Detour(uintptr_t CPhysWorld);

	static uintptr_t GetCPhysWorld();

	static void EnablePlayerAnimations(bool EnabledState);

	static bool IsInLoadingState();
	static bool IsOnline();

	static bool GPSConfigInit_detour(uintptr_t CGPSConfig, uintptr_t PawnPlayer);
	static uintptr_t ProcessMouseInput_detour(uintptr_t a1, uintptr_t a2);
	static uintptr_t ProcessMouseSmoothing_detour(uintptr_t a1, int* a2);
	static uintptr_t LoadCameraContext_detour(uintptr_t a1, uintptr_t a2);

};