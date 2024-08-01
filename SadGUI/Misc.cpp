#include "Misc.h"
#include "CameraManager.h"
#include "GridShadingManager.h"


void Misc::Initialize() {
    RemoveVMProtect();
	MakeNomadString = (MakeNomadString_t)(Imagebase + Offsets::BuildNomadString);
    SendShowOrHideAllUIEvent = (SendShowOrHideAllUIEvent_t)(Imagebase + Offsets::SendShowOrHideAllUIEvent);
    GetMinStepTime = (GetMinStepTime_t)(Imagebase + Offsets::GetMinStepTime);
    GetCRCFromString = (GetCRCFromString_t)(Imagebase + Offsets::GetCRCFromString);
    GPSConfigInit = (GPSConfigInit_t)(Imagebase + Offsets::GPSConfigInit);
    PopPlayerActionMap = (PopPlayerActionMap_t)(Imagebase + Offsets::PopPlayerActionMap);
    PushPlayerActionMap = (PushPlayerActionMap_t)(Imagebase + Offsets::PushPlayerActionMap);
    GetNumberOfPlayers = (GetNumberOfPlayers_t)(Imagebase + Offsets::GetNumberOfPlayers);
    UpdateMouseCameraLook = (UpdateMouseCameraLook_t)(Imagebase + Offsets::UpdateMouseCameraLook);
    LoadMissionData = (LoadMissionData_t)(Imagebase + Offsets::LoadMissionData);
    ExecuteFrameJob = (ExecuteFrameJob_t)(Imagebase + Offsets::ExecuteFrameJob);
    MH_Initialize();
    MH_CreateHook((LPVOID)(Imagebase + Offsets::GetMinStepTime), &GetMinStepTime_Detour, reinterpret_cast<LPVOID*>(&GetMinStepTime));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::GetMinStepTime));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::InputListener), &DummyReturn, NULL);
    MH_CreateHook((LPVOID)(Imagebase + Offsets::GPSConfigInit), &GPSConfigInit_detour, reinterpret_cast<LPVOID*>(&GPSConfigInit));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::GPSConfigInit));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::UpdateMouseCameraLook), &UpdateMouseCameraLook_detour, reinterpret_cast<LPVOID*>(&UpdateMouseCameraLook));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::UpdateMouseCameraLook));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::ExecuteFrameJob), &ExecuteFrameJob_Detour, reinterpret_cast<LPVOID*>(&ExecuteFrameJob));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::ExecuteFrameJob));
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


bool Misc::GPSConfigInit_detour(uintptr_t CGPSConfig, uintptr_t PawnPlayer) {
    ImVec2 DisplaySize = ImGui::GetIO().DisplaySize;

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

uintptr_t Misc::UpdateMouseCameraLook_detour(uintptr_t a1) {
    uintptr_t MouseDeltaData = *(uintptr_t*)(a1 + 80);
    if (MouseDeltaData) {
        MouseDeltaX = *(float*)(MouseDeltaData + o_MouseDeltaX);
        MouseDeltaY = *(float*)(MouseDeltaData + o_MouseDeltaY);
    }
    return UpdateMouseCameraLook(a1);

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

uintptr_t Misc::GetCPhysWorld() {
    return ((*(uintptr_t*)((Imagebase + Offsets::CPhysWorld)) + 0x0));
}

float Misc::GetMinStepTimeMacro() {
    return GetMinStepTime_Detour(GetCPhysWorld());
}


