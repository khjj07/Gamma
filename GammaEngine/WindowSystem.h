#pragma once
#include <Windows.h>

class Engine;

/// <summary>
/// winapi의 기본 구성을 포함하는 class
/// </summary>
class WindowSystem : public Singleton<WindowSystem>
{
public:
	WindowSystem();
	~WindowSystem();

public:
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	void Initialize(int&, int&);
	void ShutDown();
	void Run(Engine* engine);

public:
	HWND hWnd;

private:
	LPCWSTR applicationName;
	HINSTANCE hInstance;
	bool FullScreenMode = false;//전체화면 조절 변수 
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM);

static WindowSystem* ApplicationHandler = 0;
