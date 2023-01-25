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
		vector2 size;
		Matrix3x3 matrix;
		DebugRect( vector2 size, Matrix3x3 matrix, Material* material) :
			DebugShape(material),
			size(size),
			matrix(matrix) { };
	};

	struct DebugEllipse : public DebugShape
	{
		vector2 size;
		Matrix3x3 matrix;
		DebugEllipse(vector2 pos, Matrix3x3 matrix,  Material* material): 
			DebugShape(material),
			size(size),
			matrix(matrix) { };
	};

	struct DebugLine: public DebugShape
	{
		vector2 start;
		vector2 end;
		DebugLine(vector2 start, vector2 end, Material* material):
			DebugShape(material),
			start(start),
			end(end) { };
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
		static void DrawLine(vector2 start, vector2 end, Material* meterial);

	public:
		static vector<DebugRect*>* rect;
		static vector<DebugEllipse*>* ellipse;
		static vector<DebugLine*>* line;
	};
}