#include "GridShadingManager.h"


void GridShadingManager::Initialize() {
	uintptr_t Imagebase = Misc::Imagebase;
	SetGridShading = (SetGridShading_t)(Imagebase + Offsets::SetGridShading);
}

uintptr_t GridShadingManager::GetGridShadingManager() {
	uintptr_t Imagebase = Misc::Imagebase;
	return ((*(uintptr_t*)((Imagebase + Offsets::GridShadingManager)) + 0x0));
}

void GridShadingManager::DisableMenuGridShading(bool State) {
	uintptr_t Imagebase = Misc::Imagebase;
	if(State)
		*(BYTE*)(Imagebase + Offsets::GridShadingOnPause) = 0x75;
	else
		*(BYTE*)(Imagebase + Offsets::GridShadingOnPause) = 0x74;
}

void GridShadingManager::EnableGridShading(bool EnabledState) {
	SetGridShading(GetGridShadingManager(), NULL, EnabledState, 1.0);
}