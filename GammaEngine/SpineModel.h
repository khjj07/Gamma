#pragma once
#include <string>

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

class Component;
class Transform;

/// <summary>
/// Spine model class
/// </summary>
namespace GammaEngine
{
	class GammaEngineAPI SpineModel
	{
	public:
		SpineModel(spine::Skeleton*, spine::AnimationStateData*, spine::AnimationState*);
	public:
		static wstring Create(wstring,string, string);
		static void Initialize();
		void Update();
	public:
		spine::Skeleton* skeleton;
		spine::AnimationStateData* animationStateData;
		spine::AnimationState* animationState;

	public:
		static unordered_map<wstring, SpineModel*>* spineModelMap;
	};
}
