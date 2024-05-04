#include "SlideAnimations.h"
#include "CameraManager.h"
#include "Databases.h"


void SlideAnimations::Initialize() {
    uintptr_t Imagebase = Misc::Imagebase;
    UnkPhysComponentUpdateWrapper = (UnkPhysComponentUpdateWrapper_t)(Imagebase + Offsets::UnkPhysComponentWrapper);
    PostAnimUpdateWrapper = (PostAnimUpdateWrapper_t)(Imagebase + Offsets::PostAnimUpdateWrapper);
    PostAnimUpdate = (PostAnimUpdate_t)(Imagebase + Offsets::PostAnimUpdate);
    GetBulletsInClip = (GetBulletsInClip_t)(Imagebase + Offsets::GetBulletsInClip);
    HasItemInMainHand = (HasItemInMainHand_t)(Imagebase + Offsets::HasItemInMainHand);
    UpdateWeaponStatus = (UpdateWeaponStatus_t)(Imagebase + Offsets::UpdateWeaponStatus);
    GetEquippedWeaponGrip = (GetEquippedWeaponGrip_t)(Imagebase + Offsets::GetEquippedWeaponGrip);
    MH_CreateHook((LPVOID)(Imagebase + Offsets::PostAnimUpdateWrapper), &PostAnimUpdateWrapper_Detour, reinterpret_cast<LPVOID*>(&PostAnimUpdateWrapper));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::PostAnimUpdateWrapper));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::UnkPhysComponentWrapper), &UnkPhysComponentUpdateWrapper_Detour, reinterpret_cast<LPVOID*>(&UnkPhysComponentUpdateWrapper));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::UnkPhysComponentWrapper));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::PostAnimUpdate), &PostAnimUpdate_Detour, reinterpret_cast<LPVOID*>(&PostAnimUpdate));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::PostAnimUpdate));
    MH_CreateHook((LPVOID)(Imagebase + Offsets::UpdateWeaponStatus), &UpdateWeaponStatus_detour, reinterpret_cast<LPVOID*>(&UpdateWeaponStatus));
    MH_EnableHook((LPVOID)(Imagebase + Offsets::UpdateWeaponStatus));
}

uintptr_t SlideAnimations::GetWeaponMechanicComponent() {
    return *(uintptr_t*)(Misc::Imagebase + Offsets::WeaponMechanicComponent);
}

//Blowbackfix Begin
uintptr_t SlideAnimations::UnkPhysComponentUpdateWrapper_Detour(uintptr_t CPhysWorld, float DeltaTime) {
    if (GetWeaponMechanicComponent() && PatchBlowBack) {
        PostUpdate = true;
        PostAnimUpdateWrapper_Detour(GetWeaponMechanicComponent(), DeltaTime);
        PostUpdate = false;
    }
    return UnkPhysComponentUpdateWrapper(CPhysWorld, DeltaTime);
}

uintptr_t SlideAnimations::PostAnimUpdateWrapper_Detour(uintptr_t CWeaponMechanicComponent, float DeltaTime) {
    if (PostUpdate) {
        return PostAnimUpdateWrapper(CWeaponMechanicComponent, DeltaTime);
    }
    else
        return 0i64;
}
//Blowbackfix End

void SlideAnimations::PatchMissingSlideBone(uintptr_t CWeaponMechanicComponent) {
    if (*(BYTE*)(CWeaponMechanicComponent + 0x2D4) == 255) {
        *(BYTE*)(CWeaponMechanicComponent + 0x2D4) = 3;
        *(BYTE*)(CWeaponMechanicComponent + 0x2D5) = 0;
        *(BYTE*)(CWeaponMechanicComponent + 0x2D6) = 0;
        *(BYTE*)(CWeaponMechanicComponent + 0x2D7) = 0;
        *(float*)(CWeaponMechanicComponent + 0x2D8) = 0.00908953f;
        *(float*)(CWeaponMechanicComponent + 0x2DC) = 0.122821f;
        *(float*)(CWeaponMechanicComponent + 0x2E0) = 0.102064f;
    }
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
    if (SlideLocking) {
        LocalPlayerBulletsInClip = GetBulletsInClip(*(uintptr_t*)(CPlayerPawnDriverImplementation + 0x158));
        LocalPlayerHasItemInMainHand = HasItemInMainHand(*(uintptr_t*)(CPlayerPawnDriverImplementation + 0x158));
        LocalPlayerWeaponGrip = GetEquippedWeaponGrip(*(uintptr_t*)(CPlayerPawnDriverImplementation + 0x158));
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