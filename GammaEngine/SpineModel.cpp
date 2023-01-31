#include "stdafx.h"

using namespace GammaEngine;
unordered_map<string, SpineModel*>* SpineModel::spineModelMap;

GammaEngine::SpineModel::SpineModel(spine::Skeleton* skeleton, spine::AnimationStateData* animationStateData, spine::AnimationState* animationState):
	skeleton(skeleton),
	animationStateData(animationStateData),
	animationState(animationState) {}

void GammaEngine::SpineModel::Initialize()
{
	spineModelMap = new unordered_map<string, SpineModel*>();
}

string GammaEngine::SpineModel::Create(string name,string atlasName, string jsonName)
{
	
	spine::Atlas* atlas;
	spine::SkeletonData* skeletonData;
	spine::AnimationStateData* animationStateData;
	
	atlas = new spine::Atlas(atlasName.c_str(), new GammaTextureLoader());
	if (atlas->getPages().size() == 0) {
		printf("Failed to load atlas");
		delete atlas;
		exit(0);
	}

	spine::SkeletonJson json(atlas);
	skeletonData = json.readSkeletonDataFile(jsonName.c_str());
	if (!skeletonData) {
		printf("Failed to load skeleton data");
		delete atlas;
		exit(0);
	}

	animationStateData = new spine::AnimationStateData(skeletonData);

	spineModelMap->insert(make_pair(name, new SpineModel(new spine::Skeleton(skeletonData), animationStateData, new spine::AnimationState(animationStateData))));
	
	return name;
}

void GammaEngine::SpineModel::Update()
{
	animationState->update(Time::deltaTime);
	animationState->apply(*skeleton);
	skeleton->updateWorldTransform();
}

void GammaEngine::SpineModel::Render()
{
	for (size_t i = 0, n = skeleton->getSlots().size(); i < n; ++i) {
		Slot* slot = skeleton->getDrawOrder()[i];

		spine::Attachment* attachment = slot->getAttachment();
		if (!attachment) continue;
		spine::BlendMode engineBlendMode;
		switch (slot->getData().getBlendMode()) {
		case BlendMode_Normal:
			engineBlendMode = spine::BlendMode::BlendMode_Normal;
			break;
		case BlendMode_Additive:
			engineBlendMode = spine::BlendMode::BlendMode_Additive;
			break;
		case BlendMode_Multiply:
			engineBlendMode = spine::BlendMode::BlendMode_Multiply;
			break;
		case BlendMode_Screen:
			engineBlendMode = spine::BlendMode::BlendMode_Screen;
			break;
		default:
			// unknown Spine blend mode, fall back to
			// normal blend mode
			engineBlendMode = spine::BlendMode::BlendMode_Normal;
		}

    
        if (attachment->getRTTI().isExactly(spine::RegionAttachment::rtti)) {
            // Cast to an spRegionAttachment so we can get the rendererObject
            // and compute the world vertices
			spine::RegionAttachment* regionAttachment = (spine::RegionAttachment*)attachment;
			vector2 size = vector2(regionAttachment->getRegion()->width, regionAttachment->getRegion()->width);
			vector2 offset = vector2(regionAttachment->getRegion()->offsetX, regionAttachment->getRegion()->offsetY);

			vector2 translation = vector2(regionAttachment->getX(), regionAttachment->getY());
			float rotation = regionAttachment->getRotation();
			vector2 scale = vector2(regionAttachment->getScaleX(), regionAttachment->getScaleY());
			Matrix3x3 matrix = Matrix3x3::Scale(scale.x,scale.y)* Matrix3x3::Rotate(rotation) * Matrix3x3::Translation(translation.x, translation.y);
			
			wstring* bitmap = (wstring*)(regionAttachment->getRendererObject());
			
			GraphicSystem::DrawBitmap(*bitmap, size, offset, matrix, new Material());

        }
        else if (attachment->getRTTI().isExactly(MeshAttachment::rtti)) {
			return;
        }

  
       
}
}
