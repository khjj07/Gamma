#include "stdafx.h"
using namespace GammaEngine;

function<void()> GammaEngine::Animation::PlayFunction[6] = {
	PlayOnceForward,
	PlayOnceBackward,
	PlayOncePingpong,
	PlayLoopForward,
	PlayLoopBackward,
	PlayLoopPingpong
};

GammaEngine::Animation::Animation(GameObject* t) :Component(t),playtime(1.0f), count(0), image(GetComponent<BitmapRenderer>()->bitmap)
{

}

GammaEngine::Animation::~Animation()
{

}

void GammaEngine::Animation::PlayOnceForward(wstring& image, float playtime, vector<wstring>& images, int& count)
{
	TimerHandler* handler = Timer::Delay(playtime / images.size(), true, [handler,&image,images,&count]() {
		image=GraphicSystem::LoadBitmapImage(images[count]);
		if (count == images.size() - 1)
		{
			Timer::Cancel(handler);
		}
		count++;
	});
}	

void GammaEngine::Animation::PlayOnceBackward(wstring& image, float playtime, vector<wstring>& images, int& count)
{
	count = images.size() - 1;
	TimerHandler* handler = Timer::Delay(playtime / images.size(), true, [handler, &image, images, &count]() {
		image = GraphicSystem::LoadBitmapImage(images[count]);
		if (count == 0)
		{
			Timer::Cancel(handler);
		}
		count--;
	});
}

void GammaEngine::Animation::PlayOncePingpong(wstring& image, float playtime, vector<wstring>& images, int& count)
{

}

void GammaEngine::Animation::PlayLoopForward(wstring& image, float playtime, vector<wstring>& images, int& count)
{

}

void GammaEngine::Animation::PlayLoopBackward(wstring& image, float playtime, vector<wstring>& images, int& count)
{

}

void GammaEngine::Animation::PlayLoopPingpong(wstring& image, float playtime, vector<wstring>& images, int& count)
{

}

void GammaEngine::Animation::Play(PLAYBACK playback)
{
	PlayFunction[playback]();
}

void GammaEngine::Animation::AddFrame(wstring)
{

}