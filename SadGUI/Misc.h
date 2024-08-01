#pragma once
#include "GlobalHeaders.h"

#define o_MouseDeltaY 0x90
#define o_MouseDeltaX 0x94


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

	typedef uintptr_t(*UpdateMouseCameraLook_t)(uintptr_t);
	inline static UpdateMouseCameraLook_t UpdateMouseCameraLook;

	typedef void (*PopPlayerActionMap_t)(const char*);
	inline static PopPlayerActionMap_t PopPlayerActionMap;

	typedef void (*PushPlayerActionMap_t)(const char*);
	inline static PushPlayerActionMap_t PushPlayerActionMap;

	typedef uint64_t (*GetNumberOfPlayers_t)(uintptr_t*, uintptr_t*, uintptr_t*);
	inline static GetNumberOfPlayers_t GetNumberOfPlayers;

	typedef uintptr_t(*ExecuteFrameJob_t)(uintptr_t, uintptr_t, uintptr_t);
	inline static ExecuteFrameJob_t ExecuteFrameJob;

	static uintptr_t ExecuteFrameJob_Detour(uintptr_t a1, uintptr_t a2, uintptr_t a3);

	static uint32_t FNV32(const char* path);
	static float GetMinStepTime_Detour(uintptr_t CPhysWorld);

	static uintptr_t GetCPhysWorld();

	static void EnablePlayerAnimations(bool EnabledState);

	static bool IsInLoadingState();
	static bool IsOnline();

	static bool GPSConfigInit_detour(uintptr_t CGPSConfig, uintptr_t PawnPlayer);
	static uintptr_t UpdateMouseCameraLook_detour(uintptr_t a1);


};