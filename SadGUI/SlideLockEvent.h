#pragma once
#include "GlobalHeaders.h"

#define o_SlideOffset 0x2DC
#define o_FiringRate 0x530
#define o_BulletCount 0x98

class SlideLockEvent
{
public:
	void Update();
	bool ReleaseSlide();
	uintptr_t CWeaponMechanicComponent;
	float RestoredSlideOffset;
	float SlideOffset;
	bool SlideLockEventCompleted;
	SlideLockEvent(uint64_t CWeaponComponentID, float oSlideOffset) {
		CWeaponMechanicComponent = CWeaponComponentID;
		RestoredSlideOffset = oSlideOffset;
		SlideLockEventCompleted = false;
	}
};
