#include "CinematicLightingManager.h"
#include "CameraManager.h"

void CinematicLightingManager::InitializeCinematicLights()
{
	WhiteAreaLight = CinematicLight(72057594037928108);
	WarmAreaLight = CinematicLight(144115188075856044);
	ColdAreaLight = CinematicLight(216172782113783980);

	AreaLightType = "White";
	FaceLightType = "White";
	SpotlightType = "White";

	WhiteFaceLight = CinematicLight(288230376151711916);
	WarmFaceLight = CinematicLight(360287970189639852);
	ColdFaceLight = CinematicLight(432345564227567788);

	WhiteSpotlight = CinematicLight(504403158265495724);
	WarmSpotlight = CinematicLight(576460752303423660);
	ColdSpotlight = CinematicLight(648518346341351596);

	MuzzleFlash = CinematicLight(1152921504606847148);
}


void CinematicLightingManager::PlaceAreaLight()
{
	if (AreaLightPresent()) {
		RemoveAreaLight = true;
		UpdateAllCinematicLightPositions();
	}
	if (AreaLightType == "White")
		WhiteAreaLight.Place(&AreaLightPosition, &AreaLightRotation, MaintainAreaLightPosition);
	if (AreaLightType == "Warm")
		WarmAreaLight.Place(&AreaLightPosition, &AreaLightRotation, MaintainAreaLightPosition);
	if (AreaLightType == "Cool")
		ColdAreaLight.Place(&AreaLightPosition, &AreaLightRotation, MaintainAreaLightPosition);
	MaintainAreaLightPosition = false;
}

void CinematicLightingManager::PlaceFaceLight()
{
	if (FaceLightPresent()) {
		RemoveFaceLight = true;
		UpdateAllCinematicLightPositions();
	}
	if (FaceLightType == "White")
		WhiteFaceLight.Place(&FaceLightPosition, &FaceLightRotation, MaintainFaceLightPosition);
	if (FaceLightType == "Warm")
		WarmFaceLight.Place(&FaceLightPosition, &FaceLightRotation, MaintainFaceLightPosition);
	if (FaceLightType == "Cool")
		ColdFaceLight.Place(&FaceLightPosition, &FaceLightRotation, MaintainFaceLightPosition);
	MaintainFaceLightPosition = false;
}

void CinematicLightingManager::PlaceSpotlight()
{
	if (SpotlightPresent()) {
		RemoveSpotlight = true;
		UpdateAllCinematicLightPositions();
	}
	if (SpotlightType == "White")
		WhiteSpotlight.Place(&SpotlightPosition, &SpotlightRotation, MaintainSpotlightPosition);
	if (SpotlightType == "Warm")
		WarmSpotlight.Place(&SpotlightPosition, &SpotlightRotation, MaintainSpotlightPosition);
	if (SpotlightType == "Cool")
		ColdSpotlight.Place(&SpotlightPosition, &SpotlightRotation, MaintainSpotlightPosition);
	MaintainSpotlightPosition = false;
}

void CinematicLightingManager::PlaceMuzzleFlash()
{
	MuzzleFlash.Place(&MuzzleFlashPosition, &MuzzleFlashRotation, false);
}

void CinematicLightingManager::UpdateAllCinematicLightPositions()
{
	DirectX::XMFLOAT3 BlankVector = { 0, 0 , 0 };
	if (RemoveFaceLight) {
		WhiteFaceLight.UpdatePosition(BlankVector);
		WhiteFaceLight.UpdateRotation(BlankVector);
		WarmFaceLight.UpdatePosition(BlankVector);
		WarmFaceLight.UpdateRotation(BlankVector);
		ColdFaceLight.UpdatePosition(BlankVector);
		ColdFaceLight.UpdateRotation(BlankVector);
		if (!MaintainFaceLightPosition) {
			FaceLightPosition = BlankVector;
			FaceLightRotation = BlankVector;
		}
		RemoveFaceLight = false;
	}
	else 
	{
		if (FaceLightType == "White")
			FaceLightPosition = WhiteFaceLight.UpdatePosition(FaceLightPosition);
		if (FaceLightType == "Warm")
			FaceLightPosition = WarmFaceLight.UpdatePosition(FaceLightPosition);
		if (FaceLightType == "Cool")
			FaceLightPosition = ColdFaceLight.UpdatePosition(FaceLightPosition);
	}

	if (RemoveAreaLight) {
		WhiteAreaLight.UpdatePosition(BlankVector);
		WhiteAreaLight.UpdateRotation(BlankVector);
		WarmAreaLight.UpdatePosition(BlankVector);
		WarmAreaLight.UpdateRotation(BlankVector);
		ColdAreaLight.UpdatePosition(BlankVector);
		ColdAreaLight.UpdateRotation(BlankVector);
		if (!MaintainAreaLightPosition) {
			AreaLightPosition = BlankVector;
			AreaLightRotation = BlankVector;
		}
		RemoveAreaLight = false;
	}
	else
	{
		if (AreaLightType == "White")
			AreaLightPosition = WhiteAreaLight.UpdatePosition(AreaLightPosition);
		if (AreaLightType == "Warm")
			AreaLightPosition = WarmAreaLight.UpdatePosition(AreaLightPosition);
		if (AreaLightType == "Cool")
			AreaLightPosition = ColdAreaLight.UpdatePosition(AreaLightPosition);
	}

	if (RemoveSpotlight) {
		WhiteSpotlight.UpdatePosition(BlankVector);
		WhiteSpotlight.UpdateRotation(BlankVector);
		WarmSpotlight.UpdatePosition(BlankVector);
		WarmSpotlight.UpdateRotation(BlankVector);
		ColdSpotlight.UpdatePosition(BlankVector);
		ColdSpotlight.UpdateRotation(BlankVector);
		if (!MaintainSpotlightPosition) {
			SpotlightPosition = BlankVector;
			SpotlightRotation = BlankVector;
		}
		RemoveSpotlight = false;
	}
	else
	{
		if (SpotlightType == "White") {
			SpotlightPosition = WhiteSpotlight.UpdatePosition(SpotlightPosition);
			SpotlightRotation = WhiteSpotlight.UpdateRotation(SpotlightRotation);
		}
		if (SpotlightType == "Warm") {
			SpotlightPosition = WarmSpotlight.UpdatePosition(SpotlightPosition);
			SpotlightRotation = WarmSpotlight.UpdateRotation(SpotlightRotation);
		}
		if (SpotlightType == "Cool") {
			SpotlightPosition = ColdSpotlight.UpdatePosition(SpotlightPosition);
			SpotlightRotation = ColdSpotlight.UpdateRotation(SpotlightRotation);
		}

	}

	if (RemoveMuzzleFlash) {
		MuzzleFlashPosition = BlankVector;
		MuzzleFlashRotation = BlankVector;
		RemoveMuzzleFlash = false;
	}
	else
	{
		MuzzleFlash.UpdatePosition(MuzzleFlashPosition);
		MuzzleFlash.UpdateRotation(MuzzleFlashRotation);
	}

}

bool CinematicLightingManager::AreaLightPresent() {

	if (AreaLightPosition.z == 0)
		return false;
	else
		return true;
}

bool CinematicLightingManager::MuzzleFlashPresent() {

	if (MuzzleFlashPosition.z == 0)
		return false;
	else
		return true;
}

bool CinematicLightingManager::FaceLightPresent() {

	if (FaceLightPosition.z == 0)
		return false;
	else
		return true;
}

bool CinematicLightingManager::SpotlightPresent() {

	if (SpotlightPosition.z == 0)
		return false;
	else
		return true;
}

void CinematicLightingManager::RemoveAllCinematicLights()
{
	RemoveSpotlight = true;
	RemoveAreaLight = true;
	RemoveFaceLight = true;
	RemoveMuzzleFlash = true;

}
