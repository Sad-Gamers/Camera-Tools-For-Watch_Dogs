#include "SadHook.h"
#include "SadMemEdit.h"
#include "DisruptHook.h"

void DisruptHook::Initialize() {
	//Defining memory locations of instructions/functions we will be overwriting or using (General).
	pGameSpeedReadSubProc = (DWORD64)((SadHook::GetImagebase() + 0x148B40));
	pCallRenderFrameSubProc = (DWORD64)((SadHook::GetImagebase() + 0x43B216));
	pReadActionMapEnum = (DWORD64)((SadHook::GetImagebase() + 0x8AC3A3));
	SendShowOrHideAllUIEvent = (SendShowOrHideAllUIEvent_t)((DWORD64)(SadHook::GetImagebase() + 0x106B240));

	//Defining memory locations of instructions/functions we will be overwriting or using (Camera).
	pCameraPositionSubProc = (DWORD64)((SadHook::GetImagebase() + 0x1F0FE0));
	pCameraFOVWrite = (DWORD64)((SadHook::GetImagebase() + 0x1F1004));
	pViewMatrixSubProc = (DWORD64)((SadHook::GetImagebase() + 0x7935F0));
	pCallMoveReticleSubProc = (DWORD64)((SadHook::GetImagebase() + 0x16E643A));
	pLensRenderpassSubProc1 = (DWORD64)((SadHook::GetImagebase() + 0x149D8E0));
	pLensRenderpassSubProc2 = (DWORD64)((SadHook::GetImagebase() + 0x146CB53));
	pLensRenderpassSubProc3 = (DWORD64)((SadHook::GetImagebase() + 0x146C360));

	//Defining initial values for booleans.
	bUIVisibile = true;
	bPause = false;
	bHQ = false;
	bSlowMo = false;
	bCameraLoaded = false;
	bGameLoading = false;

	//Defining values to be used for the super rendering toggle.
	nAntiAliasingModeHQ = 5; //AntiAliasing.
	nMultiSampleModeHQ = 0;  //...
	nMultiSampleQualityLevelHQ = 0; //..
	nMapSizeHQ = 8192; //Used for Reflection Map Size, Shadow Map Size, etc...
	nRainShadowMapSizeHQ = 1024; //Used Only for the Rain Shadow Map, since a high value results in an odd and sharp looking map.
	fObjectMinSizeHQ = 0; //Used for all minimum object sizes to allow everything in the scene to be rendered.

	/*
	* The Kill LOD Scale could be lower, however doing may result in some artifacts after disabling the super render mode.
	* An example would be entire buildings disappearing.
	*/
	fKillLodScaleHQ = 0.25;

	//A value of zero for LOD Scale usually results in a crash, so we use a very low value instead.
	fLodScaleHQ = 0.001;

	fFSMShadowRangeHQ = 1000; //Shadow Quality.
	nShadowBilateralBlurNumSamplesHQ = 8; //..
	nShadowBilateralBlurNumPassesHQ = 4; //...
	bSoftShadowsHQ = true; //...
	bSuperSamplingHQ = true; //We want to supersample when superrendering for best results.
	DWORD WINAPI DisruptHookThread(LPVOID lpParam);
	CreateThread(0, 0, DisruptHookThread, GetModuleHandleA("Disrupt_b64.dll"), 0, 0);
}

DWORD WINAPI DisruptHookThread(LPVOID lpParam)
{
	DisruptHook* inst = (DisruptHook*)lpParam;
	inst->DisruptHookUpdate();
	return 0;
}

void DisruptHook::DisruptHookUpdate() {
	while (true) {
		/*
		* pGameLoading is true when we are in a loading screen, or reloading autosave, or going back the main menu, etc..
		* pCameraLoaded is zero when the camera is not loaded (but does not become zero again except halfway through loading.
		* Hence why we use both of these pointers to ensure we never crash.
		*/
		pGameLoading = (DWORD64)((*(uint64_t*)((SadHook::GetImagebase() + 0x3B915E0)) + 0x1A8));
		pCameraLoaded = (DWORD64)((SadHook::GetImagebase() + 0x3B75F00));
		memcpy(&bGameLoading, LPVOID(pGameLoading), 1);
		memcpy(&bCameraLoaded, LPVOID(pCameraLoaded), 4);

		//If we die, quit to menu, or try reloading autosave, reset hooks to game speed to avoid crashing.
		if (bGameLoading) {
			bPause = false; //oh yeah reset the bools too!
			bSlowMo = false;
			SadMemEdit::WriteBytes({ 0xF3, 0x0F, 0x10, 0x41, 0x58,0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC }, pGameSpeedReadSubProc);
		}

		/*
		* Update pointers and allow the player to write to them (using hotkeys)
		* if and only if we are in gameplay to avoid bad pointer reads (which lead to crashing).
		* While checking if a pointer is null is a valid approach, some pointers in Watch Dogs are bad without being null
		* so trying to read or write with them will lead to crashes.
		*/
		if (!bGameLoading && bCameraLoaded) {
			//In the code ahead, we update the pointer locations, and sometimes store the values there in our program.
			pEnvironmentPreset = ((*(uint64_t*)((SadHook::GetImagebase() + 0x3B890D8)) + 0x278));
			pTimeOfDay = ((*(uint64_t*)((*(uint64_t*)(SadHook::GetImagebase() + 0x3B89228)) + 0x8) + 0x758));
			//Write the current time of day to our variable (so we can increase or decrease it later).
			memcpy(&fTimeOfDay, LPVOID(pTimeOfDay), 4);
			/*
			* We later set our weather transition duration to 0 to instantly cycle weather presets, but we need to restore
			* the original duration right after to avoid broken, instant weather transitions during normal gameplay.
			*/
			pTransitionDuration = ((*(uint64_t*)((SadHook::GetImagebase() + 0x3B890D8)) + 0x280));
			memcpy(&fTransitionDuration, LPVOID(pTransitionDuration), 4);
			//Reading horizontal and vertical mouse displacement, we use this to control our freecam's pitch and yaw.
			pMouseDisplacement = ((*(uint64_t*)((*(uint64_t*)((*(uint64_t*)(SadHook::GetImagebase() + 0x3BBCF20)) + 0x30)) + 0x0)) + 0x0);
			pMouseDisplacementX = pMouseDisplacement + 0x94;
			pMouseDisplacementY = pMouseDisplacement + 0x90;
			memcpy(&fMouseDisplacementX, LPVOID(pMouseDisplacementX), 4);
			memcpy(&fMouseDisplacementY, LPVOID(pMouseDisplacementY), 4);
			//We are now defining the locations of the render settings we will be overwriting and reading.
			pRenderConfig = ((*(uint64_t*)((*(uint64_t*)((*(uint64_t*)((*(uint64_t*)(SadHook::GetImagebase() + 0x36B8878)) + 0x0)) + 0x18)) + 0x8)) + 0x0);
			pAntiAliasingMode = pRenderConfig + 0xD50;
			pMultiSampleMode = pRenderConfig + 0xD54;
			pMultiSampleQualityLevel = pRenderConfig + 0xD58;
			pSuperSampling = pRenderConfig + 0x2F4;
			pShadowMapSize = pRenderConfig + 0x9E0;
			pRainShadowMapSize = pRenderConfig + 0x9E8;
			pCascadedShadowMapSize = pRenderConfig + 0x9E4;
			pFSMShadowMapSize = pRenderConfig + 0xA70;
			pStaticShadowMapSize = pRenderConfig + 0xA54;
			pParaboloidReflectionTextureSize = pRenderConfig + 0x6B4;
			pKillLodScale = pRenderConfig + 0x870;
			pLodScale = pRenderConfig + 0x860;
			pRealTreesLodScale = pRenderConfig + 0x858;
			pVegetationLodScale = pRenderConfig + 0x8F0;
			pFSMObjectMinSize = pRenderConfig + 0x8CC;
			pFSMRealTreeMinSize = pRenderConfig + 0x8D0;
			pSceneObjectMinSize = pRenderConfig + 0x8B0;
			pClusterObjectMinSize = pRenderConfig + 0x8A4;
			pClusterObjectMinSizeDetail = pRenderConfig + 0x8AC;
			pShadowBilateralBlurNumPasses = pRenderConfig + 0xA60;
			pShadowBilateralBlurNumSamples = pRenderConfig + 0xA64;
			pSoftShadows = pRenderConfig + 0x9F0;
			pFSMShadowRange = pRenderConfig + 0xA7C;

			//The remainder of the code is mostly "what to do" when user presses a certain key.
			if (GetAsyncKeyState(VK_NEXT)) {
				fTimeOfDay += 40; //Increase time of day.
			}

			if (GetAsyncKeyState(VK_PRIOR)) {
				fTimeOfDay -= 40; //Decrease time of day.
			}

			if (GetAsyncKeyState(VK_F1)) {
				memset(LPVOID(pTransitionDuration), 0, 4); //Set transition duration to 0 for instant weather cycling.
				nEnvironmentPreset = 611376642; //CRC32 for "Clear".
				memcpy(LPVOID(pEnvironmentPreset), &nEnvironmentPreset, 4);
				Sleep(100);
				memcpy(LPVOID(pTransitionDuration), &fTransitionDuration, 4); //Restore original transition duration.
				while (GetAsyncKeyState(VK_F1));
			}

			if (GetAsyncKeyState(VK_F2)) {
				memset(LPVOID(pTransitionDuration), 0, 4); //...
				nEnvironmentPreset = 2386428942; //"Cloudy_NoRain"
				memcpy(LPVOID(pEnvironmentPreset), &nEnvironmentPreset, 4);
				Sleep(100);
				memcpy(LPVOID(pTransitionDuration), &fTransitionDuration, 4); //...
				while (GetAsyncKeyState(VK_F2));
			}

			if (GetAsyncKeyState(VK_F3)) {
				memset(LPVOID(pTransitionDuration), 0, 4); //...
				nEnvironmentPreset = 810417985; //"Storm"
				memcpy(LPVOID(pEnvironmentPreset), &nEnvironmentPreset, 4);
				Sleep(100);
				memcpy(LPVOID(pTransitionDuration), &fTransitionDuration, 4); //...
				while (GetAsyncKeyState(VK_F3));
			}

			if (GetAsyncKeyState(VK_F4)) {
				if (bUIVisibile) {
					bUIVisibile = false;
					SendShowOrHideAllUIEvent(bUIVisibile); //Use internal function to hide ui.
				}
				else {
					bUIVisibile = true;
					SendShowOrHideAllUIEvent(bUIVisibile); //...
				}
				while (GetAsyncKeyState(VK_F4));
			}

			if (GetAsyncKeyState(VK_F5)) {
				if (bSlowMo) {
					bSlowMo = false;
					//Restore original instruction byte code, this will prevent potential crashing.
					SadMemEdit::WriteBytes({ 0xF3, 0x0F, 0x10, 0x41, 0x58,0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC }, pGameSpeedReadSubProc);
				}
				if (!bPause) {
					DWORD64 pVirtualPage = SadMemEdit::AllocateMemory(128); //Allocate memory to write our custom function there.

					/*
					* Define our x86 assembly function, which makes the game read the current speed as 1e-8 which
					* is a very low value.
					* A value of zero sometimes results in a crash as well as broken animations/physics.
					*/
					SadMemEdit::WriteBytes({ 0x51,								//push rcx
						0x48, 0xB9, 0x77, 0xCC, 0x2B, 0x32, 0x0, 0x0, 0x0, 0x0, //mov rcx,(float)1e-8
						0x66, 0x48, 0x0F, 0x6E, 0xC1,							//movq xmm0,rcx
						0x59,													//pop rcx
						0xC3													//ret
						}, pVirtualPage);
					SadMemEdit::WriteFarJump(pVirtualPage + 0x12, pGameSpeedReadSubProc, 0); //jmp [pGameSpeedReadSubProc]
					/*
					* End of custom assembly function, the last line makes us return to the original instruction's location
					* when execution is complete.
					*/

					/*
					* Tell the original instruction to go to our virtual page, resulting in our custom code being executed.
					* Then once the execution is complete, everything that follows resumes normally.
					*/
					SadMemEdit::WriteFarJump(pGameSpeedReadSubProc, pVirtualPage, 0); //jmp [pVirtualPage]
					bPause = true;
				}
				else {
					bPause = false;
					//Restore original byte code (the instruction now reads the actual game speed again).
					SadMemEdit::WriteBytes({ 0xF3, 0x0F, 0x10, 0x41, 0x58,0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC }, pGameSpeedReadSubProc);
				}
				while (GetAsyncKeyState(VK_F5));
			}

			if (GetAsyncKeyState(VK_F6)) {
				if (bPause) {
					bPause = false;
					//Restore original instruction byte code, this will prevent potential crashing.
					SadMemEdit::WriteBytes({ 0xF3, 0x0F, 0x10, 0x41, 0x58,0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC }, pGameSpeedReadSubProc);
				}
				if (!bSlowMo) {
					bSlowMo = true;
					DWORD64 pVirtualPage = SadMemEdit::AllocateMemory(128); //Allocate memory to write our custom function there.

					/*
					* Define our x86 assembly function, which makes the game read the current speed as 1e-8 which
					* is a very low value.
					* A value of zero sometimes results in a crash as well as broken animations/physics.
					*/
					SadMemEdit::WriteBytes({ 0x51,								//push rcx
						0x48, 0xB9, 0xA6, 0x9B, 0x44, 0x3B, 0x0, 0x0, 0x0, 0x0, //mov rcx,(float)0.003
						0x66, 0x48, 0x0F, 0x6E, 0xC1,							//movq xmm0,rcx
						0x59,													//pop rcx
						0xC3													//ret
						}, pVirtualPage);
					SadMemEdit::WriteFarJump(pVirtualPage + 0x12, pGameSpeedReadSubProc, 0); //jmp [pGameSpeedReadSubProc]
					/*
					* End of custom assembly function, the last line makes us return to the original instruction's location
					* when execution is complete.
					*/

					/*
					* Tell the original instruction to go to our virtual page, resulting in our custom code being executed.
					* Then once the execution is complete, everything that follows resumes normally.
					*/
					SadMemEdit::WriteFarJump(pGameSpeedReadSubProc, pVirtualPage, 0); //jmp [pVirtualPage]
				}
				else {
					bSlowMo = false;
					//Restore original byte code (the instruction now reads the actual game speed again).
					SadMemEdit::WriteBytes({ 0xF3, 0x0F, 0x10, 0x41, 0x58,0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC }, pGameSpeedReadSubProc);
				}
				while (GetAsyncKeyState(VK_F6));
			}

			if (GetAsyncKeyState(VK_F7)) {
				if (!bHQ) {
					bHQ = true;
					//Read Original Rendering settings and store them, so we can restore them later.
					memcpy(&nAntiAliasingMode, LPVOID(pAntiAliasingMode), 4);
					memcpy(&nMultiSampleMode, LPVOID(pMultiSampleMode), 4);
					memcpy(&nMultiSampleQualityLevel, LPVOID(pMultiSampleQualityLevel), 4);
					memcpy(&nShadowMapSize, LPVOID(pShadowMapSize), 4);
					memcpy(&nRainShadowMapSize, LPVOID(pRainShadowMapSize), 4);
					memcpy(&nCascadedShadowMapSize, LPVOID(pCascadedShadowMapSize), 4);
					memcpy(&nFSMShadowMapSize, LPVOID(pFSMShadowMapSize), 4);
					memcpy(&nStaticShadowMapSize, LPVOID(pStaticShadowMapSize), 4);
					memcpy(&nParaboloidReflectionTextureSize, LPVOID(pParaboloidReflectionTextureSize), 4);
					memcpy(&fKillLodScale, LPVOID(pKillLodScale), 4);
					memcpy(&fLodScale, LPVOID(pLodScale), 4);
					memcpy(&fRealTreesLodScale, LPVOID(pRealTreesLodScale), 4);
					memcpy(&fVegetationLodScale, LPVOID(pVegetationLodScale), 4);
					memcpy(&fFSMObjectMinSize, LPVOID(pFSMObjectMinSize), 4);
					memcpy(&fFSMRealTreeMinSize, LPVOID(pFSMRealTreeMinSize), 4);
					memcpy(&fSceneObjectMinSize, LPVOID(pSceneObjectMinSize), 4);
					memcpy(&fClusterObjectMinSize, LPVOID(pClusterObjectMinSize), 4);
					memcpy(&fClusterObjectMinSizeDetail, LPVOID(pClusterObjectMinSizeDetail), 4);
					memcpy(&fFSMShadowRange, LPVOID(pFSMShadowRange), 4);
					memcpy(&nShadowBilateralBlurNumSamples, LPVOID(pShadowBilateralBlurNumSamples), 4);
					memcpy(&nShadowBilateralBlurNumPasses, LPVOID(pShadowBilateralBlurNumPasses), 4);
					memcpy(&bSoftShadows, LPVOID(pSoftShadows), 1);
					memcpy(&bSuperSampling, LPVOID(pSuperSampling), 1);
					/*
					* We Set the Anti Aliasing Mode to Temporal SMAA.
					* This is due to MSAA/TXAA causing crashes when coupled with SuperSampling.
					*/
					memcpy(LPVOID(pAntiAliasingMode), &nAntiAliasingModeHQ, 4);
					memcpy(LPVOID(pMultiSampleMode), &nMultiSampleModeHQ, 4);
					memcpy(LPVOID(pMultiSampleQualityLevel), &nMultiSampleQualityLevelHQ, 4);
					/*
					* Now we must halt the game from rendering another frame.
					* Not doing so results in an almost certain crash because we are telling the game to render at twice the
					* resolution, possibly in the middle of a framejob.
					*/
					SadMemEdit::DisableInstruction(pCallRenderFrameSubProc, 5); //Don't make another call to render a frame.
					Sleep(500);
					memcpy(LPVOID(pSuperSampling), &bSuperSamplingHQ, 1); //Enable supersampling.
					Sleep(500);
					SadMemEdit::WriteBytes({ 0xE8, 0x45, 0xCC, 0x02, 0x00 }, pCallRenderFrameSubProc); //Continue rendering.
					//Apply all other rendering tweaks.
					memcpy(LPVOID(pShadowMapSize), &nMapSizeHQ, 4);
					memcpy(LPVOID(pRainShadowMapSize), &nRainShadowMapSizeHQ, 4);
					memcpy(LPVOID(pCascadedShadowMapSize), &nMapSizeHQ, 4);
					memcpy(LPVOID(pFSMShadowMapSize), &nMapSizeHQ, 4);
					memcpy(LPVOID(pStaticShadowMapSize), &nMapSizeHQ, 4);
					memcpy(LPVOID(pParaboloidReflectionTextureSize), &nMapSizeHQ, 4);
					memcpy(LPVOID(pKillLodScale), &fKillLodScaleHQ, 4);
					memcpy(LPVOID(pLodScale), &fLodScaleHQ, 4);
					memcpy(LPVOID(pRealTreesLodScale), &fLodScaleHQ, 4);
					memcpy(LPVOID(pVegetationLodScale), &fLodScaleHQ, 4);
					memcpy(LPVOID(pFSMObjectMinSize), &fObjectMinSizeHQ, 4);
					memcpy(LPVOID(pFSMRealTreeMinSize), &fObjectMinSizeHQ, 4);
					memcpy(LPVOID(pSceneObjectMinSize), &fObjectMinSizeHQ, 4);
					memcpy(LPVOID(pClusterObjectMinSize), &fObjectMinSizeHQ, 4);
					memcpy(LPVOID(pClusterObjectMinSizeDetail), &fObjectMinSizeHQ, 4);
					memcpy(LPVOID(pFSMShadowRange), &fFSMShadowRangeHQ, 4);
					memcpy(LPVOID(pShadowBilateralBlurNumSamples), &nShadowBilateralBlurNumSamplesHQ, 4);
					memcpy(LPVOID(pShadowBilateralBlurNumPasses), &nShadowBilateralBlurNumPassesHQ, 4);
					memcpy(LPVOID(pSoftShadows), &bSoftShadowsHQ, 1);
				}
				else {
					bHQ = false;
					/*
					* We still need to halt the game from rendering another frame when disabling supersampling as well
					* Not doing so results in an almost certain crash because we are telling the game to render at half the
					* resolution yada yada framejob yada yada.
					*/
					SadMemEdit::DisableInstruction(pCallRenderFrameSubProc, 5); //..
					Sleep(500);
					//Disable supersampling (or keep it on if the user already had it on).
					memcpy(LPVOID(pSuperSampling), &bSuperSampling, 1);
					Sleep(500);
					SadMemEdit::WriteBytes({ 0xE8, 0x45, 0xCC, 0x02, 0x00 }, pCallRenderFrameSubProc); //...
					//Restore all other rendering settings.
					memcpy(LPVOID(pShadowMapSize), &nShadowMapSize, 4);
					memcpy(LPVOID(pRainShadowMapSize), &nRainShadowMapSize, 4);
					memcpy(LPVOID(pCascadedShadowMapSize), &nCascadedShadowMapSize, 4);
					memcpy(LPVOID(pFSMShadowMapSize), &nFSMShadowMapSize, 4);
					memcpy(LPVOID(pStaticShadowMapSize), &nStaticShadowMapSize, 4);
					memcpy(LPVOID(pParaboloidReflectionTextureSize), &nParaboloidReflectionTextureSize, 4);
					memcpy(LPVOID(pKillLodScale), &fKillLodScale, 4);
					memcpy(LPVOID(pLodScale), &fLodScale, 4);
					memcpy(LPVOID(pRealTreesLodScale), &fRealTreesLodScale, 4);
					memcpy(LPVOID(pVegetationLodScale), &fVegetationLodScale, 4);
					memcpy(LPVOID(pFSMObjectMinSize), &fFSMObjectMinSize, 4);
					memcpy(LPVOID(pFSMRealTreeMinSize), &fFSMRealTreeMinSize, 4);
					memcpy(LPVOID(pSceneObjectMinSize), &fSceneObjectMinSize, 4);
					memcpy(LPVOID(pClusterObjectMinSize), &fClusterObjectMinSize, 4);
					memcpy(LPVOID(pClusterObjectMinSizeDetail), &fClusterObjectMinSizeDetail, 4);
					memcpy(LPVOID(pFSMShadowRange), &fFSMShadowRange, 4);
					memcpy(LPVOID(pShadowBilateralBlurNumPasses), &nShadowBilateralBlurNumPasses, 4);
					memcpy(LPVOID(pShadowBilateralBlurNumSamples), &nShadowBilateralBlurNumSamples, 4);
					memcpy(LPVOID(pSoftShadows), &bSoftShadows, 1);
					memcpy(LPVOID(pAntiAliasingMode), &nAntiAliasingMode, 4);
					memcpy(LPVOID(pMultiSampleMode), &nMultiSampleMode, 4);
					memcpy(LPVOID(pMultiSampleQualityLevel), &nMultiSampleQualityLevel, 4);
				}
				while (GetAsyncKeyState(VK_F7));
			}

			//Update time of day (in case we changed it).
			memcpy(LPVOID(pTimeOfDay), &fTimeOfDay, 4);
		}
		Sleep(4);
	}
}