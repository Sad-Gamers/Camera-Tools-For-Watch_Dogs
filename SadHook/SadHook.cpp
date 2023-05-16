#include "SadHook.h"
#include "SadMemEdit.h"
#include "CameraSystem.h"
#include "DisruptHook.h"

void SadHook::Initialize() {
	SadMemEdit::PatchVMProtect();
	DWORD WINAPI SadHookThread(LPVOID lpParam);
	CreateThread(0, 0, SadHookThread, GetModuleHandleA("Disrupt_b64.dll"), 0, 0);
}

DWORD WINAPI SadHookThread(LPVOID lpParam)
{
	SadHook* inst = (SadHook*)lpParam;
	inst->SadHookUpdate();
	return 0;
}

void SadHook::ShowConsole() {
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "wb", stdout);
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND WindowHandle = ::GetConsoleWindow();
	SetConsoleTextAttribute(ConsoleHandle, 8); //Set text color to dark gray.

	std::cout << "[Camera Tools By Sad_Gamers Version 1.0]" << std::endl;
	std::cout << "---------------------------------------  [CONTROLS]  ------------------------------------------" << std::endl;
	std::cout << "-INSERT                                        : Toggle Freecam                               -" << std::endl;
	std::cout << "-ARROW KEYS                                    : Move Freecam	                              -" << std::endl;
	std::cout << "-HOME/END                                      : +/- Freecam Elevation                        -" << std::endl;
	std::cout << "-NUMPAD */-                                    : +/- Freecam Speed                            -" << std::endl;
	std::cout << "-NUMPAD 7/1                                    : +/- Freecam Roll                             -" << std::endl;
	std::cout << "-NUMPAD 9/3                                    : +/- Freecam Field Of View                    -" << std::endl;
	std::cout << "-NUMPAD 5                                      : Toggle Depth of Field Mode (Near/Far)        -" << std::endl;
	std::cout << "-NUMPAD 4/6                                    : +/- Depth of Field Focal Stop                -" << std::endl;
	std::cout << "-NUMPAD 8/2                                    : +/- Depth of Field Focus Range               -" << std::endl;
	std::cout << "-PAGE UP/DOWN                                  : +/- Time Of Day                              -" << std::endl;
	std::cout << "-F1/F2/F3                                      : Cycle Weather (Clear, Cloudy, Storm)         -" << std::endl;
	std::cout << "-F4                                            : Toggle HUD/UI                                -" << std::endl;
	std::cout << "-F5                                            : Toggle Freeze                                -" << std::endl;
	std::cout << "-F6                                            : Toggle Slow-Mo                               -" << std::endl;
	std::cout << "-F7                                            : Toggle Super Rendering                       -" << std::endl;
	std::cout << "-----------------------------------------------------------------------------------------------" << std::endl;

	if (WindowHandle != NULL)
	{
		HMENU WindowMenu = ::GetSystemMenu(WindowHandle, FALSE);
		if (WindowMenu != NULL) DeleteMenu(WindowMenu, SC_CLOSE, MF_BYCOMMAND);
		//This just prevents the user from being able to close the console window, since doing that closes the game.
	}
}

DWORD64 SadHook::GetImagebase() {
	return (DWORD64)GetModuleHandleA("Disrupt_b64.dll"); //Base address for the Disrupt DLL.
}

void SadHook::SadHookUpdate() {
	//Wait a few seconds before running the other threads and the console.
	Sleep(5000);
	DisruptHook::Initialize();
	CameraSystem::Initialize();
	ShowConsole();

	while (true) {
		if (GetAsyncKeyState(VK_INSERT)) {
			/*
			* Only allow the user to enable the freecam if the camera is present and the game is not in a loading transition.
			* This prevents crashing.
			*/
			if (DisruptHook::bCameraLoaded && !DisruptHook::bGameLoading) {
				if (!bFreeCamMode) {
					bFreeCamMode = true;
					CameraSystem::EnableFreeCam(true);
				}
				else {
					bFreeCamMode = false;
					CameraSystem::EnableFreeCam(false);
				}
			}
			while (GetAsyncKeyState(VK_INSERT));
		}
		Sleep(20);
	}
}