#pragma once
#include <vector>

using namespace std;

class RenderModule;
class Renderer;
class Metrerial;
/// <summary>
/// Direct2D�� �⺻���� ����� �����ϴ� class
/// </summary>
class GraphicSystem : public Singleton<GraphicSystem>
{
public:
	GraphicSystem();
	~GraphicSystem();

public:
	void Initialize(HWND);
	void Frame();
	void Release();
public:
	static void DrawRectangle(vector2 pos, vector2 size, float rotation, Metrerial* meterial);
public:
	RenderModule* render;

public:
	vector<Renderer*> renderComponentList;
	vector<Renderer*>::iterator renderComponentIter;
	
};

