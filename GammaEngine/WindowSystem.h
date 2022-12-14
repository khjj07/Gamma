#pragma once
#include <Windows.h>

class Engine;

/// <summary>
/// winapi�� �⺻ ������ �����ϴ� class
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
	bool FullScreenMode = false;//��üȭ�� ���� ���� 
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM);

static WindowSystem* ApplicationHandler = 0;
