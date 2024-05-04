#pragma once
#include "GlobalHeaders.h"

#define o_RefreshByte 0x29

#define o_SuperSampling 0x2F4
#define o_SoftShadows 0x9F0
#define o_ParaboloidReflectionTextureSize 0x6B4
#define o_WaterReflectionTextureSize 0x648

#define o_AntiAliasingMode 0xD50
#define o_MultiSampleMode 0xD54
#define o_MultiSampleQualityLevel 0xD58

#define o_ShadowMapSize 0x9E0
#define o_CascadedShadowMapSize 0x9E4

#define o_ShadowBilateralBlurNumPasses 0xA60
#define o_ShadowBilateralBlurNumSamples 0xA64

#define o_EnableCSMShadows 0x9D0

#define o_CSMDepthBias  0xA10
#define o_CSMSlopeScaleDepthBias  0xA14
#define o_CSMObjectMinSize  0xA28
#define o_CSMRealTreeMinSize 0xA34

#define o_FSMShadowMapSize 0xA70
#define o_FSMDepthBias 0xA74
#define o_FSMShadowRange 0xA7C
#define o_FSMShadowQuality 0xA80
#define o_FSMShadowFadeStart 0xA84
#define o_FSMShadowFadeEnd 0xA88
#define o_FSMObjectFadeRangeFactor 0xA90

#define o_StaticShadowMapSize 0xA54

#define o_KillLodScale 0x870
#define o_BuildingKillLodScale 0x874

#define o_RealTreesLodScale 0x858
#define o_ClustersLodScale 0x85C
#define o_LodScale 0x860

#define o_FSMObjectMinSize 0x8CC
#define o_FSMRealTreeMinSize 0x8D0

#define o_ClusterObjectMinSize 0x8A4
#define o_ClusterObjectMinSizeDetail 0x8AC
#define o_SceneObjectMinSize 0x8B0

class RenderConfig
{
public:
	inline static struct RenderConfigPreset{
		bool SuperSampling;
		bool SoftShadows;
		bool EnableCSMShadows;
		int ParaboloidReflectionTextureSize;
		int WaterReflectionTextureSize;
		int ShadowMapSize;
		int CascadedShadowMapSize;
		int RainShadowMapSize;
		int ShadowBilateralBlurNumPasses;
		int ShadowBilateralBlurNumSamples;
		int FSMShadowMapSize;
		int AntiAliasingMode;
		int MultiSampleMode;
		int MultiSampleQualityLevel;
		float RealTreesLodScale;
		float ClustersLodScale;
		float LodScale;
		float KillLodScale;
		float BuildingKillLodScale;
		float ClusterObjectMinSize;
		float ClusterObjectMinSizeDetail; 
		float SceneObjectMinSize;
		float FSMObjectMinSize;
		float FSMRealTreeMinSize;
		float FSMDepthBias;
		float FSMShadowRange;
		float FSMShadowQuality;
		float FSMShadowFadeStart;
		float FSMShadowFadeEnd;
		float FSMObjectFadeRangeFactor;
		DirectX::XMFLOAT3 CSMDepthBias;
		DirectX::XMFLOAT3 CSMSlopeScaleDepthBias;
		DirectX::XMFLOAT3 CSMObjectMinSize;
		DirectX::XMFLOAT3 CSMRealTreeMinSize;
	} oRenderConfig, UserRenderConfig, SuperRenderConfig;

	static void Initialize();
	static void InitializeSuperRenderingPreset();
	static void Revert();
	inline static bool Initialized;
	static void ApplyConfig(RenderConfigPreset Config);
	static void SaveOriginalConfig();
	static uintptr_t GetRenderConfig();
	inline static uintptr_t RefreshByte;
};