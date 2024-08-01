#include "DXHook.h"
#include "SadGUI.h"
#include "HotKeys.h"
#include "CameraToolMonitor.h"

void DXHook::Initialize() {
	ShowGUI = false;
	HookInitiated = false;
	Main();
}

void DXHook::Main() {
	GetPresent();
	MH_CreateHook(reinterpret_cast<void**>(NewPresent), &Present_Detour, reinterpret_cast<void**>(&oPresent));
	MH_EnableHook(NewPresent);	
}


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT APIENTRY DXHook::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
	ImGuiIO& io = ImGui::GetIO();

	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		io.MouseDown[0] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		io.MouseDown[0] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_RBUTTONDOWN:
		io.MouseDown[1] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_RBUTTONUP:
		io.MouseDown[1] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MBUTTONDOWN:
		io.MouseDown[2] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MBUTTONUP:
		io.MouseDown[2] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEWHEEL:
		io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		io.MousePos.x = (signed short)(lParam);
		io.MousePos.y = (signed short)(lParam >> 16);
		break;
	}

	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}




long DXHook::Present_Detour(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags) {

	if (!HookInitiated) {
		if (SUCCEEDED(p_swap_chain->GetDevice(__uuidof(ID3D11Device), (void**)&p_device)))
		{
			p_device->GetImmediateContext(&p_context);
			DXGI_SWAP_CHAIN_DESC sd;
			p_swap_chain->GetDesc(&sd);
			WindowHandle = sd.OutputWindow;
			GetWindowRect(WindowHandle, &WindowSize);
			ID3D11Texture2D* pBackBuffer;
			p_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			p_device->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			ImGui::CreateContext();
			ImGui_ImplWin32_Init(WindowHandle);
			ImGui_ImplDX11_Init(p_device, p_context);
			SadGUI::ReloadFont = true;
			HookInitiated = true;
		}
		else
			return oPresent(p_swap_chain, sync_interval, flags);
	}

	RECT CurrentWindowSize;
	GetWindowRect(WindowHandle, &CurrentWindowSize);
	if (CurrentWindowSize != WindowSize)
		HookInitiated = false;

	static bool GUIToggle = false;
	if (GetAsyncKeyState(HotKeys::GUI) < 0 && !GUIToggle) {
		ShowGUI = !ShowGUI;
		if (ShowGUI) {
			oWndProc = (WNDPROC)SetWindowLongPtr(WindowHandle, GWLP_WNDPROC, (LONG_PTR)WndProc);
			PostMessage(WindowHandle, WM_KILLFOCUS, 0, 0);
			Monitor::RemoveControl = true;
			Misc::DisableInputListening(true);
		}
		else {
			SetWindowLongPtr(WindowHandle, GWLP_WNDPROC, (LONG_PTR)(oWndProc));
			PostMessage(WindowHandle, WM_SETFOCUS, 0, 0);
			PostMessage(WindowHandle, 0x0201, 1, 0);
			Monitor::RestoreControl = true;
			Misc::DisableInputListening(false);
		}
	}

	GUIToggle = GetKeyState(HotKeys::GUI) < 0;

	if (SadGUI::ReloadFont) {
		ImGuiIO& io = ImGui::GetIO();
		io.FontDefault = io.Fonts->AddFontFromFileTTF(SadGUI::Font.c_str(), SadGUI::FontSize, nullptr, io.Fonts->GetGlyphRangesJapanese());
		ImGui::GetIO().Fonts->Build();
		ImGui_ImplDX11_InvalidateDeviceObjects();
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();


	ImGui::NewFrame();
	if (SadGUI::ReloadFont) {
		SadGUI::LoadImguiTheme();
		SadGUI::ReloadFont = false;
	}
		
	if (ShowGUI) {
		SadGUI::ShowCameraTool();
	}
	ImGui::EndFrame();
	ImGui::Render();
	p_context->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(p_swap_chain, sync_interval, flags);
}

void DXHook::GetPresent()
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = GetForegroundWindow();
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	IDXGISwapChain* swap_chain;
	ID3D11Device* device;

	const D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE, NULL, 0, feature_levels,
		2, D3D11_SDK_VERSION, &sd, &swap_chain, &device, nullptr, nullptr) == S_OK)
	{
		void** p_vtable = *reinterpret_cast<void***>(swap_chain);
		swap_chain->Release();
		device->Release();
		NewPresent = (present)p_vtable[8];
	}
}