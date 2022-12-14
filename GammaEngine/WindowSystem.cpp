#include "stdafx.h"
#include "WindowSystem.h"

WindowSystem::WindowSystem()
{

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	DirectXModule* dxModule = DirectXModule::Instance();

	switch (umsg)
	{
	case WM_SIZE:
		if (dxModule->renderTarget)
		{
			RECT rect;
			GetWindowRect(WindowSystem::Instance()->hWnd, &rect);
			dxModule->renderTarget->Resize(SizeU(rect.right - rect.left, rect.bottom - rect.top));
			Screen::height = rect.bottom - rect.top;
			Screen::width = rect.right - rect.left;
		}
		return 0;
	case WM_MOUSEWHEEL:
		Input::mouseScrollDelta = (SHORT)HIWORD(wparam);
		break;
	case WM_DESTROY:
		dxModule->Release();
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		dxModule->Release();
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

void WindowSystem::Initialize(int& screenWidth,int& screenHeight)
{
	ApplicationHandler = this;
	hInstance = GetModuleHandle(NULL);
	applicationName = L"GammaEngine";

	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// 윈도우 창 스타일 세팅
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMMAENGINE));
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDI_WINLOGO);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCEW(IDC_GAMMAENGINE);
	wc.lpszClassName = applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	int posX = 0;
	int posY = 0;

	if (FullScreenMode)
	{
		DEVMODE dmScreenSetting;
		memset(&dmScreenSetting, 0, sizeof(dmScreenSetting));
		dmScreenSetting.dmSize = sizeof(dmScreenSetting);
		dmScreenSetting.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSetting.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSetting.dmBitsPerPel = 32;
		dmScreenSetting.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		ChangeDisplaySettings(&dmScreenSetting, CDS_FULLSCREEN);
	}
	else
	{
		//posX = (GetSystemMetrics(SM_CXSCREEN)) - screenWidth / 2;
		//posY = (GetSystemMetrics(SM_CYSCREEN)) - screenHeight / 2;
	}

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, applicationName, applicationName, WS_OVERLAPPEDWINDOW, posX, posY, screenWidth, screenHeight, NULL, NULL, hInstance, NULL);
	
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	
	DirectXModule* dxModule = DirectXModule::Instance();
	Input* input = Input::Instance();

	dxModule->Initialize(hWnd);
	input->Initialize(hWnd);
}

void WindowSystem::Run(Engine* engine)
{
	Time* time = Time::Instance();
	
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			time->Frame();
			if (!engine->Frame())
				break;
		}
	}
}

void WindowSystem::ShutDown()
{
	if (FullScreenMode)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(hWnd);
	hWnd = NULL;

	UnregisterClass(applicationName, hInstance);
	hInstance = NULL;
	ApplicationHandler = NULL;
}

