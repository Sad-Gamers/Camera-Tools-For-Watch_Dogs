#pragma once
#include "GlobalHeaders.h"


class BlowbackEvent
{
public:
	uintptr_t Target_1;
	uintptr_t Target_2;
	__m128 Translation;
	BlowbackEvent(uintptr_t target_1, uintptr_t target_2, __m128 translation) {
		Target_1 = target_1;
		Target_2 = target_2;
		Translation = translation;
	}
};