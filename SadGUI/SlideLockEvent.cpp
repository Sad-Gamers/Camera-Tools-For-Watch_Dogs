#include "SlideLockEvent.h"

void SlideLockEvent::Update(){
    if (!SlideLockEventCompleted) {
        unsigned int WeaponMechanicBulletCount = *(unsigned int*)(CWeaponMechanicComponent + o_BulletCount);
        if (WeaponMechanicBulletCount == 0) {
            *(BYTE*)(CWeaponMechanicComponent + o_FiringRate) = 1;
            *(float*)(CWeaponMechanicComponent + o_SlideOffset) = 0.032f;
        }
        else{
            SlideLockEventCompleted = !ReleaseSlide();
        }
    }
}

bool SlideLockEvent::ReleaseSlide() {
    SlideOffset = *(float*)(CWeaponMechanicComponent + o_SlideOffset);
    if (SlideOffset < RestoredSlideOffset) {
        *(BYTE*)(CWeaponMechanicComponent + o_FiringRate) = 1;
        *(float*)(CWeaponMechanicComponent + o_SlideOffset) = SlideOffset + 0.32f * (float)Misc::GetMinStepTimeMacro();
        return true;
    }
    else {
        *(float*)(CWeaponMechanicComponent + o_SlideOffset) = RestoredSlideOffset;
        *(BYTE*)(CWeaponMechanicComponent + o_FiringRate) = 0;
        return false;
    }
}