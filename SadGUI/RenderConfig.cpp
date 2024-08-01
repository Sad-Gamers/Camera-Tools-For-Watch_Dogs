#include "RenderConfig.h"
#include "CameraToolMonitor.h"

void RenderConfig::ApplyConfig(RenderConfigPreset Config) {
	uintptr_t Imagebase = Misc::Imagebase;
	uintptr_t RenderConfig = GetRenderConfig();
	Misc::StopFrameJobs = true;
	*(bool*)(RenderConfig + o_SuperSampling) = Config.SuperSampling;
	*(bool*)(RenderConfig + o_SoftShadows) = Config.SoftShadows;
	*(bool*)(RenderConfig + o_EnableCSMShadows) = Config.EnableCSMShadows;
	*(int*)(RenderConfig + o_ParaboloidReflectionTextureSize) = Config.ParaboloidReflectionTextureSize;
	*(int*)(RenderConfig + o_ShadowMapSize) = Config.ShadowMapSize;
	*(int*)(RenderConfig + o_CascadedShadowMapSize) = Config.CascadedShadowMapSize;
	*(int*)(RenderConfig + o_ShadowBilateralBlurNumPasses) = Config.ShadowBilateralBlurNumPasses;
	*(int*)(RenderConfig + o_ShadowBilateralBlurNumSamples) = Config.ShadowBilateralBlurNumSamples;
	*(int*)(RenderConfig + o_FSMShadowMapSize) = Config.FSMShadowMapSize;
	*(int*)(RenderConfig + o_AntiAliasingMode) = Config.AntiAliasingMode;
	*(int*)(RenderConfig + o_MultiSampleMode) = Config.MultiSampleMode;
	*(int*)(RenderConfig + o_MultiSampleQualityLevel) = Config.MultiSampleQualityLevel;
	*(float*)(RenderConfig + o_RealTreesLodScale) = Config.RealTreesLodScale;
	*(float*)(RenderConfig + o_ClustersLodScale) = Config.ClustersLodScale;
	*(float*)(RenderConfig + o_LodScale) = Config.LodScale;
	*(float*)(RenderConfig + o_KillLodScale) = Config.KillLodScale;
	*(float*)(RenderConfig + o_BuildingKillLodScale) = Config.BuildingKillLodScale;
	*(float*)(RenderConfig + o_ClusterObjectMinSize) = Config.ClusterObjectMinSize;
	*(float*)(RenderConfig + o_ClusterObjectMinSizeDetail) = Config.ClusterObjectMinSizeDetail;
	*(float*)(RenderConfig + o_SceneObjectMinSize) = Config.SceneObjectMinSize;
	*(float*)(RenderConfig + o_FSMObjectMinSize) = Config.FSMObjectMinSize;
	*(float*)(RenderConfig + o_FSMObjectMinSize) = Config.FSMObjectMinSize;
	*(float*)(RenderConfig + o_FSMShadowRange) = Config.FSMShadowRange;
	*(float*)(RenderConfig + o_FSMShadowQuality) = Config.FSMShadowQuality;
	*(int*)(RenderConfig + o_WaterReflectionTextureSize) = Config.WaterReflectionTextureSize;
	*(DirectX::XMFLOAT3*)(RenderConfig + o_CSMRealTreeMinSize) = Config.CSMRealTreeMinSize;
	*(DirectX::XMFLOAT3*)(RenderConfig + o_CSMObjectMinSize) = Config.CSMObjectMinSize;
	*(float*)(RenderConfig + o_CSMDepthBias) = Config.CSMDepthBias.x;
	*(float*)(RenderConfig + o_CSMDepthBias + 0x8) = Config.CSMDepthBias.y;
	*(float*)(RenderConfig + o_CSMDepthBias + 0x10) = Config.CSMDepthBias.z;
	*(float*)(RenderConfig + o_CSMSlopeScaleDepthBias) = Config.CSMSlopeScaleDepthBias.x;
	*(float*)(RenderConfig + o_CSMSlopeScaleDepthBias + 0x8) = Config.CSMSlopeScaleDepthBias.y;
	*(float*)(RenderConfig + o_CSMSlopeScaleDepthBias + 0x10) = Config.CSMSlopeScaleDepthBias.z;
	*(float*)(RenderConfig + o_FSMObjectFadeRangeFactor) = Config.FSMObjectFadeRangeFactor;
	*(float*)(RenderConfig + o_FSMDepthBias) = Config.FSMDepthBias;
	*(float*)(RenderConfig + o_FSMShadowFadeStart) = Config.FSMShadowFadeStart;
	*(float*)(RenderConfig + o_FSMShadowFadeEnd) = Config.FSMShadowFadeEnd;
	*(bool*)(RefreshByte) = true;
}


void RenderConfig::Initialize() {
	uintptr_t RenderConfig = GetRenderConfig();
	uintptr_t Imagebase = Misc::Imagebase;
	if (RenderConfig) {
		RefreshByte = ((*(uintptr_t*)((Imagebase + Offsets::RenderConfig)) + o_RefreshByte));
		UserRenderConfig.SuperSampling = *(bool*)(RenderConfig + o_SuperSampling);
		UserRenderConfig.SoftShadows = *(bool*)(RenderConfig + o_SoftShadows);
		UserRenderConfig.EnableCSMShadows = *(bool*)(RenderConfig + o_EnableCSMShadows);
		UserRenderConfig.ParaboloidReflectionTextureSize = *(int*)(RenderConfig + o_ParaboloidReflectionTextureSize);
		UserRenderConfig.ShadowMapSize = *(int*)(RenderConfig + o_ShadowMapSize);
		UserRenderConfig.CascadedShadowMapSize = *(int*)(RenderConfig + o_CascadedShadowMapSize);
		UserRenderConfig.ShadowBilateralBlurNumPasses = *(int*)(RenderConfig + o_ShadowBilateralBlurNumPasses);
		UserRenderConfig.ShadowBilateralBlurNumSamples = *(int*)(RenderConfig + o_ShadowBilateralBlurNumSamples);
		UserRenderConfig.FSMShadowMapSize = *(int*)(RenderConfig + o_FSMShadowMapSize);
		UserRenderConfig.AntiAliasingMode = *(int*)(RenderConfig + o_AntiAliasingMode);
		UserRenderConfig.MultiSampleMode = *(int*)(RenderConfig + o_MultiSampleMode);
		UserRenderConfig.MultiSampleQualityLevel = *(int*)(RenderConfig + o_MultiSampleQualityLevel);
		UserRenderConfig.RealTreesLodScale = *(float*)(RenderConfig + o_RealTreesLodScale);
		UserRenderConfig.ClustersLodScale = *(float*)(RenderConfig + o_ClustersLodScale);
		UserRenderConfig.LodScale = *(float*)(RenderConfig + o_LodScale);
		UserRenderConfig.KillLodScale = *(float*)(RenderConfig + o_KillLodScale);
		UserRenderConfig.BuildingKillLodScale = *(float*)(RenderConfig + o_BuildingKillLodScale);
		UserRenderConfig.ClusterObjectMinSize = *(float*)(RenderConfig + o_ClusterObjectMinSize);
		UserRenderConfig.ClusterObjectMinSizeDetail = *(float*)(RenderConfig + o_ClusterObjectMinSizeDetail);
		UserRenderConfig.SceneObjectMinSize = *(float*)(RenderConfig + o_SceneObjectMinSize);
		UserRenderConfig.FSMObjectMinSize = *(float*)(RenderConfig + o_FSMObjectMinSize);
		UserRenderConfig.FSMRealTreeMinSize = *(float*)(RenderConfig + o_FSMRealTreeMinSize);
		UserRenderConfig.CSMRealTreeMinSize = *(DirectX::XMFLOAT3*)(RenderConfig + o_CSMRealTreeMinSize);
		UserRenderConfig.CSMObjectMinSize = *(DirectX::XMFLOAT3*)(RenderConfig + o_CSMObjectMinSize);
		UserRenderConfig.FSMShadowRange = *(float*)(RenderConfig + o_FSMShadowRange);
		UserRenderConfig.FSMShadowQuality = *(float*)(RenderConfig + o_FSMShadowQuality);
		UserRenderConfig.WaterReflectionTextureSize = *(int*)(RenderConfig + o_WaterReflectionTextureSize);
		UserRenderConfig.CSMRealTreeMinSize = *(DirectX::XMFLOAT3*)(RenderConfig + o_CSMRealTreeMinSize);
		UserRenderConfig.CSMObjectMinSize = *(DirectX::XMFLOAT3*)(RenderConfig + o_CSMObjectMinSize);
		UserRenderConfig.CSMDepthBias.x = *(float*)(RenderConfig + o_CSMDepthBias);
		UserRenderConfig.CSMDepthBias.y = *(float*)(RenderConfig + o_CSMDepthBias + 0x8);
		UserRenderConfig.CSMDepthBias.z = *(float*)(RenderConfig + o_CSMDepthBias + 0x10);
		UserRenderConfig.CSMSlopeScaleDepthBias.x = *(float*)(RenderConfig + o_CSMSlopeScaleDepthBias);
		UserRenderConfig.CSMSlopeScaleDepthBias.y = *(float*)(RenderConfig + o_CSMSlopeScaleDepthBias + 0x8);
		UserRenderConfig.CSMSlopeScaleDepthBias.z = *(float*)(RenderConfig + o_CSMSlopeScaleDepthBias + 0x10);
		UserRenderConfig.FSMObjectFadeRangeFactor = *(float*)(RenderConfig + o_FSMObjectFadeRangeFactor);
		UserRenderConfig.FSMDepthBias = *(float*)(RenderConfig + o_FSMDepthBias);
		UserRenderConfig.FSMShadowFadeStart = *(float*)(RenderConfig + o_FSMShadowFadeStart);
		UserRenderConfig.FSMShadowFadeEnd = *(float*)(RenderConfig + o_FSMShadowFadeEnd);
		Initialized = true;
	}
}

void RenderConfig::InitializeSuperRenderingPreset() {
	SuperRenderConfig.SuperSampling = true;
	SuperRenderConfig.SoftShadows = true;
	SuperRenderConfig.EnableCSMShadows = true;
	SuperRenderConfig.ParaboloidReflectionTextureSize = 8192;
	SuperRenderConfig.ShadowMapSize = 8192;
	SuperRenderConfig.CascadedShadowMapSize = 5000;
	SuperRenderConfig.ShadowBilateralBlurNumPasses = 4;
	SuperRenderConfig.ShadowBilateralBlurNumSamples = 8;
	SuperRenderConfig.FSMShadowMapSize = 8192;
	SuperRenderConfig.AntiAliasingMode = 5;
	SuperRenderConfig.MultiSampleMode = 0;
	SuperRenderConfig.MultiSampleQualityLevel = 0;
	SuperRenderConfig.RealTreesLodScale = 0.001f;
	SuperRenderConfig.ClustersLodScale = 0.001f;
	SuperRenderConfig.LodScale = 0.001f;
	SuperRenderConfig.KillLodScale = 0.01f;
	SuperRenderConfig.BuildingKillLodScale = 0.01f;
	SuperRenderConfig.ClusterObjectMinSize = 0.0f;
	SuperRenderConfig.ClusterObjectMinSizeDetail = 0.0f;
	SuperRenderConfig.SceneObjectMinSize = 0.0f;
	SuperRenderConfig.FSMObjectMinSize = 0.0f;
	SuperRenderConfig.FSMRealTreeMinSize = 0.0f;
	SuperRenderConfig.CSMRealTreeMinSize = { 0.0f , 0.0f, 0.0f };
	SuperRenderConfig.CSMObjectMinSize = { 0.0f, 0.0f, 0.0f };
	SuperRenderConfig.FSMShadowRange = 800;
	SuperRenderConfig.FSMShadowQuality = 25;
	SuperRenderConfig.WaterReflectionTextureSize = 2000;
	SuperRenderConfig.CSMRealTreeMinSize = { 0.0f, 0.0f, 0.0f };
	SuperRenderConfig.CSMObjectMinSize = { 0.0f, 0.0f, 0.0f };
	SuperRenderConfig.CSMDepthBias.x = 0.0005f;
	SuperRenderConfig.CSMDepthBias.y = 0.0005f;
	SuperRenderConfig.CSMDepthBias.z = 0.0005f;
	SuperRenderConfig.CSMSlopeScaleDepthBias.x = 1;
	SuperRenderConfig.CSMSlopeScaleDepthBias.y = 1;
	SuperRenderConfig.CSMSlopeScaleDepthBias.z = 1;
	SuperRenderConfig.FSMObjectFadeRangeFactor = 0;
	SuperRenderConfig.FSMDepthBias = 0.0001f;
	SuperRenderConfig.FSMShadowFadeStart = 0.1f;
	SuperRenderConfig.FSMShadowFadeEnd = 0.0f;
}

void RenderConfig::SaveOriginalConfig() {
	uintptr_t RenderConfig = GetRenderConfig();
	oRenderConfig.SuperSampling = *(bool*)(RenderConfig + o_SuperSampling);
	oRenderConfig.SoftShadows = *(bool*)(RenderConfig + o_SoftShadows);
	oRenderConfig.EnableCSMShadows = *(bool*)(RenderConfig + o_EnableCSMShadows);
	oRenderConfig.ParaboloidReflectionTextureSize = *(int*)(RenderConfig + o_ParaboloidReflectionTextureSize);
	oRenderConfig.ShadowMapSize = *(int*)(RenderConfig + o_ShadowMapSize);
	oRenderConfig.CascadedShadowMapSize = *(int*)(RenderConfig + o_CascadedShadowMapSize);
	oRenderConfig.ShadowBilateralBlurNumPasses = *(int*)(RenderConfig + o_ShadowBilateralBlurNumPasses);
	oRenderConfig.ShadowBilateralBlurNumSamples = *(int*)(RenderConfig + o_ShadowBilateralBlurNumSamples);
	oRenderConfig.FSMShadowMapSize = *(int*)(RenderConfig + o_FSMShadowMapSize);
	oRenderConfig.AntiAliasingMode = *(int*)(RenderConfig + o_AntiAliasingMode);
	oRenderConfig.MultiSampleMode = *(int*)(RenderConfig + o_MultiSampleMode);
	oRenderConfig.MultiSampleQualityLevel = *(int*)(RenderConfig + o_MultiSampleQualityLevel);
	oRenderConfig.RealTreesLodScale = *(float*)(RenderConfig + o_RealTreesLodScale);
	oRenderConfig.ClustersLodScale = *(float*)(RenderConfig + o_ClustersLodScale);
	oRenderConfig.LodScale = *(float*)(RenderConfig + o_LodScale);
	oRenderConfig.KillLodScale = *(float*)(RenderConfig + o_KillLodScale);
	oRenderConfig.BuildingKillLodScale = *(float*)(RenderConfig + o_BuildingKillLodScale);
	oRenderConfig.ClusterObjectMinSize = *(float*)(RenderConfig + o_ClusterObjectMinSize);
	oRenderConfig.ClusterObjectMinSizeDetail = *(float*)(RenderConfig + o_ClusterObjectMinSizeDetail);
	oRenderConfig.SceneObjectMinSize = *(float*)(RenderConfig + o_SceneObjectMinSize);
	oRenderConfig.FSMObjectMinSize  = *(float*)(RenderConfig + o_FSMObjectMinSize);
	oRenderConfig.FSMRealTreeMinSize = *(float*)(RenderConfig + o_FSMRealTreeMinSize);
	oRenderConfig.CSMRealTreeMinSize = *(DirectX::XMFLOAT3*)(RenderConfig + o_CSMRealTreeMinSize);
	oRenderConfig.CSMObjectMinSize = *(DirectX::XMFLOAT3*)(RenderConfig + o_CSMObjectMinSize);
	oRenderConfig.FSMShadowRange = *(float*)(RenderConfig + o_FSMShadowRange);
	oRenderConfig.FSMShadowQuality = *(float*)(RenderConfig + o_FSMShadowQuality);
	oRenderConfig.WaterReflectionTextureSize = *(int*)(RenderConfig + o_WaterReflectionTextureSize);
	oRenderConfig.CSMRealTreeMinSize = *(DirectX::XMFLOAT3*)(RenderConfig + o_CSMRealTreeMinSize);
	oRenderConfig.CSMObjectMinSize = *(DirectX::XMFLOAT3*)(RenderConfig + o_CSMObjectMinSize);
	oRenderConfig.CSMDepthBias.x = *(float*)(RenderConfig + o_CSMDepthBias);
	oRenderConfig.CSMDepthBias.y = *(float*)(RenderConfig + o_CSMDepthBias + 0x8);
	oRenderConfig.CSMDepthBias.z = *(float*)(RenderConfig + o_CSMDepthBias + 0x10);
	oRenderConfig.CSMSlopeScaleDepthBias.x = *(float*)(RenderConfig + o_CSMSlopeScaleDepthBias);
	oRenderConfig.CSMSlopeScaleDepthBias.y = *(float*)(RenderConfig + o_CSMSlopeScaleDepthBias + 0x8);
	oRenderConfig.CSMSlopeScaleDepthBias.z = *(float*)(RenderConfig + o_CSMSlopeScaleDepthBias + 0x10);
	oRenderConfig.FSMObjectFadeRangeFactor = *(float*)(RenderConfig + o_FSMObjectFadeRangeFactor);
	oRenderConfig.FSMDepthBias = *(float*)(RenderConfig + o_FSMDepthBias);
	oRenderConfig.FSMShadowFadeStart = *(float*)(RenderConfig + o_FSMShadowFadeStart);
	oRenderConfig.FSMShadowFadeEnd = *(float*)(RenderConfig + o_FSMShadowFadeEnd);
}

void RenderConfig::Revert() {
	uintptr_t RenderConfig = GetRenderConfig();
	UserRenderConfig = oRenderConfig;
	ApplyConfig(UserRenderConfig);
}


uintptr_t RenderConfig::GetRenderConfig() {
	uintptr_t Imagebase = Misc::Imagebase;
	return ((*(uintptr_t*)((*(uintptr_t*)(Imagebase + Offsets::RenderConfig)) + 0x20) + 0x0));
}