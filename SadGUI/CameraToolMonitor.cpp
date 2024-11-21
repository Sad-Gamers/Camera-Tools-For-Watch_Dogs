#include "CameraToolMonitor.h"
#include "DXHook.h"
#include "CameraManager.h"
#include "GridShadingManager.h"
#include "EnvironmentManager.h"
#include "EntityManager.h"
#include "RenderConfig.h"
#include "Player.h"
#include "Actor.h"
#include "Databases.h"
#include "CinematicLightingManager.h"
#include "SlideAnimations.h"
#include "CinematicLight.h"
#include "HotKeys.h"
#include "SadGUI.h"


void Monitor::MonitorChanges() {

	ProccessInput();

	if (Misc::IsInLoadingState() || Misc::IsOnline()) {
		FreeCam = false;
		TimeStop = false;
		SlowMo = false;
		CustomSpeed = false;
		FreezeRain = false;
		GridShading = false;
		HideUI = false;
		UpdateWeatherPreset = false;
		UpdateTimeOfDay = false;
		UpdatePlayerGraphicKit = false;
		UpdatePlayerAnimation = false;
		StopPlayerAnimation = false;
		KillPlayer = false;
		ShovePlayer = false;
		MaskPlayer = false;
		UnMaskPlayer = false;
		PlaceActor = false;
		RemoveActor = false;
		UpdateActorGraphicKit = false;
		UpdateActorAnimation = false;
		StopActorAnimation = false;
		ActorNoCollission = false;
		ActorDrawWeapon = false;
		ActorConcealWeapon = false;
		MaskActor = false;
		UnMaskActor = false;
		StartPlayerHighlight = false;
		RemovePlayerHighlight = false;
		UpdateRenderConfig = false;
		RevertRenderConfig = false;
		MakePlayerImmortal = false;
		NoClip = false;
		TeleportToWaypoint = false;
		TeleportToWillisTower = false;
		EnableFelony = false;
		DisableFelony = false;
		if (Actor::IsPresent())
			Actor::Remove();
		CinematicLightingManager::RemoveAllCinematicLights();
		CameraManager::CinematicTransition = false;
		SlideAnimations::DeleteAllSlideLockEvents();
		EnvironmentManager::UpdateTimeOfDay();
	}


	if (RemoveControl) {
		Misc::PushPlayerActionMap("common_emptyactionmap");
		RemoveControl = false;
		RestoreControlEvent = false;
	}

	if (RestoreControl) {
		TickCountOnUIHide = GetTickCount64();
		RestoreControl = false;
		RestoreControlEvent = true;
	}

	if (RestoreControlEvent) {
		if (GetTickCount64() >= (TickCountOnUIHide + 100uLL)) {
			Misc::PopPlayerActionMap("common_emptyactionmap");
			RestoreControlEvent = true;
		}
	}

	if (Misc::TimeStop != TimeStop) {
		if (TimeStop) {
			SlowMo = false;
			CustomSpeed = false;
			Misc::SlowMo = false;
			Misc::CustomSpeed = false;
			Misc::TimeStop = true;
			Misc::EnablePlayerAnimations(false);
		}
		else 
		{
			Misc::TimeStop = false;
			Misc::EnablePlayerAnimations(true);
		}
	}

	if (Misc::SlowMo != SlowMo) {
		if (SlowMo) {
			TimeStop = false;
			CustomSpeed = false;
			Misc::SlowMo = true;
			Misc::TimeStop = false;
			Misc::CustomSpeed = false;
			Misc::EnablePlayerAnimations(true);
		}
		else
			Misc::SlowMo = false;
	}

	if (Misc::CustomSpeed != CustomSpeed) {
		if (CustomSpeed) {
			Misc::SpeedMultiplier = 1.0f;
			TimeStop = false;
			SlowMo = false;
			Misc::CustomSpeed = true;
			Misc::TimeStop = false;
			Misc::SlowMo = false;
			Misc::EnablePlayerAnimations(true);
		}
		else
			Misc::CustomSpeed = false;
	}

	if (FreeCam != CameraManager::FreeCam) {
		if (FreeCam) {
			CinematicLightingManager::LoadCinematicLights();
			Misc::PopPlayerActionMap("cinematic");
			Misc::PopPlayerActionMap("no_controls");
			*(BYTE*)(Misc::Imagebase + Offsets::DepthOfFieldCondition) = Offsets::ForceDOF;
			Offsets::oUpdatePlayerLook = *(BYTE*)(Misc::Imagebase + Offsets::UpdatePlayerLook);
			*(BYTE*)(Misc::Imagebase + Offsets::UpdatePlayerLook) = Offsets::oUpdatePlayerLook + 5;
			CameraManager::FreeCam = true;
			CameraManager::FreeCamInit = false;
		}
		else {
			CameraManager::FreeCam = false;
			CameraManager::FreeCamInit = false;
			CameraManager::FreeCamMode = "Unbounded";
			CameraManager::CinematicTransition = false;
			*(BYTE*)(Misc::Imagebase + Offsets::UpdatePlayerLook) = Offsets::oUpdatePlayerLook;
			*(BYTE*)(Misc::Imagebase + Offsets::DepthOfFieldCondition) = Offsets::ReleaseDOF;
			CinematicLightingManager::RemoveAllCinematicLights();
		}
	}

	if (HideUI != Misc::HideUI) {
		if (HideUI) {
			Misc::HideUI = true;
			Misc::SendShowOrHideAllUIEvent(false);
		}
		else 
		{
			Misc::HideUI = false;
			Misc::SendShowOrHideAllUIEvent(true);
		}
	}


	if (FreezeRain != EnvironmentManager::FreezeRain) {
		if (FreezeRain)
			EnvironmentManager::FreezeRain = true;
		else
			EnvironmentManager::FreezeRain = false;
	}

	if (GridShading != GridShadingManager::GridShading) {
		if (GridShading) {
			GridShadingManager::GridShading = true;
			GridShadingManager::EnableGridShading(true);
		}
		else {
			GridShadingManager::GridShading = false;
			GridShadingManager::EnableGridShading(false);
		}		
	}

	if (TeleportToWaypoint) {
		if (NoClip)
			NoClip = false;
			Player::TeleportToWaypoint();
		TeleportToWaypoint = false;
	}

	if (TeleportToWillisTower) {
		if (NoClip)
			NoClip = false;
		Player::TeleportToWillisTower();
		TeleportToWillisTower = false;
	}


	if (NoClip != Player::NoClipMode) {
		if (NoClip) {
			Player::BeginNoClip();
		}
		else {
			Player::EndNoClip();
		}
	}

	if (Player::NoClipMode) {
		Player::UpdateNoClip();
	}

	if (MakePlayerImmortal != Player::IsImmortal) {
		if (MakePlayerImmortal) {
			Player::MakeImmortal();
			Player::IsImmortal = true;
		}
		else {
			Player::RemoveImmortality();
			Player::IsImmortal = false;
		}
	}

	if (EnableFelony) {
		Misc::EnableFelonySystemMacro(true);
		EnableFelony = false;
	}
		

	if (DisableFelony) {
		Misc::EnableFelonySystemMacro(false);
		DisableFelony = false;
	}
		

	if (UpdateWeatherPreset) {
		EnvironmentManager::SetWeatherPreset();
		UpdateWeatherPreset = false;
	}

	if (UpdateTimeOfDay) {
		EnvironmentManager::SetTimeOfDay();
		UpdateTimeOfDay = false;
	}

	if (UpdatePlayerGraphicKit) {
		Player::UpdateGraphicKitModel();
		UpdatePlayerGraphicKit = false;
	}


	if (UpdatePlayerAnimation) {
		Player::UpdateAnimation();
		UpdatePlayerAnimation = false;
	}

	if (StopPlayerAnimation) {
		Player::StopAnimation();
		StopPlayerAnimation = false;
	}

	if (StartPlayerHighlight) {
		Player::StartHighlight();
		StartPlayerHighlight = false;
	}

	if (RemovePlayerHighlight) {
		Player::RemoveHighlight();
		RemovePlayerHighlight = false;
	}

	if (KillPlayer) {
		Player::Kill();
		KillPlayer = false;
	}

	if (ShovePlayer) {
		Player::Shove();
		ShovePlayer = false;
	}

	if (MaskPlayer) {
		Player::WearMask();
		MaskPlayer = false;
	}

	if (UnMaskPlayer) {
		Player::UnMask();
		UnMaskPlayer = false;
	}

	if (PlaceActor) {
		Actor::Place();
		PlaceActor = false;
	}

	if (RemoveActor) {
		Actor::Remove();
		RemoveActor = false;
	}

	if (StaticAngle != CameraManager::StaticAngles) {
		if (StaticAngle)
			CameraManager::StaticAngles = true;
		else
			CameraManager::StaticAngles = false;
	}

	if (UpdateActorGraphicKit) {
		Actor::UpdateGraphicKitModel();
		UpdateActorGraphicKit = false;
	}

	if (UpdateActorAnimation) {
		Actor::UpdateAnimation();
		UpdateActorAnimation = false;
	}

	if (StopActorAnimation) {
		Actor::StopAnimation();
		StopActorAnimation = false;
	}


	if (ActorDrawWeapon) {
		Actor::Draw();
		ActorDrawWeapon = false;
	}

	if (ActorConcealWeapon) {
		Actor::Holster();
		ActorConcealWeapon = false;
	}

	if (MaskActor) {
		Actor::WearMask();
		MaskActor = false;
	}

	if (UnMaskActor) {
		Actor::UnMask();
		UnMaskActor = false;
	}


	if (RemoveFaceLight) {
		CinematicLightingManager::RemoveFaceLight = true;
		RemoveFaceLight = false;
	}

	if (PlaceFaceLight) {
		CinematicLightingManager::PlaceFaceLight();
		PlaceFaceLight = false;
	}

	if (RemoveSpotlight) {
		CinematicLightingManager::RemoveSpotlight = true;
		RemoveSpotlight = false;
	}

	if (PlaceSpotlight) {
		CinematicLightingManager::PlaceSpotlight();
		PlaceSpotlight = false;
	}

	if (RemoveAreaLight) {
		CinematicLightingManager::RemoveAreaLight = true;
		RemoveAreaLight = false;
	}

	if (PlaceAreaLight) {
		CinematicLightingManager::PlaceAreaLight();
		PlaceAreaLight = false;
	}

	if (RemoveMuzzleFlash) {
		CinematicLightingManager::RemoveMuzzleFlash = true;
		RemoveMuzzleFlash = false;
	}

	if (PlaceMuzzleFlash) {
		CinematicLightingManager::PlaceMuzzleFlash();
		PlaceMuzzleFlash = false;
	}

	CinematicLightingManager::UpdateAllCinematicLightPositions();

	if (RemoveAllLights) {
		CinematicLightingManager::RemoveAllCinematicLights();
		RemoveAllLights = false;
	}
	if (Actor::NoCollision != ActorNoCollission) {
		if (ActorNoCollission) {
			SlowMo = false;
			Actor::NoCollision = true;
			EntityManager::SetPhysicsEnabled(Actor::ID, 0);
		}
		else
		{
			Actor::NoCollision = false;
			EntityManager::SetPhysicsEnabled(Actor::ID, 1);
		}
	}

	if (Actor::IsPresent()) {
		EntityManager::ActivateInvincibility(Actor::ID);
		Actor::UpdatePosition();
		Actor::UpdateRotation();
	}

	if (ReleaseActor != Actor::Release) {
		if (ReleaseActor) {
			Actor::Release = true;
		}
		else {
			uint64_t ID = Actor::ID;
			Actor::Position = {
				EntityManager::GetEntityPosition(ID, 0),
				EntityManager::GetEntityPosition(ID, 1),
				EntityManager::GetEntityPosition(ID, 2),
			};
			Actor::Rotation = {0, 0 ,0};
			Actor::Release = false;
		}
	}


	if (!RenderConfig::Initialized) {
		RenderConfig::Initialize();
		if(RenderConfig::Initialized)
			RenderConfig::SaveOriginalConfig();
	}

	if (SuperRender) {
		RenderConfig::ApplyConfig(RenderConfig::SuperRenderConfig);
		RenderConfig::UserRenderConfig = RenderConfig::SuperRenderConfig;
		SuperRender = false;
	}

	if (UpdateRenderConfig) {
		RenderConfig::ApplyConfig(RenderConfig::UserRenderConfig);
		UpdateRenderConfig = false;
	}

	if (RevertRenderConfig) {
		RenderConfig::Revert();
		RevertRenderConfig = false;
	}
	if(!DXHook::ShowGUI)
		EnvironmentManager::UpdateTimeOfDay();

}

void Monitor::ProccessInput() {
	float DeltaTime = ImGui::GetIO().DeltaTime;
	static bool ToggleTimeStopKey = false;
	static bool ToggleSlowMotionKey = false;
	static bool ToggleUIKey = false;
	static bool ToggleFreeCamKey = false;
	static bool ToggleGridShadingKey = false;
	static bool ToggleNoClipKey = false;
	static bool TransitionKey = false;
	static bool PlayAnimKey = false;

	if (FreeCam && CameraManager::FreeCamInit && CameraManager::FreeCamMode == "Unbounded"
		&& !CameraManager::CinematicTransition) {
		float CameraSpeed = DeltaTime * CameraManager::CameraSpeed;


		CameraManager::CamRotation.z += Misc::MouseDeltaX * DeltaTime;
		CameraManager::CamRotation.x += Misc::MouseDeltaY * DeltaTime;

		if (GetAsyncKeyState(VK_UP)) {
			CameraManager::CamPosition.x += CameraSpeed * CameraManager::CamDirectionVectorY.x;
			CameraManager::CamPosition.y += CameraSpeed * CameraManager::CamDirectionVectorY.y;
			CameraManager::CamPosition.z += CameraSpeed * CameraManager::CamDirectionVectorY.z;
		}

		if (GetAsyncKeyState(VK_DOWN)) {
			CameraManager::CamPosition.x -= CameraSpeed * CameraManager::CamDirectionVectorY.x;
			CameraManager::CamPosition.y -= CameraSpeed * CameraManager::CamDirectionVectorY.y;
			CameraManager::CamPosition.z -= CameraSpeed * CameraManager::CamDirectionVectorY.z;
		}

		if (GetAsyncKeyState(VK_RIGHT)) {
			CameraManager::CamPosition.x += CameraSpeed * CameraManager::CamDirectionVectorX.x;
			CameraManager::CamPosition.y += CameraSpeed * CameraManager::CamDirectionVectorX.y;
		}

		if (GetAsyncKeyState(VK_LEFT)) {
			CameraManager::CamPosition.x -= CameraSpeed * CameraManager::CamDirectionVectorX.x;
			CameraManager::CamPosition.y -= CameraSpeed * CameraManager::CamDirectionVectorX.y;
		}

		if (GetAsyncKeyState(VK_PRIOR))
			CameraManager::CamPosition.z += CameraSpeed;

		if (GetAsyncKeyState(VK_NEXT))
			CameraManager::CamPosition.z -= CameraSpeed;



	}
	if (FreeCam) {
		if (GetAsyncKeyState(VK_NUMPAD9) && CameraManager::FieldOfView <= 160)
			CameraManager::FieldOfView += DeltaTime * 2.0f;

		if (GetAsyncKeyState(VK_NUMPAD6))
			CameraManager::FieldOfView = CameraManager::FieldOfViewOnActivation;

		if (GetAsyncKeyState(VK_NUMPAD3) && CameraManager::FieldOfView >= 0)
			CameraManager::FieldOfView -= DeltaTime * 2.0f;

		if (GetAsyncKeyState(VK_NUMPAD7) && CameraManager::Roll < 180)
			CameraManager::Roll += DeltaTime * 2.0f;

		if (GetAsyncKeyState(VK_NUMPAD4))
			CameraManager::Roll = 0;

		if (GetAsyncKeyState(VK_NUMPAD1) && CameraManager::Roll > -180)
			CameraManager::Roll -= DeltaTime * 2.0f;
	}


	if (GetAsyncKeyState(VK_MULTIPLY))
		EnvironmentManager::IncreaseTimeOfDay(DeltaTime);

	if (GetAsyncKeyState(VK_SUBTRACT))
		EnvironmentManager::DecreaseTimeOfDay(DeltaTime);


	if (GetAsyncKeyState(HotKeys::HUD) < 0 && !ToggleUIKey)
		HideUI = !HideUI;
	if (GetAsyncKeyState(HotKeys::NoClip) < 0 && !ToggleNoClipKey)
		NoClip = !NoClip;
	if (GetAsyncKeyState(HotKeys::SlowMo) < 0 && !ToggleSlowMotionKey)
		SlowMo = !SlowMo;
	if (GetAsyncKeyState(HotKeys::TimeStop) < 0 && !ToggleTimeStopKey)
		TimeStop = !TimeStop;
	if (GetAsyncKeyState(HotKeys::FreeCam) < 0 && !ToggleFreeCamKey)
		FreeCam = !FreeCam;
	if (GetAsyncKeyState(HotKeys::GridShading) < 0 && !ToggleGridShadingKey)
		GridShading = !GridShading;
	if (GetAsyncKeyState(HotKeys::PlayAnim) < 0 && !PlayAnimKey)
		UpdatePlayerAnimation = true;
	
	if (GetAsyncKeyState(HotKeys::Transition) < 0 && !TransitionKey) {
		if(CameraManager::CinematicTransition)
			CameraManager::CinematicTransition = false;
		else {
			UserConfig::LoadCameraData(0);
			UserConfig::LoadCameraData(1);
			UserConfig::CameraData PointOneData = UserConfig::CameraData1;
			UserConfig::CameraData PointTwoData = UserConfig::CameraData2;
			if (SadGUI::PointOne == "A")
				PointOneData = UserConfig::CameraData1;
			if (SadGUI::PointOne == "B")
				PointOneData = UserConfig::CameraData2;
			if (SadGUI::PointTwo == "A")
				PointTwoData = UserConfig::CameraData1;
			if (SadGUI::PointTwo == "B")
				PointTwoData = UserConfig::CameraData2;
			CameraManager::StartCinematicTransition({ PointOneData, PointTwoData });
		}
	}

	TransitionKey = GetKeyState(HotKeys::Transition) < 0;
	PlayAnimKey = GetKeyState(HotKeys::PlayAnim) < 0;
	ToggleUIKey = GetKeyState(HotKeys::HUD) < 0;
	ToggleSlowMotionKey = GetKeyState(HotKeys::SlowMo) < 0;
	ToggleTimeStopKey = GetKeyState(HotKeys::TimeStop) < 0;
	ToggleFreeCamKey = GetKeyState(HotKeys::FreeCam) < 0;
	ToggleGridShadingKey = GetKeyState(HotKeys::GridShading) < 0;
	ToggleNoClipKey = GetKeyState(HotKeys::NoClip) < 0;
}