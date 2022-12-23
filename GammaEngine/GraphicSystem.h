#pragma once
#include <vector>
using namespace std;

class RenderModule;
class Meterial;
namespace GammaEngine
{
	class Renderer;
	/// <summary>
	/// Direct2D의 기본적인 기능을 포함하는 class
	/// </summary>
	class GammaEngineAPI GraphicSystem : public Singleton<GraphicSystem>
	{
	public:
		GraphicSystem();
		~GraphicSystem();

	public:
		void Initialize(HWND);
		void Frame();
		void Release();

	public:
		void Resize(int width, int height);

	public:
		static void DrawRectangle(vector2 pos, vector2 size, float rotation, Meterial* meterial);
		static void DrawEllipse(vector2 pos, vector2 size, float rotation, Meterial* meterial);
		static void DrawLine(vector2 start, vector2 end, float thickness, Meterial* meterial);
		static void DrawTextBox(vector2 pos, vector2 size, string text, string fontFamily, Meterial* meterial);
		static void DrawBitmap(string bitmap, vector2 pos, vector2 size, float rotation, Meterial* meterial);
		static string LoadBitmapImage(string filename);
		static vector2 GetBitmapSize(string bitmap);

	public:
		static RenderModule* render;

	public:
		vector<Renderer*> renderComponentList;
		vector<Renderer*>::iterator renderComponentIter;
	};
}


