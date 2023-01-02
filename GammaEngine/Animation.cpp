#include "stdafx.h"
using namespace GammaEngine;

function<void(AnimationData*)> GammaEngine::Animation::PlayFunction[6] = {
	PlayOnceForward,
	PlayOnceBackward,
	PlayOncePingpong,
	PlayLoopForward,
	PlayLoopBackward,
	PlayLoopPingpong
};

GammaEngine::Animation::Animation(GameObject* t) :Component(t)
{

}

GammaEngine::Animation::~Animation()
{

}

void GammaEngine::Animation::PlayOnceForward(AnimationData* data)
{
	data->handler = Timer::Delay(data->playtime / data->images.size(), true, [data]() {
		data->image = GraphicSystem::LoadBitmapImage(data->images[data->count]);
		if (data->count == data->images.size() - 1)
		{
			Timer::Cancel(data->handler);
		}
		else
		{
			data->count++;
		}
	});
}	

void GammaEngine::Animation::PlayOnceBackward(AnimationData* data)
{
	data->count = data->images.size() - 1;
	data->handler = Timer::Delay(data->playtime / data->images.size(), true, [data]() {
		data->image = GraphicSystem::LoadBitmapImage(data->images[data->count]);
		if (data->count == 0)
		{
			Timer::Cancel(data->handler);
		}
		else
		{
			data->count--;
		}
	});
}

void GammaEngine::Animation::PlayOncePingpong(AnimationData* data)
{
	data->forward = true;
	data->count = 0;
	data->handler = Timer::Delay(data->playtime / data->images.size() * 0.5, true, [data]() {
		data->image = GraphicSystem::LoadBitmapImage(data->images[data->count]);
		if (data->forward && data->count == data->images.size() - 1)
		{
			data->forward = false;
		}
		else if (!data->forward && data->count == 0)
		{
			Timer::Cancel(data->handler);
		}

		if (data->forward)
		{
			data->count++;
		}
		else
		{
			data->count--;
		}
	});
}

void GammaEngine::Animation::PlayLoopForward(AnimationData* data)
{
	data->count = 0;
	data->handler = Timer::Delay(data->playtime / data->images.size(), true, [data]() {
		data->image = GraphicSystem::LoadBitmapImage(data->images[data->count]);
		if (data->count == data->images.size() - 1)
		{
			data->count = 0;
		}
		else
		{
			data->count++;
		}
	});
}

void GammaEngine::Animation::PlayLoopBackward(AnimationData* data)
{
	data->count = data->images.size() - 1;
	data->handler = Timer::Delay(data->playtime / data->images.size(), true, [data]() {
		data->image = GraphicSystem::LoadBitmapImage(data->images[data->count]);
		if (data->count == 0)
		{
			data->count = data->images.size() - 1;
		}
		else
		{
			data->count--;
		}
	});
}

void GammaEngine::Animation::PlayLoopPingpong(AnimationData* data)
{
	data->count = 0;
	data->forward = true;
	data->handler = Timer::Delay(data->playtime / data->images.size() * 0.5, true, [data]() {
		data->image = GraphicSystem::LoadBitmapImage(data->images[data->count]);
		if (data->forward && data->count == data->images.size() - 1)
		{
			data->forward = false;
		}
		else if (!data->forward && data->count == 0)
		{
			data->forward = true;
		}

		if (data->forward)
		{
			data->count++;
		}
		else
		{
			data->count--;
		}
	});
}

void GammaEngine::Animation::Play(PLAYBACK playback)
{
	BitmapRenderer* bitmapRenderer = GetComponent<BitmapRenderer>();
	AnimationData* data = new AnimationData(bitmapRenderer->bitmap, images);
	PlayFunction[playback](data);
}

void GammaEngine::Animation::AddFrame(wstring image)
{
	images.push_back(image);
}