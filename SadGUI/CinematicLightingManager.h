#pragma once
#include "GlobalHeaders.h"
#include "CinematicLight.h"


class CinematicLightingManager
{
public:
	static void InitializeCinematicLights();

	static void LoadCinematicLights();

	static void UpdateAllCinematicLightPositions();

	static void RemoveAllCinematicLights();

	static bool MuzzleFlashPresent();
	static bool FaceLightPresent();
	static bool AreaLightPresent();
	static bool SpotlightPresent();

	static void PlaceMuzzleFlash();
	static void PlaceFaceLight();
	static void PlaceAreaLight();
	static void PlaceSpotlight();

	inline static CinematicLight WhiteAreaLight;
	inline static CinematicLight WarmAreaLight;
	inline static CinematicLight ColdAreaLight;

	inline static const char* FaceLightType;
	inline static const char* AreaLightType;
	inline static const char* SpotlightType;

	inline static bool RemoveSpotlight;
	inline static bool RemoveAreaLight;
	inline static bool RemoveFaceLight;
	inline static bool RemoveMuzzleFlash;
	inline static bool MaintainFaceLightPosition;
	inline static bool MaintainAreaLightPosition;
	inline static bool MaintainSpotlightPosition;

	inline static DirectX::XMFLOAT3 MuzzleFlashPosition;
	inline static DirectX::XMFLOAT3 MuzzleFlashRotation;

	inline static DirectX::XMFLOAT3 FaceLightPosition;
	inline static DirectX::XMFLOAT3 FaceLightRotation;

	inline static DirectX::XMFLOAT3 AreaLightPosition;
	inline static DirectX::XMFLOAT3 AreaLightRotation;

	inline static DirectX::XMFLOAT3 SpotlightPosition;
	inline static DirectX::XMFLOAT3 SpotlightRotation;

	inline static CinematicLight WhiteFaceLight;
	inline static CinematicLight WarmFaceLight;
	inline static CinematicLight ColdFaceLight;

	inline static CinematicLight WhiteSpotlight;
	inline static CinematicLight WarmSpotlight;
	inline static CinematicLight ColdSpotlight;

	inline static CinematicLight MuzzleFlash;
};