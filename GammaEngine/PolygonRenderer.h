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
	/// �簢�� ������
	/// </summary>
	class GammaEngineAPI PolygonRenderer : public Renderer
	{
	public:
		PolygonRenderer(GameObject* g);
		~PolygonRenderer();

	public:
		virtual void Render();

	public:
		void SetPoints(vector<vector2>);
		void AddPoints(vector2);
		void MakePolygon(wstring name);

	public:
		vector<vector2>* points;
		wstring* name;
	};
}