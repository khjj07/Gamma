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
	/// ºñÆ®¸Ê ·»´õ·¯ ÄÄÆ÷³ÍÆ®
	/// </summary>
	class GammaEngineAPI BitmapRenderer : public Renderer
	{
	public:
		BitmapRenderer();
		BitmapRenderer(GameObject* t);
		~BitmapRenderer();

	public:
		virtual void Render() abstract;

	public:
		void LoadBitmapImage(string filename);

	public:
		string bitmap;
	};
}
