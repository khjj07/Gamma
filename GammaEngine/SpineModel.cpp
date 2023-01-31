#include "stdafx.h"
using namespace GammaEngine;
unordered_map<wstring, SpineModel*>* SpineModel::spineModelMap;

GammaEngine::SpineModel::SpineModel(spine::Skeleton* skeleton, spine::AnimationStateData* animationStateData, spine::AnimationState* animationState):
	skeleton(skeleton),
	animationStateData(animationStateData),
	animationState(animationState){}

void GammaEngine::SpineModel::Initialize()
{
	spineModelMap = new unordered_map<wstring, SpineModel*>();
}

wstring GammaEngine::SpineModel::Create(wstring name, wstring atlasName, wstring jsonName)
{
	auto atlas = spine::Atlas::createFromFile(atlasName.c_str(), nullptr);
	spine::SkeletonJson sjson(*atlas);
	auto data = sjson.readSkeletonDataFile(jsonName.c_str());
	auto skeleton = new spine::Skeleton(*data);
	auto animationStateData = new spine::AnimationStateData(*data);
	auto animState = new spine::AnimationState(*animationStateData);
	spineModelMap->insert(make_pair(name, new SpineModel(skeleton, animationStateData, animState)));


	return name;
}

void GammaEngine::SpineModel::Update()
{
	skeleton->update(Time::deltaTime);
}

void GammaEngine::SpineModel::Render()
{


	GraphicSystem::DrawBitmap()
}
