#pragma once
#include <vector>
using namespace std;

class RenderModule;
class Material;
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
		static void DrawRectangle(vector2 size, Matrix3x3 matrix, Material* material);
		static void DrawPolygon(wstring name, Matrix3x3 matrix, Material* material);
		static void DrawEllipse(vector2 size, Matrix3x3 matrix, Material* material);
		static void DrawLine(vector2 start, vector2 end, Material* material);
		static void DrawTextBox(vector2 size, Matrix3x3 matrix, wstring text, wstring fontFamily, Material* material);
		static void DrawBitmap(wstring bitmap,vector2 size, Matrix3x3 matrix, Material* material);
		static wstring LoadBitmapImage(wstring);
		static wstring MakePolygon(wstring, vector<vector2>);
		static vector2 GetBitmapSize(wstring);

	public:
		static RenderModule* render;

	public:
		vector<Renderer*>* renderComponentList;
	};
}


