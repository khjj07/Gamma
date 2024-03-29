#pragma once
#include "Type.h"
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif
namespace GammaEngine
{
	class Renderer;
	class Transform;

	/// <summary>
	/// ��Ʈ�� ������ ������Ʈ
	/// </summary>
	class GammaEngineAPI BitmapRenderer : public Renderer
	{
	public:
		BitmapRenderer();
		BitmapRenderer(GameObject* t);
		~BitmapRenderer();

	public:
		virtual void Render();

	public:
		void LoadBitmapImage(wstring filename);

	public:
		wstring* bitmap;
	};
}
