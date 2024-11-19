#pragma once
#include "GlobalHeaders.h"
#include "SlideLockEvent.h"

#define o_SlideOffset 0x2DC
#define o_FiringRate 0x530
#define o_BulletCount 0x98


class SlideAnimations
{
public:
	inline static bool PostUpdate;
	inline static bool PatchBlowBack;
	inline static bool SlideLocking;
	inline static unsigned int LocalPlayerBulletsInClip;
	inline static bool LocalPlayerHasItemInMainHand;
	inline static int LocalPlayerWeaponGrip;

	inline static std::vector<SlideLockEvent> SlideLockEvents;

	typedef uintptr_t(*UpdateWeaponStatus_t)(uintptr_t CPlayerPawnDriverImplementation);
	inline static UpdateWeaponStatus_t UpdateWeaponStatus;

	typedef bool (*HasItemInMainHand_t)(uintptr_t CInventoryComponent);
	inline static HasItemInMainHand_t HasItemInMainHand;

	typedef int (*GetEquippedWeaponGrip_t)(uintptr_t CInventoryComponent);
	inline static GetEquippedWeaponGrip_t GetEquippedWeaponGrip;

	typedef uintptr_t(*PostAnimUpdateWrapper_t)(uintptr_t CWeaponMechanicComponent, float DeltaTime);
	inline static PostAnimUpdateWrapper_t PostAnimUpdateWrapper;

	typedef uintptr_t(*GetWeaponBlah_t)(uintptr_t, uintptr_t);
	inline static GetWeaponBlah_t GetWeaponBlah;

	typedef uintptr_t(*PostAnimUpdate_t)(uintptr_t CWeaponMechanicComponent, float DeltaTime);
	inline static PostAnimUpdate_t PostAnimUpdate;

	typedef uint32_t (*GetBulletsInClip_t)(uintptr_t CInventoryComponent);
	inline static GetBulletsInClip_t GetBulletsInClip;

	typedef uintptr_t(*UnkRoutineWrapper_t)(uintptr_t a1, float DeltaTime);
	inline static UnkRoutineWrapper_t UnkRoutineWrapper;

	static uintptr_t PostAnimUpdate_Detour(uintptr_t CWeaponMechanicComponent, float DeltaTime);
	static uintptr_t GetWeaponMechanicComponent();
	static uintptr_t UnkRoutineWrapper_Detour(uintptr_t a1, float DeltaTime);
	static uintptr_t PostAnimUpdateWrapper_Detour(uintptr_t CWeaponMechanicComponent, float DeltaTime);
	static uintptr_t UpdateWeaponStatus_detour(uintptr_t CPlayerPawnDriverImplementation);

	static void SlideLockEventsMonitor(uintptr_t CWeaponMechanicComponent);
	static void UpdateAllSlideLockEvents();
	static void DeleteAllSlideLockEvents();
	static void PatchMissingSlideBone(uintptr_t CWeaponMechanicComponent);
	static void Initialize();
};
