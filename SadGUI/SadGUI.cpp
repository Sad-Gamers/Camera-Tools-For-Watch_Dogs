#include "SadGUI.h"
#include "CameraToolMonitor.h"
#include "GlobalHeaders.h"
#include "CameraManager.h"
#include "EnvironmentManager.h"
#include "RenderConfig.h"
#include "Databases.h"
#include "Player.h"
#include "HotKeys.h"
#include "UserConfig.h"
#include "Actor.h"
#include "CinematicLightingManager.h"
#include "CinematicLight.h"


void SadGUI::LoadImguiTheme() {
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4(0.01f, 0.01f, 0.01f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.92f);
	colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.29f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.18f, 0.53f, 0.24f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.13f, 0.13f, 0.13f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.13f, 0.13f, 0.13f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.13f, 0.13f, 0.13f, 0.54f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.13f, 0.13f, 0.13f, 0.54f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.13f, 0.13f, 0.13f, 0.54f);
	colors[ImGuiCol_Button] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.22f, 0.82f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.00f, 0.17f, 0.40f, 0.36f);
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
	colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.00f, 0.10f, 0.24f, 0.36f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding = ImVec2(ImGui::GetFontSize() * 0.4705882f, ImGui::GetFontSize() * 0.4705882f);
	style.FramePadding = ImVec2(ImGui::GetFontSize() * 0.29412f, ImGui::GetFontSize() * 0.11765f);
	style.CellPadding = ImVec2(ImGui::GetFontSize() * 0.35294f, ImGui::GetFontSize() * 0.35294f);
	style.ItemSpacing = ImVec2(ImGui::GetFontSize() * 0.35294f, ImGui::GetFontSize() * 0.35294f);
	style.ItemInnerSpacing = ImVec2(ImGui::GetFontSize() * 0.35294f, ImGui::GetFontSize() * 0.35294f);
	style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
	style.IndentSpacing = ImGui::GetFontSize() * 1.47059f;
	style.ScrollbarSize = ImGui::GetFontSize() * 0.88235f;
	style.GrabMinSize = ImGui::GetFontSize() * 0.588235f;
	style.WindowBorderSize = ImGui::GetFontSize() * 0.05882f;
	style.ChildBorderSize = ImGui::GetFontSize() * 0.05882f;;
	style.PopupBorderSize = ImGui::GetFontSize() * 0.05882f;;
	style.FrameBorderSize = ImGui::GetFontSize() * 0.05882f;;
	style.TabBorderSize = ImGui::GetFontSize() * 0.05882f;;

	style.WindowRounding = ImGui::GetFontSize() * 0.117647f;
	style.ChildRounding = ImGui::GetFontSize() * 0.117647f;
	style.FrameRounding = ImGui::GetFontSize() * 0.117647f;
	style.PopupRounding = ImGui::GetFontSize() * 0.117647f;
	style.ScrollbarRounding = ImGui::GetFontSize() * 0.117647f;
	style.GrabRounding = ImGui::GetFontSize() * 0.117647f;
	style.LogSliderDeadzone = ImGui::GetFontSize() * 0.117647f;
	style.TabRounding = ImGui::GetFontSize() * 0.117647f;
}


void SadGUI::ShowCameraTool() {
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ImGui::GetFontSize() * 38.23529f, ImGui::GetFontSize() * 35.2941f));
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetFontSize() * 38.23529f, ImGui::GetFontSize() * 35.2941f));
	ImGui::PushItemFlag(ImGuiWindowFlags_NoResize, true);
	ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);
	ImGui::Begin("CameraToolController", &WindowOpen, ImGuiWindowFlags_NoTitleBar);
	if (ImGui::BeginTabBar("##Newtabs", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Camera"))
		{
			ImGui::BeginChild("#FreeCam", ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() * 0.85f),
				ImGuiChildFlags_None);
			ImGui::Checkbox("FreeCam", &Monitor::FreeCam);
			ImGui::Checkbox("Hide UI", &Monitor::HideUI);
			if (!CameraManager::FreeCam)
				ImGui::BeginDisabled();
			ImGui::SeparatorText("FreeCam Settings");
			ImGui::Text("Mode");
			ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
			if (ImGui::BeginCombo("##FreeCamMode", CameraManager::FreeCamMode))
			{
				for (int i = 0; i < Databases::FreeCamModes.size(); i++) {
					bool SelectedCameraMode = (CameraManager::FreeCamMode == Databases::FreeCamModes[i]);
					if (ImGui::Selectable(Databases::FreeCamModes[i], SelectedCameraMode)) {
						CameraManager::FreeCamMode = Databases::FreeCamModes[i];
						if (CameraManager::FreeCamMode != "Unbounded") {
							CameraManager::FreeCamInit = false;
							CameraManager::InitializeLookAtCam();
						}
						else {
							Offsets::oUpdatePlayerLook = *(BYTE*)(Misc::Imagebase + Offsets::UpdatePlayerLook);
							*(BYTE*)(Misc::Imagebase + Offsets::UpdatePlayerLook) = Offsets::oUpdatePlayerLook + 5;
						}
					}
					if (SelectedCameraMode) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			if (CameraManager::FreeCamMode != "Unbounded") {
				ImGui::Text("Static Angles");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
				ImGui::Checkbox("##StaticAngles", &Monitor::StaticAngle);
				ImGui::Text("Ideal Position Offset");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
				ImGui::DragFloat3("##CamIdealPos", &CameraManager::CameraIdeal.x, 0.01f, -200, 200, "%.2f");
				ImGui::Text("Ideal Angle Offset");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
				ImGui::DragFloat3("##CamIdealRot", &CameraManager::CameraIdealAngles.x, 0.25f, -180, 180, "%.2f Degrees");
			}
			ImGui::Text("Field Of View");
			ImGui::SameLine(ImGui::GetFontSize() * 8.8235f); ImGui::SliderScalar("##Field Of View", ImGuiDataType_Float, &CameraManager::FieldOfView, &MinFOV, &MaxFOV, "%.2f Degrees");
			if (CameraManager::FreeCamMode == "Unbounded") {
				ImGui::Text("Camera Roll");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f); ImGui::SliderScalar("##Camera Roll", ImGuiDataType_Float, &CameraManager::Roll, &MinRoll, &MaxRoll, "%.2f Degrees");
				ImGui::Text("Camera Speed");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f); ImGui::SliderScalar("##Camera Speed", ImGuiDataType_Float, &CameraManager::CameraSpeed, &MinCameraSpeed, &MaxCameraSpeed, "%.2f");
			}
			ImGui::SeparatorText("Depth Of Field");
			ImGui::Text("Mode");
			ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
			if (ImGui::BeginCombo("##DOFMode", CameraManager::DOFMode))
			{
				for (int i = 0; i < Databases::DepthOfFieldModes.size(); i++) {
					bool SelectedDepthOfFieldMode = (CameraManager::DOFMode == Databases::DepthOfFieldModes[i]);
					if (ImGui::Selectable(Databases::DepthOfFieldModes[i], SelectedDepthOfFieldMode)) {
						CameraManager::DOFMode = Databases::DepthOfFieldModes[i];
						if (CameraManager::DOFMode == "Disabled") {
							CameraManager::NearDOF = false;
							CameraManager::FarDOF = false;
						}
						else if (CameraManager::DOFMode == "Blur Far") {
							CameraManager::NearDOF = false;
							CameraManager::FarDOF = true;
						}
						else if (CameraManager::DOFMode == "Blur Near") {
							CameraManager::NearDOF = true;
							CameraManager::FarDOF = false;
						}
						else {
							CameraManager::NearDOF = true;
							CameraManager::FarDOF = true;
						}
					}
					if (SelectedDepthOfFieldMode) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::Text("Focus Distance");
			ImGui::SameLine(ImGui::GetFontSize() * 8.8235f); ImGui::SliderScalar("##Focus Distance", ImGuiDataType_Float, &CameraManager::FocusDistance, &MinFocusDistance, &MaxFocusDistance, "%.2f mm");
			ImGui::Text("Focal Length");
			ImGui::SameLine(ImGui::GetFontSize() * 8.8235f); ImGui::SliderScalar("##Focal Length", ImGuiDataType_Float, &CameraManager::FocalLength, &MinFocalLength, &MaxFocalLength, "%.2f mm");
			ImGui::Text("F-Stop");
			ImGui::SameLine(ImGui::GetFontSize() * 8.8235f); ImGui::SliderScalar("##F-Stop", ImGuiDataType_Float, &CameraManager::FStop, &MinFStop, &MaxFStop, "%.2f f");
			if (!CameraManager::FreeCam)
				ImGui::EndDisabled();
			if (CameraManager::FreeCam) {
				ImGui::SeparatorText("Controls");
				ImGui::Text("Toggle FreeCam");
				ImGui::SameLine(ImGui::GetFontSize() * 14.70588f);
				ImGui::TextDisabled(Databases::HotKeys[UserConfig::HotKeyFile.FreeCam]);
				ImGui::Text("Toggle UI");
				ImGui::SameLine(ImGui::GetFontSize() * 14.70588f);
				ImGui::TextDisabled(Databases::HotKeys[UserConfig::HotKeyFile.HUD]);
				ImGui::Text("Move");
				ImGui::SameLine(ImGui::GetFontSize() * 14.70588f);
				ImGui::TextDisabled("Arrow Keys");
				ImGui::Text("Move Up / Down");
				ImGui::SameLine(ImGui::GetFontSize() * 14.70588f);
				ImGui::TextDisabled("Page Up / Down");
				ImGui::Text("Increase / Reset / Decrease FOV");
				ImGui::SameLine(ImGui::GetFontSize() * 14.70588f);
				ImGui::TextDisabled("Numpad 9 / 6 / 3");
				ImGui::Text("Increase / Reset / Decrease Roll");
				ImGui::SameLine(ImGui::GetFontSize() * 14.70588f);
				ImGui::TextDisabled("Numpad 7 / 4 / 1");
			}
			ImGui::EndChild();
			ImGui::EndTabItem();
		}
		if (CameraManager::FreeCam && CameraManager::FreeCamMode == "Unbounded") {
			if (ImGui::BeginTabItem("Transitions"))
			{
				ImGui::BeginChild("#TransitionEditor", ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() * 0.85f),
					ImGuiChildFlags_None);
				ImGui::SeparatorText("Camera Points");
				ImGui::Text("Point A");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
				if (ImGui::Button("Save##SavePointOne"))
				{
					UserConfig::SaveCameraData(0, CameraManager::CamPosition,
						CameraManager::CamRotation, CameraManager::FieldOfView,
						CameraManager::FocusDistance,
						CameraManager::FocalLength,
						CameraManager::FStop,
						CameraManager::NearDOF,
						CameraManager::FarDOF);
				}
				ImGui::SameLine();
				if (ImGui::Button("Load##LoadPointOne"))
				{
					UserConfig::LoadCameraData(0);
					CameraManager::LoadCameraData(0);
				}
				ImGui::Text("Point B");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
				if (ImGui::Button("Save##SavePointTwo"))
				{
					UserConfig::SaveCameraData(1, CameraManager::CamPosition,
						CameraManager::CamRotation, CameraManager::FieldOfView,
						CameraManager::FocusDistance,
						CameraManager::FocalLength,
						CameraManager::FStop,
						CameraManager::NearDOF,
						CameraManager::FarDOF);
				}
				ImGui::SameLine();
				if (ImGui::Button("Load##LoadPointTwo"))
				{
					UserConfig::LoadCameraData(1);
					CameraManager::LoadCameraData(1);
				}
				ImGui::SeparatorText("Curve");
				ImGui::Text("Slope");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
				ImGui::SliderScalar("##TranSlope", ImGuiDataType_Float, &CameraManager::TranSlope, &MinSlope, &MaxSlope, "%.2f");
				ImGui::Text("Type");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
				ImGui::PushItemWidth(ImGui::GetFontSize() * 5.88235f);
				if (ImGui::BeginCombo("##CurveType", CameraManager::TransitionCurve))
				{
					for (int i = 0; i < Databases::TransitionCurves.size(); i++) {
						bool SelectedHUDHkey = (CameraManager::TransitionCurve == Databases::TransitionCurves[i]);
						if (ImGui::Selectable(Databases::TransitionCurves[i], SelectedHUDHkey)) {
							CameraManager::TransitionCurve = Databases::TransitionCurves[i];
						}
						if (SelectedHUDHkey) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
				ImGui::SeparatorText("Transition");
				ImGui::Text("From");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
				ImGui::PushItemWidth(ImGui::GetFontSize() * 5.88235f);
				if (ImGui::BeginCombo("##TranA", PointOne))
				{
					for (int i = 0; i < Databases::CameraPoints.size(); i++) {
						bool SelectedHUDHkey = (PointOne == Databases::CameraPoints[i]);
						if (ImGui::Selectable(Databases::CameraPoints[i], SelectedHUDHkey)) {
							PointOne = Databases::CameraPoints[i];
						}
						if (SelectedHUDHkey) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
				ImGui::Text("To");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
				ImGui::PushItemWidth(ImGui::GetFontSize() * 5.88235f);
				if (ImGui::BeginCombo("##TranB", PointTwo))
				{
					for (int i = 0; i < Databases::CameraPoints.size(); i++) {
						bool SelectedHUDHkey = (PointTwo == Databases::CameraPoints[i]);
						if (ImGui::Selectable(Databases::CameraPoints[i], SelectedHUDHkey)) {
							PointTwo = Databases::CameraPoints[i];
						}
						if (SelectedHUDHkey) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
				ImGui::PopItemWidth();
				if (ImGui::Button("Begin Transition##StartTran"))
				{
					UserConfig::LoadCameraData(0);
					UserConfig::LoadCameraData(1);
					UserConfig::CameraData PointOneData = UserConfig::CameraData1;
					UserConfig::CameraData PointTwoData = UserConfig::CameraData2;
					if (PointOne == "A")
						PointOneData = UserConfig::CameraData1;
					if (PointOne == "B")
						PointOneData = UserConfig::CameraData2;
					if (PointTwo == "A")
						PointTwoData = UserConfig::CameraData1;
					if (PointTwo == "B")
						PointTwoData = UserConfig::CameraData2;
					CameraManager::StartCinematicTransition({ PointOneData, PointTwoData });
				}
				if (ImGui::Button("Stop Transition##StopTran"))
				{
					CameraManager::CinematicTransition = false;
				}
				ImGui::SeparatorText("Controls");
				ImGui::Text("Toggle Transition");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
				ImGui::TextDisabled(Databases::HotKeys[UserConfig::HotKeyFile.Transition]);
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Lights"))
			{
				ImGui::BeginChild("#SpotlightEditor", ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() * 0.87f),
					ImGuiChildFlags_None);

				ImGui::SeparatorText("Face Light");
				if (ImGui::BeginCombo("##FaceLightType", CinematicLightingManager::FaceLightType))
				{
					for (int i = 0; i < Databases::CinematicLightTypes.size(); i++) {
						bool SelectedFaceLightType = (CinematicLightingManager::FaceLightType == Databases::CinematicLightTypes[i]);
						if (ImGui::Selectable(Databases::CinematicLightTypes[i], SelectedFaceLightType)) {
							CinematicLightingManager::FaceLightType = Databases::CinematicLightTypes[i];
							if (CinematicLightingManager::FaceLightPresent()) {
								CinematicLightingManager::MaintainFaceLightPosition = true;
								Monitor::PlaceFaceLight = true;
							}
						}
						if (SelectedFaceLightType) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
				ImGui::Text("Position");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
				ImGui::DragFloat3("##FaceLightPos", &CinematicLightingManager::FaceLightPosition.x, 0.01f, -2500.0f, 2500.0f, "%.2f");
				if (ImGui::Button("Place##PlaceFaceLight"))
				{
					Monitor::PlaceFaceLight = true;
				}
				ImGui::SameLine();
				if (ImGui::Button("Remove##RemoveFaceLight"))
				{
					Monitor::RemoveFaceLight = true;
				}

				ImGui::SeparatorText("Area Light");
				if (ImGui::BeginCombo("##AreaLightType", CinematicLightingManager::AreaLightType))
				{
					for (int i = 0; i < Databases::CinematicLightTypes.size(); i++) {
						bool SelectedAreaLightType = (CinematicLightingManager::AreaLightType == Databases::CinematicLightTypes[i]);
						if (ImGui::Selectable(Databases::CinematicLightTypes[i], SelectedAreaLightType)) {
							CinematicLightingManager::AreaLightType = Databases::CinematicLightTypes[i];
							if (CinematicLightingManager::AreaLightPresent()) {
								CinematicLightingManager::MaintainAreaLightPosition = true;
								Monitor::PlaceAreaLight = true;
							}
						}
						if (SelectedAreaLightType) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
				ImGui::Text("Position");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
				ImGui::DragFloat3("##AreaLightPos", &CinematicLightingManager::AreaLightPosition.x, 0.01f, -2500.0f, 2500.0f, "%.2f");
				if (ImGui::Button("Place##PlaceAreaLight"))
				{
					Monitor::PlaceAreaLight = true;
				}
				ImGui::SameLine();
				if (ImGui::Button("Remove##RemoveAreaLight"))
				{
					Monitor::RemoveAreaLight = true;
				}

				ImGui::SeparatorText("Spotlight");
				if (ImGui::BeginCombo("##SpotlightType", CinematicLightingManager::SpotlightType))
				{
					for (int i = 0; i < Databases::CinematicLightTypes.size(); i++) {
						bool SelectedSpotlightType = (CinematicLightingManager::SpotlightType == Databases::CinematicLightTypes[i]);
						if (ImGui::Selectable(Databases::CinematicLightTypes[i], SelectedSpotlightType)) {
							CinematicLightingManager::SpotlightType = Databases::CinematicLightTypes[i];
							if (CinematicLightingManager::SpotlightPresent()) {
								CinematicLightingManager::MaintainSpotlightPosition = true;
								Monitor::PlaceSpotlight = true;
							}
						}
						if (SelectedSpotlightType) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
				ImGui::Text("Position");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
				ImGui::DragFloat3("##SpotlightPos", &CinematicLightingManager::SpotlightPosition.x, 0.01f, -2500.0f, 2500.0f, "%.2f");
				ImGui::Text("Rotation");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
				ImGui::DragFloat3("##SpotlightRot", &CinematicLightingManager::SpotlightRotation.x, 0.5f, -2500.0f, 2500.0f, "%.2f Degrees");
				if (ImGui::Button("Place##PlaceSpotlight"))
				{
					Monitor::PlaceSpotlight = true;
				}
				ImGui::SameLine();
				if (ImGui::Button("Remove##RemoveSpotlight"))
				{
					Monitor::RemoveSpotlight = true;
				}

				ImGui::SeparatorText("Muzzle Flash");
				ImGui::Text("Position");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
				ImGui::DragFloat3("##MuzzleFlashPos", &CinematicLightingManager::MuzzleFlashPosition.x, 0.01f, -2500.0f, 2500.0f, "%.2f");
				ImGui::Text("Rotation");
				if (ImGui::Button("Place##PlaceMuzzleFlash"))
				{
					Monitor::PlaceMuzzleFlash = true;
				}
				ImGui::SameLine();
				if (ImGui::Button("Remove##RemoveMuzzleFlash"))
				{
					Monitor::RemoveMuzzleFlash = true;
				}

				ImGui::EndChild();
				if (ImGui::Button("Remove All Lights"))
				{
					Monitor::RemoveAllLights = true;
				}

				ImGui::EndTabItem();
			}
		}
		if (ImGui::BeginTabItem("World"))
		{
			ImGui::BeginChild("#WorldEditor", ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() * 0.85f),
				ImGuiChildFlags_None);
			ImGui::SeparatorText("Weather Preset");
			if (ImGui::BeginCombo("##EnvPreset", EnvironmentManager::CurrentWeatherPreset))
			{
				for (int i = 0; i < Databases::EnvironmentPresets.size(); i++) {
					bool SelectedWeatherPreset = (EnvironmentManager::CurrentWeatherPreset == Databases::EnvironmentPresets[i]);
					if (ImGui::Selectable(Databases::EnvironmentPresets[i], SelectedWeatherPreset)) {
						EnvironmentManager::CurrentWeatherPreset = Databases::EnvironmentPresets[i];
						Monitor::UpdateWeatherPreset = true;
					}
					if (SelectedWeatherPreset) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::SeparatorText("Time Of Day");
			ImGui::PushItemWidth(ImGui::GetFontSize() * 2.9411f);
			ImGui::InputInt("##TODHour", &EnvironmentManager::MilitaryTimeHour , 0, 12); 
			ImGui::SameLine();
			ImGui::InputInt("##TODMinute", &EnvironmentManager::MilitaryTimeMinute, 0, 60);
			ImGui::PopItemWidth();
			if (ImGui::Button("Apply##ApplyTOD"))
			{
				Monitor::UpdateTimeOfDay = true;
			}
			ImGui::SeparatorText("Game Speed");
			ImGui::Checkbox("Use Custom Speed", &Monitor::CustomSpeed);
			if (Misc::CustomSpeed) {
				ImGui::Text("Speed Multiplier");
				ImGui::SameLine(ImGui::GetFontSize() * 8.8235f); ImGui::SliderScalar("##SpeedMult", ImGuiDataType_Float, &Misc::SpeedMultiplier, &MinSpeed, &MaxSpeed, "%.2f");
			}
			else {
				ImGui::Checkbox("Slow Motion", &Monitor::SlowMo);
				ImGui::Checkbox("Stop Time", &Monitor::TimeStop);
			}
			ImGui::SeparatorText("Misc");
			ImGui::Checkbox("Grid Shading", &Monitor::GridShading);
			ImGui::Checkbox("Freeze Rain Drops", &Monitor::FreezeRain);
			ImGui::SeparatorText("Controls");
			ImGui::Text("Increase / Decrease Time Of Day");
			ImGui::SameLine(ImGui::GetFontSize() * 14.70588f);
			ImGui::TextDisabled("Numpad * / -");
			ImGui::Text("Toggle Stop Time");
			ImGui::SameLine(ImGui::GetFontSize() * 14.70588f);
			ImGui::TextDisabled(Databases::HotKeys[UserConfig::HotKeyFile.TimeStop]);
			ImGui::Text("Toggle Slow Motion");
			ImGui::SameLine(ImGui::GetFontSize() * 14.70588f);
			ImGui::TextDisabled(Databases::HotKeys[UserConfig::HotKeyFile.SlowMo]);
			ImGui::Text("Toggle GridShading");
			ImGui::SameLine(ImGui::GetFontSize() * 14.70588f);
			ImGui::TextDisabled(Databases::HotKeys[UserConfig::HotKeyFile.GridShading]);
			ImGui::EndChild();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Player"))
		{
			ImGui::BeginChild("#PlayerEditor", ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() * 0.85f),
				ImGuiChildFlags_None);
			ImGui::SeparatorText("GraphicKit / Model");
			ImGui::PushItemWidth(ImGui::GetFontSize() * 8.8235f);
			if (ImGui::BeginCombo("##GraphicKitListLocalPlayer", GraphicKitSelectionMode))
			{
				for (int i = 0; i < Databases::SelectionModes.size(); i++) {
					bool SelectedSelectionMode = (GraphicKitSelectionMode == Databases::SelectionModes[i]);
					if (ImGui::Selectable(Databases::SelectionModes[i], SelectedSelectionMode)) {
						GraphicKitSelectionMode = Databases::SelectionModes[i];
						if (GraphicKitSelectionMode == "Bookmarks") {
							UserConfig::LoadGraphicKitBookmarks();
							if (Databases::BookmarkedGraphicKitModels.size() != 0)
								Player::GraphicKitModel = Databases::BookmarkedGraphicKitModels[0].c_str();
						}
						else {
							Player::GraphicKitModel = Databases::GraphicKitModels[0];
						}
					}
					if (SelectedSelectionMode) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			if (GraphicKitSelectionMode == "Bookmarks") {
				ImGui::PushID(4001);
				static ImGuiTextFilter GraphicKitFilterLocalPlayer;
				GraphicKitFilterLocalPlayer.Draw();
				ImGui::PopID();
				if (ImGui::BeginCombo("##GraphicKitLocalPlayer", Player::GraphicKitModel))
				{
					for (int i = 0; i < Databases::BookmarkedGraphicKitModels.size(); i++)
						if (GraphicKitFilterLocalPlayer.PassFilter(Databases::BookmarkedGraphicKitModels[i].c_str())) {
							bool SelectedPlayerGraphicKit = (Player::GraphicKitModel == Databases::BookmarkedGraphicKitModels[i]);
							if (ImGui::Selectable(Databases::BookmarkedGraphicKitModels[i].c_str(), SelectedPlayerGraphicKit)) {
								Player::GraphicKitModel = Databases::BookmarkedGraphicKitModels[i].c_str();
								Monitor::UpdatePlayerGraphicKit = true;
							}
							if (SelectedPlayerGraphicKit) {
								ImGui::SetItemDefaultFocus();
							}
						}
					ImGui::EndCombo();
				}
				ImGui::SameLine();
				if (ImGui::Button("Remove Bookmark##RemoveBookMarkBookmarkLocalPlayerModel"))
				{
					UserConfig::RemoveGraphicKitBookmark(Player::GraphicKitModel);
					if (Databases::BookmarkedGraphicKitModels.size() != 0)
						Player::GraphicKitModel = Databases::BookmarkedGraphicKitModels[0].c_str();
					else
						Player::GraphicKitModel = Databases::GraphicKitModels[0];
				}
			}
			else {
				ImGui::PushID(4001);
				static ImGuiTextFilter GraphicKitFilterLocalPlayer;
				GraphicKitFilterLocalPlayer.Draw();
				ImGui::PopID();
				if (ImGui::BeginCombo("##GraphicKitLocalPlayer", Player::GraphicKitModel))
				{
					for (int i = 0; i < Databases::GraphicKitModels.size(); i++)
						if (GraphicKitFilterLocalPlayer.PassFilter(Databases::GraphicKitModels[i])) {
							bool SelectedPlayerGraphicKit = (Player::GraphicKitModel == Databases::GraphicKitModels[i]);
							if (ImGui::Selectable(Databases::GraphicKitModels[i], SelectedPlayerGraphicKit)) {
								Player::GraphicKitModel = Databases::GraphicKitModels[i];
								Monitor::UpdatePlayerGraphicKit = true;
							}
							if (SelectedPlayerGraphicKit) {
								ImGui::SetItemDefaultFocus();
							}
						}
					ImGui::EndCombo();
				}
				ImGui::SameLine();
				if (ImGui::Button("Bookmark##BookmarkLocalPlayerModel"))
				{
					UserConfig::AddGraphicKitBookmark(Player::GraphicKitModel);
				}
			}

			ImGui::SeparatorText("Animation / Pose");
			ImGui::PushItemWidth(ImGui::GetFontSize() * 8.8235f);
			if (ImGui::BeginCombo("##AnimListLocalPlayer", AnimationSelectionMode))
			{
				for (int i = 0; i < Databases::SelectionModes.size(); i++) {
					bool SelectedSelectionMode = (AnimationSelectionMode == Databases::SelectionModes[i]);
					if (ImGui::Selectable(Databases::SelectionModes[i], SelectedSelectionMode)) {
						AnimationSelectionMode  = Databases::SelectionModes[i];
						if (AnimationSelectionMode == "Bookmarks") {
							UserConfig::LoadAnimationBookmarks();
							if (Databases::BookmarkedDecisionTrees.size() != 0)
								Player::Animation = Databases::BookmarkedDecisionTrees[0].c_str();
						}
						else {
							Player::Animation = Databases::DecisionTrees[0];
						}
					}
					if (SelectedSelectionMode) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			if (AnimationSelectionMode == "Bookmarks") {
				ImGui::PushID(4002);
				static ImGuiTextFilter AnimationFilterLocalPlayer;
				AnimationFilterLocalPlayer.Draw();
				ImGui::PopID();
				if (ImGui::BeginCombo("##AnimationLocalPlayer", Player::Animation))
				{
					for (int i = 0; i < Databases::BookmarkedDecisionTrees.size(); i++)
						if (AnimationFilterLocalPlayer.PassFilter(Databases::BookmarkedDecisionTrees[i].c_str())) {
							bool SelectedPlayerAnimation = (Player::Animation == Databases::BookmarkedDecisionTrees[i]);
							if (ImGui::Selectable(Databases::BookmarkedDecisionTrees[i].c_str(), SelectedPlayerAnimation)) {
								Player::Animation = Databases::BookmarkedDecisionTrees[i].c_str();
							}
							if (SelectedPlayerAnimation) {
								ImGui::SetItemDefaultFocus();
							}
						}
					ImGui::EndCombo();
				}
				ImGui::SameLine();
				if (ImGui::Button("Remove Bookmark##RemoveBookMarkBookmarkLocalPlayerAnim"))
				{
					UserConfig::RemoveAnimationBookmark(Player::Animation);
					if (Databases::BookmarkedDecisionTrees.size() != 0)
						Player::Animation = Databases::BookmarkedDecisionTrees[0].c_str();
					else
						Player::Animation = Databases::DecisionTrees[0];
				}
			}
			else {
				ImGui::PushID(4002);
				static ImGuiTextFilter AnimationFilterLocalPlayer;
				AnimationFilterLocalPlayer.Draw();
				ImGui::PopID();
				if (ImGui::BeginCombo("##AnimationLocalPlayer", Player::Animation))
				{
					for (int i = 0; i < Databases::DecisionTrees.size(); i++)
						if (AnimationFilterLocalPlayer.PassFilter(Databases::DecisionTrees[i])) {
							bool SelectedPlayerAnimation = (Player::Animation == Databases::DecisionTrees[i]);
							if (ImGui::Selectable(Databases::DecisionTrees[i], SelectedPlayerAnimation)) {
								Player::Animation = Databases::DecisionTrees[i];
							}
							if (SelectedPlayerAnimation) {
								ImGui::SetItemDefaultFocus();
							}
						}
					ImGui::EndCombo();
				}
				ImGui::SameLine();
				if (ImGui::Button("Bookmark##BookmarkLocalPlayerAnim"))
				{
					UserConfig::AddAnimationBookmark(Player::Animation);
				}
			}

			if (ImGui::Button("Play##PlayPlayerAnim"))
			{
				Monitor::UpdatePlayerAnimation = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Stop##StopPlayerAnim"))
			{
				Monitor::StopPlayerAnimation = true;
			}
			ImGui::Checkbox("Loop", &Player::LoopAnimation);
			ImGui::SeparatorText("Highlight");
			ImGui::PushID(3999);
			ImGui::PopID();
			if (ImGui::BeginCombo("##HighlightLocalPlayer", Player::HighlightColorStr))
			{
				for (int i = 0; i < Databases::HighlightColors.size(); i++) {
					bool SelectedHighlightColor = (Player::HighlightColorStr == Databases::HighlightColors[i]);
					if (ImGui::Selectable(Databases::HighlightColors[i], SelectedHighlightColor)) {
						Player::HighlightColorStr = Databases::HighlightColors[i];
						Player::HighlightColor = i;
						Monitor::UpdateWeatherPreset = true;
					}
					if (SelectedHighlightColor) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			if (ImGui::Button("Highlight##HighlightPlayer"))
			{
				Monitor::StartPlayerHighlight = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Remove##RemovePlayerHighlight"))
			{
				Monitor::RemovePlayerHighlight = true;
			}
			ImGui::SeparatorText("Random");
			ImGui::Text("Immortality");
			ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
			ImGui::Checkbox("##Immortality", &Monitor::MakePlayerImmortal);
			ImGui::Text("Hurt Player");
			ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
			if (ImGui::Button("InstaKill"))
			{
				Monitor::KillPlayer = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Shove"))
			{
				Monitor::ShovePlayer = true;
			}
			ImGui::Text("Vigilante Mask");
			ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
			if (ImGui::Button("Wear##PlayerWearMask"))
			{
				Monitor::MaskPlayer = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Remove##PlayerRemoveMask"))
			{
				Monitor::UnMaskPlayer = true;
			}
			ImGui::EndChild();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Actor")) {
			ImGui::BeginChild("#ActorEditor", ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() * 0.85f),
				ImGuiChildFlags_None);
			ImGui::SeparatorText("Placement");
			if (Actor::Release ||!Actor::IsPresent())
				ImGui::BeginDisabled();
			ImGui::Text("Position");
			ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
			ImGui::DragFloat3("##ActorPos", &Actor::Position.x, 0.01f, -2500.0f, 2500.0f, "%.2f");
			ImGui::Text("Rotation");
			ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
			ImGui::DragFloat3("##ActorRot", &Actor::Rotation.x, 0.5f, -180.0f, 180.0f, "%.2f Degrees");
			if (Actor::Release || !Actor::IsPresent())
				ImGui::EndDisabled();
			ImGui::Text("Release");
			ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
			ImGui::Checkbox("##ReleaseActor", &Monitor::ReleaseActor);
			ImGui::Text("No Collission");
			ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
			ImGui::Checkbox("##ActorNoCollissions", &Monitor::ActorNoCollission);
			ImGui::SeparatorText("GraphicKit / Model");
			ImGui::PushItemWidth(ImGui::GetFontSize() * 8.8235f);
			if (ImGui::BeginCombo("##GraphicKitListActor", GraphicKitSelectionMode))
			{
				for (int i = 0; i < Databases::SelectionModes.size(); i++) {
					bool SelectedSelectionMode = (GraphicKitSelectionMode == Databases::SelectionModes[i]);
					if (ImGui::Selectable(Databases::SelectionModes[i], SelectedSelectionMode)) {
						GraphicKitSelectionMode = Databases::SelectionModes[i];
						if (GraphicKitSelectionMode == "Bookmarks") {
							UserConfig::LoadGraphicKitBookmarks();
							if (Databases::BookmarkedGraphicKitModels.size() != 0)
								Actor::GraphicKitModel = Databases::BookmarkedGraphicKitModels[0].c_str();
						}
						else {
							Actor::GraphicKitModel = Databases::GraphicKitModels[0];
						}
					}
					if (SelectedSelectionMode) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			if (GraphicKitSelectionMode == "Bookmarks") {
				ImGui::PushID(4001);
				static ImGuiTextFilter GraphicKitFilterActor;
				GraphicKitFilterActor.Draw();
				ImGui::PopID();
				if (ImGui::BeginCombo("##GraphicKitActor", Actor::GraphicKitModel))
				{
					for (int i = 0; i < Databases::BookmarkedGraphicKitModels.size(); i++)
						if (GraphicKitFilterActor.PassFilter(Databases::BookmarkedGraphicKitModels[i].c_str())) {
							bool SelectedActorGraphicKit = (Actor::GraphicKitModel == Databases::BookmarkedGraphicKitModels[i]);
							if (ImGui::Selectable(Databases::BookmarkedGraphicKitModels[i].c_str(), SelectedActorGraphicKit)) {
								Actor::GraphicKitModel = Databases::BookmarkedGraphicKitModels[i].c_str();
								Monitor::UpdateActorGraphicKit = true;
							}
							if (SelectedActorGraphicKit) {
								ImGui::SetItemDefaultFocus();
							}
						}
					ImGui::EndCombo();
				}
				ImGui::SameLine();
				if (ImGui::Button("Remove Bookmark##RemoveBookMarkBookmarkActorModel"))
				{
					UserConfig::RemoveGraphicKitBookmark(Actor::GraphicKitModel);
					if (Databases::BookmarkedGraphicKitModels.size() != 0)
						Actor::GraphicKitModel = Databases::BookmarkedGraphicKitModels[0].c_str();
					else
						Actor::GraphicKitModel = Databases::GraphicKitModels[0];
				}
			}
			else {
				ImGui::PushID(4001);
				static ImGuiTextFilter GraphicKitFilterActor;
				GraphicKitFilterActor.Draw();
				ImGui::PopID();
				if (ImGui::BeginCombo("##GraphicKitActor", Actor::GraphicKitModel))
				{
					for (int i = 0; i < Databases::GraphicKitModels.size(); i++)
						if (GraphicKitFilterActor.PassFilter(Databases::GraphicKitModels[i])) {
							bool SelectedActorGraphicKit = (Actor::GraphicKitModel == Databases::GraphicKitModels[i]);
							if (ImGui::Selectable(Databases::GraphicKitModels[i], SelectedActorGraphicKit)) {
								Actor::GraphicKitModel = Databases::GraphicKitModels[i];
								Monitor::UpdateActorGraphicKit = true;
							}
							if (SelectedActorGraphicKit) {
								ImGui::SetItemDefaultFocus();
							}
						}
					ImGui::EndCombo();
				}
				ImGui::SameLine();
				if (ImGui::Button("Bookmark##BookmarkActorModel"))
				{
					UserConfig::AddGraphicKitBookmark(Actor::GraphicKitModel);
				}
			}

			ImGui::SeparatorText("Animation / Pose");
			ImGui::PushItemWidth(ImGui::GetFontSize() * 8.8235f);
			if (ImGui::BeginCombo("##AnimListActor", AnimationSelectionMode))
			{
				for (int i = 0; i < Databases::SelectionModes.size(); i++) {
					bool SelectedSelectionMode = (AnimationSelectionMode == Databases::SelectionModes[i]);
					if (ImGui::Selectable(Databases::SelectionModes[i], SelectedSelectionMode)) {
						AnimationSelectionMode = Databases::SelectionModes[i];
						if (AnimationSelectionMode == "Bookmarks") {
							UserConfig::LoadAnimationBookmarks();
							if (Databases::BookmarkedDecisionTrees.size() != 0)
								Actor::Animation = Databases::BookmarkedDecisionTrees[0].c_str();
						}
						else {
							Actor::Animation = Databases::DecisionTrees[0];
						}
					}
					if (SelectedSelectionMode) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			if (AnimationSelectionMode == "Bookmarks") {
				ImGui::PushID(4002);
				static ImGuiTextFilter AnimationFilterActor;
				AnimationFilterActor.Draw();
				ImGui::PopID();
				if (ImGui::BeginCombo("##AnimationActor", Actor::Animation))
				{
					for (int i = 0; i < Databases::BookmarkedDecisionTrees.size(); i++)
						if (AnimationFilterActor.PassFilter(Databases::BookmarkedDecisionTrees[i].c_str())) {
							bool SelectedActorAnimation = (Actor::Animation == Databases::BookmarkedDecisionTrees[i]);
							if (ImGui::Selectable(Databases::BookmarkedDecisionTrees[i].c_str(), SelectedActorAnimation)) {
								Actor::Animation = Databases::BookmarkedDecisionTrees[i].c_str();
							}
							if (SelectedActorAnimation) {
								ImGui::SetItemDefaultFocus();
							}
						}
					ImGui::EndCombo();
				}
				ImGui::SameLine();
				if (ImGui::Button("Remove Bookmark##RemoveBookMarkBookmarkActorAnim"))
				{
					UserConfig::RemoveAnimationBookmark(Actor::Animation);
					if (Databases::BookmarkedDecisionTrees.size() != 0)
						Actor::Animation = Databases::BookmarkedDecisionTrees[0].c_str();
					else
						Actor::Animation = Databases::DecisionTrees[0];
				}
			}
			else {
				ImGui::PushID(4002);
				static ImGuiTextFilter AnimationFilterActor;
				AnimationFilterActor.Draw();
				ImGui::PopID();
				if (ImGui::BeginCombo("##AnimationActor", Actor::Animation))
				{
					for (int i = 0; i < Databases::DecisionTrees.size(); i++)
						if (AnimationFilterActor.PassFilter(Databases::DecisionTrees[i])) {
							bool SelectedActorAnimation = (Actor::Animation == Databases::DecisionTrees[i]);
							if (ImGui::Selectable(Databases::DecisionTrees[i], SelectedActorAnimation)) {
								Actor::Animation = Databases::DecisionTrees[i];
							}
							if (SelectedActorAnimation) {
								ImGui::SetItemDefaultFocus();
							}
						}
					ImGui::EndCombo();
				}
				ImGui::SameLine();
				if (ImGui::Button("Bookmark##BookmarkActorAnim"))
				{
					UserConfig::AddAnimationBookmark(Actor::Animation);
				}
			}
			if (ImGui::Button("Play##PlayActorAnim"))
			{
				Monitor::UpdateActorAnimation = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Stop##StopActorAnim"))
			{
				Monitor::StopActorAnimation = true;
			}
			ImGui::Checkbox("Loop", &Actor::LoopAnimation);
			ImGui::SeparatorText("Random");
			ImGui::Text("Weapon");
			ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
			if (ImGui::Button("Draw##ActorDrawWep"))
			{
				Monitor::ActorDrawWeapon = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Conceal##ActorHolsterWep"))
			{
				Monitor::ActorConcealWeapon = true;
			}
			ImGui::Text("Vigilante Mask");
			ImGui::SameLine(ImGui::GetFontSize() * 8.8235f);
			if (ImGui::Button("Wear##ActorMask"))
			{
				Monitor::MaskActor = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Remove##ActorUnMask"))
			{
				Monitor::UnMaskActor = true;
			}
			ImGui::EndChild();
			if (ImGui::Button("Spawn##SpawnActor"))
			{
				Monitor::PlaceActor = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Remove##RemoveActor"))
			{
				Monitor::RemoveActor = true;
			}
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Rendering"))
		{
			ImGui::BeginChild("#RenderConfigEditor", ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() * 0.87f),
				ImGuiChildFlags_None);
			if (!RenderConfig::Initialized)
				ImGui::BeginDisabled();
			ImGui::SeparatorText("Profile");
			if (ImGui::Button("Save"))
			{
				UserConfig::SaveRenderConfig();
			}
			ImGui::SameLine();
			if (ImGui::Button("Load"))
			{
				UserConfig::LoadRenderConfig();
			}
			if (ImGui::Button("SuperRender"))
			{
				Monitor::SuperRender = true;
			}
			ImGui::SeparatorText("Anti-Aliasing");
			ImGui::Text("SuperSampling");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::Checkbox("##SuperSampling", &RenderConfig::UserRenderConfig.SuperSampling);
			ImGui::Text("AntiAliasingMode");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputInt("##AntiAliasingMode",
				&RenderConfig::UserRenderConfig.AntiAliasingMode, 0, 0);
			ImGui::Text("MultiSampleMode");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputInt("##MultiSampleMode",
				&RenderConfig::UserRenderConfig.MultiSampleMode, 0, 0);
			ImGui::Text("MultiSampleQualityLevel");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputInt("##MultiSampleQualityLevel",
				&RenderConfig::UserRenderConfig.MultiSampleQualityLevel, 0, 0);

			ImGui::SeparatorText("Level Of Detail");
			ImGui::Text("LodScale");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputFloat("##LodScale",
				&RenderConfig::UserRenderConfig.LodScale, 0, 0);
			ImGui::Text("RealTreesLodScale");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputFloat("##RealTreesLodScale",
				&RenderConfig::UserRenderConfig.RealTreesLodScale, 0, 0);
			ImGui::Text("ClustersLodScale");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputFloat("##ClustersLodScale",
				&RenderConfig::UserRenderConfig.ClustersLodScale, 0, 0);
			ImGui::Text("KillLodScale");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputFloat("##KillLodScale",
				&RenderConfig::UserRenderConfig.KillLodScale, 0, 0);
			ImGui::Text("BuildingKillLodScale");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputFloat("##BuildingKillLodScale",
				&RenderConfig::UserRenderConfig.BuildingKillLodScale, 0, 0);
			ImGui::Text("ClusterObjectMinSize");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputFloat("##ClusterObjectMinSize",
				&RenderConfig::UserRenderConfig.ClusterObjectMinSize, 0, 0);
			ImGui::Text("ClusterObjectMinSizeDetail");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputFloat("##ClusterObjectMinSizeDetail",
				&RenderConfig::UserRenderConfig.ClusterObjectMinSizeDetail, 0, 0);
			ImGui::Text("SceneObjectMinSize");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputFloat("##SceneObjectMinSize",
				&RenderConfig::UserRenderConfig.SceneObjectMinSize, 0, 0);

			ImGui::SeparatorText("Shadows");
			ImGui::Text("SoftShadows");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::Checkbox("##SoftShadows", &RenderConfig::UserRenderConfig.SoftShadows);
			ImGui::Text("UseCSMShadows");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::Checkbox("##EnableCSMShadows", &RenderConfig::UserRenderConfig.EnableCSMShadows);
			ImGui::Text("BilateralBlurSamples");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputInt("##ShadowBilateralBlurNumSamples",
				&RenderConfig::UserRenderConfig.ShadowBilateralBlurNumSamples, 0, 0);
			ImGui::Text("BilateralBlurPasses");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputInt("##ShadowBilateralBlurNumPasses",
				&RenderConfig::UserRenderConfig.ShadowBilateralBlurNumPasses, 0, 0);

			ImGui::Text("DynamicShadowMapSize");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputInt("##ShadowMapSize",
				&RenderConfig::UserRenderConfig.ShadowMapSize, 0, 0);
			if (RenderConfig::UserRenderConfig.EnableCSMShadows) {
				ImGui::Text("CascadedShadowMapSize");
				ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
				ImGui::InputInt("##CascadedShadowMapSize",
					&RenderConfig::UserRenderConfig.CascadedShadowMapSize, 0, 0);
				ImGui::Text("DepthBias");
				ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
				ImGui::DragFloat3("##CSMDepthBias", &RenderConfig::UserRenderConfig.CSMDepthBias.x, 0.01f, 0.0f, 10.0f, "%.4f");
				ImGui::Text("SlopeScaleDepthBias");
				ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
				ImGui::DragFloat3("##CSMSlopeScaleDepthBias", &RenderConfig::UserRenderConfig.CSMSlopeScaleDepthBias.x, 0.01f, 0.0f, 10.0f, "%.4f");
				ImGui::Text("ObjectMinSize");
				ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
				ImGui::DragFloat3("##CSMObjectMinSize", &RenderConfig::UserRenderConfig.CSMObjectMinSize.x, 0.01f, 0.0f, 10.0f, "%.4f");
				ImGui::Text("RealTreeMinSize");
				ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
				ImGui::DragFloat3("##CSMRealTreeMinSize", &RenderConfig::UserRenderConfig.CSMRealTreeMinSize.x, 0.01f, 0.0f, 10.0f, "%.4f");
			}
			if (!RenderConfig::UserRenderConfig.EnableCSMShadows) {
				ImGui::Text("Facetted ShadowMapSize");
				ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
				ImGui::InputInt("##FSMShadowMapSize",
					&RenderConfig::UserRenderConfig.FSMShadowMapSize, 0, 0);
				ImGui::Text("DepthBias");
				ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
				ImGui::InputFloat("##FSMDepthBias",
					&RenderConfig::UserRenderConfig.FSMDepthBias, 0, 0);
				ImGui::Text("ShadowFadeStart");
				ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
				ImGui::InputFloat("##FSMShadowFadeStart",
					&RenderConfig::UserRenderConfig.FSMShadowFadeStart, 0, 0);
				ImGui::Text("ShadowFadeEnd");
				ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
				ImGui::InputFloat("##FSMShadowFadeEnd",
					&RenderConfig::UserRenderConfig.FSMShadowFadeEnd, 0, 0);
				ImGui::Text("ShadowRange");
				ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
				ImGui::InputFloat("##FSMShadowRange",
					&RenderConfig::UserRenderConfig.FSMShadowRange, 0, 0);
				ImGui::Text("ShadowQuality");
				ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
				ImGui::InputFloat("##FSMShadowQuality",
					&RenderConfig::UserRenderConfig.FSMShadowQuality, 0, 0);
				ImGui::Text("ObjectMinSize");
				ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
				ImGui::InputFloat("##FSMObjectMinSize",
					&RenderConfig::UserRenderConfig.FSMObjectMinSize, 0, 0);
				ImGui::Text("RealTreeMinSize");
				ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
				ImGui::InputFloat("##FSMRealTreeMinSize",
					&RenderConfig::UserRenderConfig.FSMRealTreeMinSize, 0, 0);
			}


			ImGui::SeparatorText("Reflections");
			ImGui::Text("TextureSize");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputInt("##ParaboloidReflectionTextureSize",
				&RenderConfig::UserRenderConfig.ParaboloidReflectionTextureSize, 0, 0);

			ImGui::SeparatorText("Water");
			ImGui::Text("TextureSize");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::InputInt("##WaterReflectionTextureSize",
				&RenderConfig::UserRenderConfig.WaterReflectionTextureSize, 0, 0);
			ImGui::EndChild();
			if (ImGui::Button("Apply##ApplyRenderConfig"))
			{
				Monitor::UpdateRenderConfig = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Revert##RevertRenderConfig"))
			{
				Monitor::RevertRenderConfig = true;
			}
			ImGui::SameLine();
			if (!RenderConfig::Initialized)
				ImGui::EndDisabled();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Configure"))
		{
			ImGui::BeginChild("#UserSettings", ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() * 0.87f), 
				ImGuiChildFlags_None);
			ImGui::SeparatorText("Hotkeys");
			ImGui::Text("Overlay");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::PushItemWidth(ImGui::GetFontSize() * 5.88235f);
			if (ImGui::BeginCombo("##OverlayHkey", HotKeys::EditorGUI))
			{
				for (int i = 1; i < Databases::HotKeys.size(); i++) {
					bool SelectedOverlayHkey = (HotKeys::EditorGUI == Databases::HotKeys[i] );
					if (ImGui::Selectable(Databases::HotKeys[i], SelectedOverlayHkey)) {
						UserConfig::SanatizeHotKeySelection(i);
						HotKeys::EditorGUI = Databases::HotKeys[i];
						UserConfig::HotKeyFileToSave.GUI = i;
					}
					if (SelectedOverlayHkey) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			ImGui::Text("FreeCam");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::PushItemWidth(ImGui::GetFontSize() * 5.88235f);
			if (ImGui::BeginCombo("##FreeCamHkey", HotKeys::EditorFreeCam))
			{
				for (int i = 0; i < Databases::HotKeys.size(); i++) {
					bool SelectedFreeCamHkey = (HotKeys::EditorFreeCam == Databases::HotKeys[i]);
					if (ImGui::Selectable(Databases::HotKeys[i], SelectedFreeCamHkey)) {
						UserConfig::SanatizeHotKeySelection(i);
						HotKeys::EditorFreeCam = Databases::HotKeys[i];
						UserConfig::HotKeyFileToSave.FreeCam = i;
					}
					if (SelectedFreeCamHkey) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::Text("HUD/UI");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::PushItemWidth(ImGui::GetFontSize() * 5.88235f);
			if (ImGui::BeginCombo("##HUDHkey", HotKeys::EditorHUD))
			{
				for (int i = 0; i < Databases::HotKeys.size(); i++) {
					bool SelectedHUDHkey = (HotKeys::EditorHUD == Databases::HotKeys[i]);
					if (ImGui::Selectable(Databases::HotKeys[i], SelectedHUDHkey)) {
						UserConfig::SanatizeHotKeySelection(i);
						HotKeys::EditorHUD = Databases::HotKeys[i];
						UserConfig::HotKeyFileToSave.HUD = i;
					}
					if (SelectedHUDHkey) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			ImGui::PopItemWidth();
			ImGui::Text("TimeStop");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::PushItemWidth(ImGui::GetFontSize() * 5.88235f);
			if (ImGui::BeginCombo("##TimeStopHkey", HotKeys::EditorTimeStop))
			{
				for (int i = 0; i < Databases::HotKeys.size(); i++) {
					bool SelectedTimeStopHkey = (HotKeys::EditorTimeStop == Databases::HotKeys[i]);
					if (ImGui::Selectable(Databases::HotKeys[i], SelectedTimeStopHkey)) {
						UserConfig::SanatizeHotKeySelection(i);
						HotKeys::EditorTimeStop = Databases::HotKeys[i];
						UserConfig::HotKeyFileToSave.TimeStop = i;
					}
					if (SelectedTimeStopHkey) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			ImGui::Text("SlowMo");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::PushItemWidth(ImGui::GetFontSize() * 5.88235f);
			if (ImGui::BeginCombo("##SlowMoHkey", HotKeys::EditorSlowMo))
			{
				for (int i = 0; i < Databases::HotKeys.size(); i++) {
					bool SelectedSlowMoHkey = (HotKeys::EditorSlowMo == Databases::HotKeys[i]);
					if (ImGui::Selectable(Databases::HotKeys[i], SelectedSlowMoHkey)) {
						UserConfig::SanatizeHotKeySelection(i);
						HotKeys::EditorSlowMo = Databases::HotKeys[i];
						UserConfig::HotKeyFileToSave.SlowMo = i;
					}
					if (SelectedSlowMoHkey) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			ImGui::Text("GridShading");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::PushItemWidth(ImGui::GetFontSize() * 5.88235f);
			if (ImGui::BeginCombo("##GridShadingHkey", HotKeys::EditorGridShading))
			{
				for (int i = 0; i < Databases::HotKeys.size(); i++) {
					bool SelectedGridShadingHkey = (HotKeys::EditorGridShading == Databases::HotKeys[i]);
					if (ImGui::Selectable(Databases::HotKeys[i], SelectedGridShadingHkey)) {
						UserConfig::SanatizeHotKeySelection(i);
						HotKeys::EditorGridShading = Databases::HotKeys[i];
						UserConfig::HotKeyFileToSave.GridShading = i;
					}
					if (SelectedGridShadingHkey) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			ImGui::Text("Transition");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::PushItemWidth(ImGui::GetFontSize() * 5.88235f);
			if (ImGui::BeginCombo("##TransitionHKey", HotKeys::EditorTransition))
			{
				for (int i = 0; i < Databases::HotKeys.size(); i++) {
					bool SelectedTransitionHkey = (HotKeys::EditorTransition == Databases::HotKeys[i]);
					if (ImGui::Selectable(Databases::HotKeys[i], SelectedTransitionHkey)) {
						UserConfig::SanatizeHotKeySelection(i);
						HotKeys::EditorTransition = Databases::HotKeys[i];
						UserConfig::HotKeyFileToSave.Transition = i;
					}
					if (SelectedTransitionHkey) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			ImGui::SeparatorText("Fixes");
			ImGui::Text("FOV Multiplier");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::PushItemWidth(ImGui::GetFontSize() * 5.88235f);
			ImGui::DragFloat("##FovMultiplier", &UserConfig::HotFixesFileToSave.FOVMultiplier, 0.01f, 0.75f, 1.45f, "%.2f");
			ImGui::PopItemWidth();
			ImGui::Text("Blowback");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::Checkbox("##BlowBack", &UserConfig::HotFixesFileToSave.BlowBack);
			ImGui::Text("SlideLocking");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::Checkbox("##SlideLocking", &UserConfig::HotFixesFileToSave.SlideLocking);
			ImGui::Text("Disable Mouse Acceleration");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::Checkbox("##NoMouseAccel", &UserConfig::HotFixesFileToSave.DisableMouseAcceleration);
			ImGui::Text("Disable Mouse Speed Cap");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::Checkbox("##NoRotSpeedCap", &UserConfig::HotFixesFileToSave.DisableRotSpeedCap);
			ImGui::Text("Disable Menu GridShading");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::Checkbox("##NoGridShading", &UserConfig::HotFixesFileToSave.NoMenuGridShading);
			ImGui::SeparatorText("Window");
			ImGui::Text("Font Size / Scale");
			ImGui::SameLine(ImGui::GetFontSize() * 11.7647f);
			ImGui::PushItemWidth(ImGui::GetFontSize() * 5.88235f);
			ImGui::DragFloat("##FontSize", &UserConfig::GUIFileToSave.FontSize, 0.01f, 15.0f, 30.0f, "%.2f");
			ImGui::PopItemWidth();
			ImGui::EndChild();

			if (ImGui::Button("Save##SaveConfig"))
			{
				UserConfig::SaveAndReloadHotkeys();
				UserConfig::SaveAndReloadHotFixConfig();
				UserConfig::SaveAndReloadGUIConfig();
			}
			ImGui::EndTabItem();
		}
	}
	ImGui::End();
}
