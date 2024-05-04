#pragma once
#include "GlobalHeaders.h"

class DXHook
{
public:
	static void Initialize();

	typedef long (*present)(IDXGISwapChain*, UINT, UINT);
	inline static present oPresent;
	inline static present NewPresent;
	inline static ID3D11Device* p_device = NULL;
	inline static ID3D11DeviceContext* p_context = NULL;
	inline static ID3D11RenderTargetView* mainRenderTargetView = NULL;
	inline static HWND WindowHandle = NULL;
	inline static RECT WindowSize;
	inline static WNDPROC oWndProc;
	inline static DirectX::XMFLOAT3 oCamRotation;
	inline static bool HookInitiated;
	inline static bool ShowGUI;

	inline static void Main();
	static void GetPresent();
	inline static long Present_Detour(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags);
	inline static LRESULT APIENTRY WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};