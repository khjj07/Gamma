#include "stdafx.h"
using namespace GammaEngine;

GammaEngine::Animator::Animator(GameObject* t) :Component(t)
{
	bitmapRenderer = GetComponent<BitmapRenderer>();
	animationList = new unordered_map<wstring, Animation*>();
	currentAnimation = wstring(L"");

}

GammaEngine::Animator::~Animator()
{

}

void GammaEngine::Animator::AddAnimation(wstring name,Animation* animation)
{
	(* animationList)[name] = animation;
}

wstring GammaEngine::Animator::GetCurrentAnimation()
{
	return currentAnimation;
}

void GammaEngine::Animator::Play(wstring name, PLAYBACK playback)
{
	if (currentAnimation!=wstring(L""))
	{
		(*animationList)[currentAnimation]->Pause();
	}

	if ((*animationList)[name])
	{
		currentAnimation = name;
		(*animationList)[currentAnimation]->Play((*bitmapRenderer->bitmap), playback);
	}

	
}
