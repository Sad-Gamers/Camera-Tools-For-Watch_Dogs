#include "SadHook.h"

class DisruptHook {
public:
	static void Initialize();
	static void DisruptHookUpdate();
	typedef void (*SendShowOrHideAllUIEvent_t)(int); //Internal Function for controlling UI visibility. 
	inline static SendShowOrHideAllUIEvent_t SendShowOrHideAllUIEvent;

	//Miscellaneous variables.
	inline static int bCameraLoaded, bGameLoading;
	inline static bool bUIVisibile, bPause, bHQ, bSlowMo;
	inline static float fTimeOfDay;
	inline static float fTransitionDuration;
	inline static int nEnvironmentPreset;
	inline static float fMouseDisplacementX, fMouseDisplacementY;

	//Variables that we will use to store the original render settings.
	inline static bool bSuperSampling, bSoftShadows;
	inline static float fRealTreesLodScale, fKillLodScale, fLodScale, fVegetationLodScale;
	inline static float fClusterObjectMinSize, fClusterObjectMinSizeDetail, fSceneObjectMinSize;
	inline static float fFSMObjectMinSize, fFSMRealTreeMinSize, fFSMShadowRange;
	inline static int nShadowMapSize, nCascadedShadowMapSize, nRainShadowMapSize, nFSMShadowMapSize, nStaticShadowMapSize;
	inline static int nShadowBilateralBlurNumSamples, nShadowBilateralBlurNumPasses;
	inline static int nParaboloidReflectionTextureSize;

	//Variables that we will hold the values for the super render settings.
	inline static bool bSuperSamplingHQ, bSoftShadowsHQ;
	inline static float  fKillLodScaleHQ, fLodScaleHQ;
	inline static float fObjectMinSizeHQ;
	inline static float fFSMShadowRangeHQ;
	inline static int nShadowBilateralBlurNumSamplesHQ, nShadowBilateralBlurNumPassesHQ;
	inline static int nMapSizeHQ, nRainShadowMapSizeHQ;
	inline static int nAntiAliasingMode, nMultiSampleMode, nMultiSampleQualityLevel;
	inline static int nAntiAliasingModeHQ, nMultiSampleModeHQ, nMultiSampleQualityLevelHQ;

	//Pointers to miscellaneous functions / instructions.
	inline static DWORD64 pReadActionMapEnum;
	inline static DWORD64 pCallRenderFrameSubProc;
	inline static DWORD64 pGameSpeedReadSubProc;

	//Pointers to miscellaneous floats and booleans.
	inline static DWORD64 pMouseDisplacement, pMouseDisplacementX, pMouseDisplacementY;
	inline static DWORD64 pCameraLoaded, pGameLoading;
	inline static DWORD64 pTimeOfDay, pEnvironmentPreset, pTransitionDuration;

	//Pointers to rendering settings. 
	inline static DWORD64 pRenderConfig;
	inline static DWORD64 pSuperSampling;
	inline static DWORD64 pAntiAliasingMode, pMultiSampleMode, pMultiSampleQualityLevel;
	inline static DWORD64 pRealTreesLodScale, pKillLodScale, pLodScale, pVegetationLodScale;
	inline static DWORD64 pClusterObjectMinSize, pClusterObjectMinSizeDetail, pSceneObjectMinSize;
	inline static DWORD64 pFSMObjectMinSize, pFSMRealTreeMinSize;
	inline static DWORD64 pShadowMapSize, pCascadedShadowMapSize, pRainShadowMapSize, pFSMShadowMapSize, pStaticShadowMapSize;
	inline static DWORD64 pFSMShadowRange, pSoftShadows, pShadowBilateralBlurNumSamples, pShadowBilateralBlurNumPasses;
	inline static DWORD64 pParaboloidReflectionTextureSize;

	//Pointers to camera floats and booleans.
	inline static DWORD64 pLensDOFEnabled, pLensStruct, pLensConditionals, pLensFloats;
	inline static DWORD64 pCameraStruct, pCameraPosition, pViewMatrix, pCameraFOV;

	//Pointers to camera functions / instructions.
	inline static DWORD64 pCameraPositionSubProc, pViewMatrixSubProc, pCameraFOVWrite, pCallMoveReticleSubProc;
	inline static DWORD64 pLensRenderpassSubProc1, pLensRenderpassSubProc2, pLensRenderpassSubProc3;
};