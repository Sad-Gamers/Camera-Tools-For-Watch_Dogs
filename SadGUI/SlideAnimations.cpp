#include "SlideAnimations.h"
#include "CameraManager.h"
#include "Actor.h"
#include "Databases.h"


void SlideAnimations::Initialize() {
    uintptr_t Imagebase = Misc::Imagebase;
    PostAnimUpdate = (PostAnimUpdate_t)(Imagebase + Offsets::PostAnimUpdate);
    GetBulletsInClip = (GetBulletsInClip_t)(Imagebase + Offsets::GetBulletsInClip);
    HasItemInMainHand = (HasItemInMainHand_t)(Imagebase + Offsets::HasItemInMainHand);
    UpdateWeaponStatus = (UpdateWeaponStatus_t)(Imagebase + Offsets::UpdateWeaponStatus);
    GetEquippedWeaponGrip = (GetEquippedWeaponGrip_t)(Imagebase + Offsets::GetEquippedWeaponGrip);
    PostPartRecoil = (Blowback_t)(Imagebase + Offsets::PostPartRecoil);
    UpdateSkeletons = (UnkAni_t)(Imagebase + Offsets::UpdateSkeletons);
    MH_CreateHook((LPVOID)(Imagebase + Offsets::PostPartRecoil), &PostPartRecoil_detour, reinterpret_cast<LPVOID*>(&PostPartRecoil));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::PostPartRecoil));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::UpdateSkeletons), &UpdateSkeletons_detour, reinterpret_cast<LPVOID*>(&UpdateSkeletons));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::UpdateSkeletons));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::PostAnimUpdate), &PostAnimUpdate_Detour, reinterpret_cast<LPVOID*>(&PostAnimUpdate));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::PostAnimUpdate));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::UpdateWeaponStatus), &UpdateWeaponStatus_detour, reinterpret_cast<LPVOID*>(&UpdateWeaponStatus));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::UpdateWeaponStatus));
}

uintptr_t SlideAnimations::GetWeaponMechanicComponent() {
    return *(uintptr_t*)(Misc::Imagebase + Offsets::WeaponMechanicComponent);
}

//Blowbackfix Begin
bool SlideAnimations::PostPartRecoil_detour(uintptr_t* a1, uintptr_t a2, __m128* a3) {
    if (PatchBlowBack) {
        uintptr_t Target_1 = 32 * a2;
        uintptr_t Target_2 = a1[23];
        __m128 Translation = *a3;
        std::lock_guard<std::mutex> lock(BlowbackEventsMutex);
        BlowbackEvents.push_back(BlowbackEvent(Target_1, Target_2, Translation));
    }
    return 1;
}

uintptr_t* SlideAnimations::UpdateSkeletons_detour(uintptr_t* a1, uintptr_t a2) {
    uintptr_t* Result = UpdateSkeletons(a1, a2);
    if (PatchBlowBack) {
        std::lock_guard<std::mutex> lock(BlowbackEventsMutex);
        for (int i = 0; i < BlowbackEvents.size(); i++)
        {
            uintptr_t Target_1 = 32 * a2;
            uintptr_t Target_2 = a1[2];
            if (BlowbackEvents[i].Target_1 == Target_1 && BlowbackEvents[i].Target_2 == Target_2) {
                *(__m128*)(Target_1 + Target_2 + 16) = BlowbackEvents[i].Translation;
                BlowbackEvents.erase(BlowbackEvents.begin() + i);
            }
        }
    }

    return Result;
}
//Blowbackfix End

void SlideAnimations::PatchMissingSlideBone(uintptr_t CWeaponMechanicComponent) {
    //if (*(BYTE*)(CWeaponMechanicComponent + 0x2D4) == 255) {
    //    *(BYTE*)(CWeaponMechanicComponent + 0x2D4) = 3;
    //    *(BYTE*)(CWeaponMechanicComponent + 0x2D5) = 0;
    //    *(BYTE*)(CWeaponMechanicComponent + 0x2D6) = 0;
    //    *(BYTE*)(CWeaponMechanicComponent + 0x2D7) = 0;
    //    *(float*)(CWeaponMechanicComponent + 0x2D8) = 0.00908953f;
    //    *(float*)(CWeaponMechanicComponent + 0x2DC) = 0.122821f;
    //    *(float*)(CWeaponMechanicComponent + 0x2E0) = 0.102064f;
    //}
}

//Slide Locking Begin
void SlideAnimations::DeleteAllSlideLockEvents() {
    SlideLockEvents = {};
}


void SlideAnimations::UpdateAllSlideLockEvents() {
    for (int i = 0; i < SlideLockEvents.size(); i++)
    {
        if (SlideLockEvents[i].SlideLockEventCompleted)
            SlideLockEvents.erase(SlideLockEvents.begin() + i);
    }
    for (SlideLockEvent& SlideLockEvent : SlideLockEvents)
        SlideLockEvent.Update();
}

uintptr_t SlideAnimations::PostAnimUpdate_Detour(uintptr_t CWeaponMechanicComponent, float DeltaTime) {
    if(SlideLocking)
        SlideLockEventsMonitor(CWeaponMechanicComponent);
    return PostAnimUpdate(CWeaponMechanicComponent, DeltaTime);
}

uintptr_t SlideAnimations::UpdateWeaponStatus_detour(uintptr_t CPlayerPawnDriverImplementation) {
    if(!Actor::IsPresent())
        CPlayerPawnDriverImplementationCache = CPlayerPawnDriverImplementation;
    if (SlideLocking) {
        LocalPlayerBulletsInClip = GetBulletsInClip(*(uintptr_t*)(CPlayerPawnDriverImplementationCache + 0x158));
        LocalPlayerHasItemInMainHand = HasItemInMainHand(*(uintptr_t*)(CPlayerPawnDriverImplementationCache + 0x158));
        LocalPlayerWeaponGrip = GetEquippedWeaponGrip(*(uintptr_t*)(CPlayerPawnDriverImplementationCache + 0x158));
        UpdateAllSlideLockEvents();
    }
    return UpdateWeaponStatus(CPlayerPawnDriverImplementation);
}

void SlideAnimations::SlideLockEventsMonitor(uintptr_t CWeaponMechanicComponent) {
    if (LocalPlayerHasItemInMainHand && LocalPlayerWeaponGrip == 0) {
        unsigned int WeaponMechanicBulletCount = *(unsigned int*)(CWeaponMechanicComponent + o_BulletCount);
        if (WeaponMechanicBulletCount == 0 && LocalPlayerBulletsInClip == 0) {
            for (SlideLockEvent& SlideLockEvent : SlideLockEvents) {
                if (SlideLockEvent.CWeaponMechanicComponent == CWeaponMechanicComponent)
                    return;
            }
            float WeaponSlideOffset = *(float*)(CWeaponMechanicComponent + o_SlideOffset);
            SlideLockEvents.push_back(SlideLockEvent(CWeaponMechanicComponent, WeaponSlideOffset));
        }
    }
}
//Slide Locking End