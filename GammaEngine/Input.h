#pragma once
struct vector2;
static enum KeyState {
	pressed,
	released,
	pressing,
	not
};


class Input : public Singleton<Input>
{
public:
	Input();
	~Input();

	void Initialize(HWND hwnd);
	void Frame();
	static bool GetKey(int);
	static bool GetKeyDown(int);
	static bool GetKeyUp(int);
	static bool GetMouseButton(int);
	static bool GetMouseButtonDown(int);
	static bool GetMouseButtonUp(int);
	static vector2 GetMousePosition();
public:
	static HWND hWnd;
	static KeyState key[256];
	static int mouse[3];
	static short mouseScrollDelta;
private:

};

