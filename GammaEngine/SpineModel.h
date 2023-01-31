#pragma once
#include <string>
#include "spine/spine.h"

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
		static string Create(string, string, string);
		static void Initialize();
		void Update();
		void Render();

	public:
		spine::Skeleton* skeleton;
		spine::AnimationStateData* animationStateData;
		spine::AnimationState* animationState;
		wstring* image;

	public:
		static unordered_map<string, SpineModel*>* spineModelMap;
	};
}
