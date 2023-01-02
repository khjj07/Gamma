#include "stdafx.h"
using namespace GammaEngine;

function<void(wstring&, float, vector<wstring>&, int&)> GammaEngine::Animation::PlayFunction[6] = {
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
	count = 0;
	TimerHandler* handler = Timer::Delay(playtime / images.size(), true, [&image, handler,images,&count]() {
		wstring image = GraphicSystem::LoadBitmapImage(images[count]);
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
	TimerHandler* handler = Timer::Delay(playtime / images.size(), true, [&image, handler, images, &count]() {
		wstring image = GraphicSystem::LoadBitmapImage(images[count]);
		if (count == 0)
		{
			Timer::Cancel(handler);
		}
		count--;
	});
}

void GammaEngine::Animation::PlayOncePingpong(wstring& image, float playtime, vector<wstring>& images, int& count)
{
	bool forward = true;
	count = 0;
	TimerHandler* handler = Timer::Delay(playtime / images.size() * 0.5, true, [&image, &forward, playtime, handler,images, &count]() {
		wstring image = GraphicSystem::LoadBitmapImage(images[count]);
		if (forward && count == images.size() - 1)
		{
			forward = false;
		}
		else if (!forward && count == 0)
		{
			Timer::Cancel(handler);
		}

		if (forward)
		{
			count++;
		}
		else
		{
			count--;
		}
	});
}

void GammaEngine::Animation::PlayLoopForward(wstring& image, float playtime, vector<wstring>& images, int& count)
{
	count = 0;
	TimerHandler* handler = Timer::Delay(playtime / images.size(), true, [&image, handler, images, &count]() {
		wstring image = GraphicSystem::LoadBitmapImage(images[count]);
		if (count == images.size() - 1)
		{
			count = 0;
		}
		count++;
		});
}

void GammaEngine::Animation::PlayLoopBackward(wstring& image, float playtime, vector<wstring>& images, int& count)
{
	count = images.size() - 1;
	TimerHandler* handler = Timer::Delay(playtime / images.size(), true, [&image, handler, images, &count]() {
		wstring image = GraphicSystem::LoadBitmapImage(images[count]);
		if (count == 0)
		{
			count = images.size() - 1;
		}
		count--;
		});
}

void GammaEngine::Animation::PlayLoopPingpong(wstring& image, float playtime, vector<wstring>& images, int& count)
{
	count = 0;
	bool forward = true;
	TimerHandler* handler = Timer::Delay(playtime / images.size() * 0.5, true, [&image, &forward, playtime, handler, images, &count]() {
		image = GraphicSystem::LoadBitmapImage(images[count]);
		if (forward && count == images.size() - 1)
		{
			forward = false;
		}
		else if (!forward && count == 0)
		{
			forward = true;
		}

		if (forward)
		{
			count++;
		}
		else
		{
			count--;
		}
	});
}

void GammaEngine::Animation::Play(PLAYBACK playback)
{
	PlayFunction[playback](image, playtime, images, count);
}

void GammaEngine::Animation::AddFrame(wstring image)
{
	images.push_back(image);
}