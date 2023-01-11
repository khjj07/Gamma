#pragma once
#include <vector>
using namespace std;

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

class RenderModule;
class Material;

namespace GammaEngine
{
	struct DebugShape
	{
		Material* material;
		DebugShape(Material*  material) : material(material)
		{

		}
	};

	struct DebugRect : public DebugShape
	{
		vector2 pos;
		vector2 size;
		float rotation;
		DebugRect(vector2 pos, vector2 size, float rotation, Material* material)
			: pos(pos), size(size), rotation(rotation), DebugShape(material)
		{

		};
	};

	struct DebugEllipse : public DebugShape
	{
		vector2 pos;
		vector2 size;
		float rotation;
		DebugEllipse(vector2 pos, vector2 size, float rotation, Material* material)
			: pos(pos), size(size), rotation(rotation), DebugShape(material)
		{

		};
	};

	struct DebugLine: public DebugShape
	{
		vector2 start;
		vector2 end;
		float thickness;
		DebugLine(vector2 start, vector2 end, float thickness, Material* material)
			: start(start), end(end), thickness(thickness), DebugShape(material)
		{

		};
	};

	/// <summary>
	/// 디버그용 클래스
	/// </summary>
	/// 
	/// #ifdef GammaEngineAPI_Exporting
	class GammaEngineAPI Debug
	{
	public:
		friend class GraphicSystem;

	public:
		Debug();
		~Debug();

	private:
		static void Render();

	public:
		static void DrawRectangle(vector2 pos, vector2 size, float rotation, Material* meterial);
		static void DrawEllipse(vector2 pos, vector2 size, float rotation, Material* meterial);
		static void DrawLine(vector2 start, vector2 end, float thickness, Material* meterial);

	public:
		static vector<GammaEngine::DebugRect*> rect;
		static vector<GammaEngine::DebugEllipse*> ellipse;
		static vector<GammaEngine::DebugLine*> line;
	};
}