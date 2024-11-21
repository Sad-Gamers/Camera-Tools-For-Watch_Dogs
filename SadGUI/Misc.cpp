#include "Misc.h"
#include "Player.h"
#include "DXHook.h"
#include "CameraManager.h"
#include "EntityManager.h"
#include "GridShadingManager.h"


void Misc::Initialize() {
    RemoveVMProtect();
	EnableFelonySystem = (EnableFelonySystem_t)(Imagebase + Offsets::EnableFelonySystem);
	MakeNomadString = (MakeNomadString_t)(Imagebase + Offsets::BuildNomadString);
    SendShowOrHideAllUIEvent = (SendShowOrHideAllUIEvent_t)(Imagebase + Offsets::SendShowOrHideAllUIEvent);
    GetMinStepTime = (GetMinStepTime_t)(Imagebase + Offsets::GetMinStepTime);
    GetCRCFromString = (GetCRCFromString_t)(Imagebase + Offsets::GetCRCFromString);
    GPSConfigInit = (GPSConfigInit_t)(Imagebase + Offsets::GPSConfigInit);
    PopPlayerActionMap = (PopPlayerActionMap_t)(Imagebase + Offsets::PopPlayerActionMap);
    PushPlayerActionMap = (PushPlayerActionMap_t)(Imagebase + Offsets::PushPlayerActionMap);
    GetNumberOfPlayers = (GetNumberOfPlayers_t)(Imagebase + Offsets::GetNumberOfPlayers);
    LoadMissionData = (LoadMissionData_t)(Imagebase + Offsets::LoadMissionData);
    ExecuteFrameJob = (ExecuteFrameJob_t)(Imagebase + Offsets::ExecuteFrameJob);
    ProcessMouseInput = (ProcessMouseInput_t)(Imagebase + Offsets::ProcessMouseInput);
    ProcessMouseSmoothing = (ProcessMouseSmoothing_t)(Imagebase + Offsets::ProcessMouseSmoothing);
    LoadCameraContext = (LoadCameraContext_t)(Imagebase + Offsets::LoadCameraContext);
    UpdatePlayerPawn = (UpdatePlayerPawn_t)(Imagebase + Offsets::UpdatePlayerPawn);
    SetWaypoint = (SetWaypoint_t)(Imagebase + Offsets::SetWaypoint);
    MH_Initialize();
    MH_CreateHook((LPVOID)(Imagebase + Offsets::GetMinStepTime), &GetMinStepTime_Detour, reinterpret_cast<LPVOID*>(&GetMinStepTime));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::GetMinStepTime));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::InputListener), &DummyReturn, NULL);
    MH_CreateHook((LPVOID)(Imagebase + Offsets::GPSConfigInit), &GPSConfigInit_detour, reinterpret_cast<LPVOID*>(&GPSConfigInit));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::GPSConfigInit));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::ExecuteFrameJob), &ExecuteFrameJob_Detour, reinterpret_cast<LPVOID*>(&ExecuteFrameJob));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::ExecuteFrameJob));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::ProcessMouseInput), &ProcessMouseInput_detour, reinterpret_cast<LPVOID*>(&ProcessMouseInput));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::ProcessMouseInput));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::ProcessMouseSmoothing), &ProcessMouseSmoothing_detour, reinterpret_cast<LPVOID*>(&ProcessMouseSmoothing));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::ProcessMouseSmoothing));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::LoadCameraContext), &LoadCameraContext_detour, reinterpret_cast<LPVOID*>(&LoadCameraContext));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::LoadCameraContext));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::UpdatePlayerPawn), &UpdatePlayerPawn_detour, reinterpret_cast<LPVOID*>(&UpdatePlayerPawn));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::UpdatePlayerPawn));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::UpdatePlayerPawn), &UpdatePlayerPawn_detour, reinterpret_cast<LPVOID*>(&UpdatePlayerPawn));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::UpdatePlayerPawn));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::SetWaypoint), &SetWaypoint_detour, reinterpret_cast<LPVOID*>(&SetWaypoint));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::SetWaypoint));
}

void Misc::RemoveVMProtect() {
    DWORD oldProtect = 0;
    auto ntdll = GetModuleHandleA("ntdll.dll");
    BYTE callcode = ((BYTE*)GetProcAddress(ntdll, "NtQuerySection"))[4] - 1;
    BYTE restore[] = { 0x4C, 0x8B, 0xD1, 0xB8, callcode };
    auto nt_vp = (BYTE*)GetProcAddress(ntdll, "NtProtectVirtualMemory");
    VirtualProtect(nt_vp, sizeof(restore), PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy(nt_vp, restore, sizeof(restore));
    VirtualProtect(nt_vp, sizeof(restore), oldProtect, &oldProtect);
    VirtualProtect(LPVOID(Imagebase + Offsets::UpdateAnimations), 64, PAGE_EXECUTE_READWRITE, &oldProtect);
    VirtualProtect(LPVOID(Imagebase + Offsets::GridShadingOnPause), 64, PAGE_EXECUTE_READWRITE, &oldProtect);
    VirtualProtect(LPVOID(Imagebase + Offsets::DepthOfFieldCondition), 64, PAGE_EXECUTE_READWRITE, &oldProtect);
    VirtualProtect(LPVOID(Imagebase + Offsets::UpdatePlayerLook), 64, PAGE_EXECUTE_READWRITE, &oldProtect);
}

uintptr_t Misc::UpdatePlayerPawn_detour(uintptr_t CPlayerPawn) {
    Player::PlayerDirectionX = *(float*)(CPlayerPawn + o_PlayerDirectionX);
    Player::PlayerDirectionY = *(float*)(CPlayerPawn + o_PlayerDirectionY);
    return UpdatePlayerPawn(CPlayerPawn);
}

uintptr_t Misc::SetWaypoint_detour(uintptr_t a1, uintptr_t a2) {
    Player::WaypointPosition.x = *(float*)(a2 + 116);
    Player::WaypointPosition.y = *(float*)(a2 + 120);
    Player::WaypointPosition.z = *(float*)(a2 + 124) + 40.0f;
    return SetWaypoint(a1, a2);
}

bool Misc::GPSConfigInit_detour(uintptr_t CGPSConfig, uintptr_t PawnPlayer) {
    //ImVec2 DisplaySize = ImGui::GetIO().DisplaySize;

    //if( (DisplaySize.x / DisplaySize.y) >= ( 16.0f / 9.0f) ){
    //    float MiniMapPosition = (((DisplaySize.y * 16 / 9) * 0.84f) +
    //        ((DisplaySize.x - (DisplaySize.y * 16 / 9)) / 2)) / DisplaySize.x;
    //    *(float*)(CGPSConfig + 172) = MiniMapPosition;
    //}
    //else {
    //    float MiniMapPosition = ( ( (DisplaySize.x - (DisplaySize.y / (16 / 9)) ) / 2) +
    //        ((DisplaySize.y / (16 / 9)) * 0.72f) ) / DisplaySize.x;
    //    *(float*)(CGPSConfig + 176) = MiniMapPosition;
    //    float MiniMapSize = (0.3f / ((16 / 9) * (DisplaySize.x / DisplaySize.y)));
    //    *(float*)(CGPSConfig + 168) = MiniMapSize;
    //}
    return GPSConfigInit(CGPSConfig, PawnPlayer);
}

void Misc::DummyReturn() {
    return;
}


uintptr_t Misc::ProcessMouseInput_detour(uintptr_t a1, uintptr_t a2) {
    uintptr_t Result = ProcessMouseInput(a1, a2);
    if (DisableMouseAcceleration) {
        if (*(DWORD*)a2 == 2033636637) { //cam_look_py_mouse
            float MouseSensX = *(float*)((*(uintptr_t*)((Imagebase + Offsets::MouseSensitivity)) + o_MouseSensX));
            float MouseSensY = *(float*)((*(uintptr_t*)((Imagebase + Offsets::MouseSensitivity)) + o_MouseSensY));
            MouseSensX = (MouseSensX / 100.0f) * (5.0f - 0.1f) + 0.1f;
            MouseSensY = (MouseSensY / 100.0f) * (5.0f - 0.1f) + 0.1f;
            *(float*)(*(uintptr_t*)(a1 + 8) + o_MouseDeltaX) = *(float*)(a2 + 4) * -1.0f * MouseSensX;
            *(float*)(*(uintptr_t*)(a1 + 8) + o_MouseDeltaY) = *(float*)(a2 + 8) * MouseSensY;
            MouseDeltaX = *(float*)(a2 + 4) * -1.0f * MouseSensX;
            MouseDeltaY = *(float*)(a2 + 8) *  MouseSensY;
        }
    }
    else {
        if (*(DWORD*)a2 == 2033636637) { //cam_look_py_mouse
            MouseDeltaX = *(float*)(*(uintptr_t*)(a1 + 8) + o_MouseDeltaX);
            MouseDeltaY = *(float*)(*(uintptr_t*)(a1 + 8) + o_MouseDeltaY);
        }
    }
    return Result;
}

uintptr_t Misc::ProcessMouseSmoothing_detour(uintptr_t a1, int* a2) {
    if (DisableMouseAcceleration)
        return 0;
    else return ProcessMouseSmoothing(a1, a2);
}

uintptr_t Misc::LoadCameraContext_detour(uintptr_t a1, uintptr_t a2) {
    uintptr_t Result = LoadCameraContext(a1, a2);
    if (DisableRotSpeedCap) {
        *(float*)(a1 + o_InputYawExtraSpeed) = 800.0f; //
        *(float*)(a1 + o_InputYawExtraSpeedAngleThreshold) = 0.0f; //
        //*(float*)(a1 + o_InputDampDown) = 0.0f; //
        //*(float*)(a1 + o_InputDampUp) = 0.0f; //
        //*(float*)(a1 + 0xB8) = 120.0f; //fInputPitchSpeed
        //*(float*)(a1 + 0xBC) = 120.0f; //fInputYawSpeed
    }
    return Result;
}

void Misc::DisableInputListening(bool State) {
    if (State)
        MH_EnableHook((LPVOID)(Imagebase + Offsets::InputListener));
    else
        MH_DisableHook((LPVOID)(Imagebase + Offsets::InputListener));
}

uint32_t Misc::FNV32(const char* path) {

    std::string str(path);

    uint64_t hash64 = 0xCBF29CE484222325;
    for (char t : str) {
        hash64 *= 0x100000001B3;
        hash64 ^= t;
    }

    uint32_t hash32 = (uint32_t)hash64;
    if ((hash32 & 0xFFFF0000) == 0xFFFF0000) {
        return hash32 & ~(1u << 16);
    }
    return hash32;
}


uintptr_t Misc::ExecuteFrameJob_Detour(uintptr_t a1, uintptr_t a2, uintptr_t a3) {

    if (StopFrameJobs) {
        if (a1) {
            if (*(uintptr_t*)(a1 + 200))
            {
                TickCountOnFrameJobStop = GetTickCount64();
                StopFrameJobs = false;
            }
        }
        return 0;
    }

    if (GetTickCount64() <= (TickCountOnFrameJobStop + 500uLL)) {
        return 0;
    }

    return ExecuteFrameJob(a1, a2, a3);
}


float Misc::GetMinStepTime_Detour(uintptr_t CPhysWorld) {
    if (SlowMo) {
        return 0.3f * (*(float*)(CPhysWorld + 88));
    }
    if (TimeStop) {
        return 1e-8f;
    }
    if (CustomSpeed) {
        return SpeedMultiplier * (*(float*)(CPhysWorld + 88));
    }
    return *(float*)(CPhysWorld + 88);
}

void Misc::EnablePlayerAnimations(bool EnabledState) {
    if (EnabledState)
        *(BYTE*)(Imagebase + Offsets::UpdateAnimations) = Offsets::ResumePlayerAnimation;
    else
        *(BYTE*)(Imagebase + Offsets::UpdateAnimations) = Offsets::StopPlayerAnimation;
}

bool Misc::IsInLoadingState() {
    uintptr_t LoadingStatePtr = ((*(uintptr_t*)((Imagebase + Offsets::LoadingState)) + 0x1A8));
    if (!LoadingStatePtr)
        return true;
    if (*(bool*)(LoadingStatePtr))
        return true;
    else
        return false;
}

bool Misc::IsOnline() {
    uint64_t Dummy = 0;
    uint64_t NumberOfPlayers = Misc::GetNumberOfPlayers(&Dummy, &Dummy, &Dummy);
    if (NumberOfPlayers > 1)
        return true;
    uintptr_t OnlineStatePtr = ((*(uintptr_t*)((Imagebase + Offsets::OnlineState)) + 0x2C));
    if (!OnlineStatePtr)
        return false;
    if (*(int*)(OnlineStatePtr) != 0)
        return true;
    else
        return false;
}

uintptr_t Misc::GetFelonySystem() {
    return ((*(uintptr_t*)((Imagebase + Offsets::CFelonySystem)) + 0x0));
}

void Misc::EnableFelonySystemMacro(bool Enabled) {
    if (GetFelonySystem()) {
        EnableFelonySystem(GetFelonySystem(), Enabled);
    }
}

uintptr_t Misc::GetCPhysWorld() {
    return ((*(uintptr_t*)((Imagebase + Offsets::CPhysWorld)) + 0x0));
}

float Misc::GetMinStepTimeMacro() {
    return GetMinStepTime_Detour(GetCPhysWorld());
}


