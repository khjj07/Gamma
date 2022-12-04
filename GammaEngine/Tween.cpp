#include "stdafx.h"


function<void(TweenDataF*)> Tween::stepF[6] = {
	StepOnceForwardF,
	StepOnceBackwardF,
	StepOncePingpongF,
	StepLoopForwardF,
	StepLoopBackwardF,
	StepLoopPingpongF
};
function<void(TweenDataV*)> Tween::stepV[6] = {
	StepOnceForwardV,
	StepOnceBackwardV,
	StepOncePingpongV,
	StepLoopForwardV,
	StepLoopBackwardV,
	StepLoopPingpongV
};

function<float(float)> Tween::easingFuction[31] = {
easeLinear,
easeInBack,
easeOutBack,
easeInOutBack,
easeInBounce,
easeOutBounce,
easeInOutBounce,
easeInElastic,
easeOutElastic,
easeInOutElastic,
easeInSine,
easeOutSine,
easeInOutSine,
easeInExpo,
easeOutExpo,
easeInOutExpo,
easeInCirc,
easeOutCirc,
easeInOutCirc,
easeInQuad,
easeOutQuad,
easeInOutQuad,
easeInCubic,
easeOutCubic,
easeInOutCubic,
easeInQuart,
easeOutQuart,
easeInOutQuart,
easeInQuint,
easeOutQuint,
easeInOutQuint
};


Tween::Tween()
{
}

Tween::~Tween()
{
}
void Tween::CancelAnimate(TweenData* data)
{
	Timer::Cancel(data->handler);
	data->handler = nullptr;
	delete data;
}


TweenData* Tween::Animate(float& src, PLAYBACK playback, float dst, EASING ease, float duration, float delay, function<void()> callback)
{
	function<float(float)> easingFunc = easingFuction[ease];
	function<void(TweenDataF*)> stepFunc = stepF[playback];
	TweenDataF* data = new TweenDataF(src,dst, easingFunc,duration,callback);
	if (delay > 0)
	{
		Timer::Delay(delay, false, [stepFunc,data]() {
			stepFunc(data);
		});
	}
	else
	{
		stepFunc(data);
	}
	return data;
}

TweenData* Tween::Animate(vector2& src, PLAYBACK playback, vector2 dst, EASING ease, float duration, float delay, function<void()> callback)
{
	function<float(float)> easingFunc = easingFuction[ease];
	function<void(TweenDataV*)> stepFunc = stepV[playback];
	TweenDataV* data = new TweenDataV(src, dst, easingFunc, duration, callback);
	if (delay > 0)
	{
		Timer::Delay(delay, false, [stepFunc, data]() {
			stepFunc(data);
		});
	}
	else
	{
		stepFunc(data);
	}
	return data;
}

void StepOnceForwardF(TweenDataF* data)
{
	data->handler=Timer::Delay(TWEEN_STEP, true, [data]() {
		data->src = data->original + data->difference*data->easingFunc(data->accumulation / data->duration);
		data->accumulation += Time::deltaTime;
		if (data->accumulation >= data->duration)
		{
			data->src = data->dst;
			if (data->callback)
				data->callback();
			Timer::Cancel(data->handler);
		}
	});
	
}


void StepOnceForwardV(TweenDataV* data)
{
	data->handler = Timer::Delay(TWEEN_STEP, true, [data]() {
		data->src = data->original + data->difference * data->easingFunc(data->accumulation / data->duration);
		data->accumulation += Time::deltaTime;
		if (data->accumulation >= data->duration)
		{
			data->src = data->dst;
			if (data->callback)
				data->callback();
			Timer::Cancel(data->handler);
		}
	});
}

void StepOnceBackwardF(TweenDataF* data)
{
	data->src = data->dst;
	data->handler = Timer::Delay(TWEEN_STEP, true, [data]() {
		data->src = data->dst - data->difference*data->easingFunc(data->accumulation / data->duration);
		data->accumulation += Time::deltaTime;
		if (data->accumulation >= data->duration)
		{
			data->src = data->original;
			if(data->callback)
				data->callback();
			Timer::Cancel(data->handler);
		}
	});
}

void StepOnceBackwardV(TweenDataV* data)
{
	data->src = data->dst;
	data->handler = Timer::Delay(TWEEN_STEP, true, [data]() {
		data->src = data->dst - data->difference * data->easingFunc(data->accumulation / data->duration);
		data->accumulation += Time::deltaTime;
		if (data->accumulation >= data->duration)
		{
			data->src = data->original;
			if (data->callback)
				data->callback();
			Timer::Cancel(data->handler);
		}
	});
}

void StepOncePingpongF(TweenDataF* data)
{
	data->handler = Timer::Delay(TWEEN_STEP, true, [data]() {
		if (data->accumulation < (data->duration / 2))
		{
			data->src = data->original + data->difference*data->easingFunc(data->accumulation / (data->duration / 2));
		}
		else
		{
			data->src = data->dst - data->difference * data->easingFunc((data->accumulation- (data->duration / 2)) / (data->duration / 2)) ;
		}
		data->accumulation += Time::deltaTime;
		if (data->accumulation >= data->duration)
		{
			data->src = data->original;
			if (data->callback)
				data->callback();
			Timer::Cancel(data->handler);
		}
	});
}

void StepOncePingpongV(TweenDataV* data)
{
	data->handler = Timer::Delay(TWEEN_STEP, true, [data]() {
		if (data->accumulation < (data->duration / 2))
		{
			data->src = data->original + data->difference * data->easingFunc(data->accumulation / (data->duration / 2));
		}
		else
		{
			data->src = data->dst - data->difference * data->easingFunc((data->accumulation - (data->duration / 2)) / (data->duration / 2));
		}
		data->accumulation += Time::deltaTime;
		if (data->accumulation >= data->duration)
		{
			data->src = data->original;
			if (data->callback)
				data->callback();
			Timer::Cancel(data->handler);
		}
	});
}

void StepLoopForwardF(TweenDataF* data)
{
	data->handler = Timer::Delay(TWEEN_STEP, true, [data]() {
		data->src = data->original + data->difference * data->easingFunc(data->accumulation / data->duration) ;
		data->accumulation += Time::deltaTime;
		if (data->accumulation >= data->duration)
		{
			data->src = data->dst;
			if (data->callback)
				data->callback();
			data->accumulation = 0;
		}
	});
}


void StepLoopForwardV(TweenDataV* data)
{
	data->handler = Timer::Delay(TWEEN_STEP, true, [data]() {
		data->src = data->original + data->difference * data->easingFunc(data->accumulation / data->duration);
		data->accumulation += Time::deltaTime;
		if (data->accumulation >= data->duration)
		{
			data->src = data->dst;
			if (data->callback)
				data->callback();
			data->accumulation = 0;
		}
	});
}


void StepLoopBackwardF(TweenDataF* data)
{
	data->src = data->dst;
	data->handler = Timer::Delay(TWEEN_STEP, true, [data]() {
		data->src = data->dst - data->difference * data->easingFunc(data->accumulation / data->duration);
		data->accumulation += Time::deltaTime;
		if (data->accumulation >= data->duration)
		{
			data->src = data->original;
			if (data->callback)
				data->callback();
			data->accumulation = 0;
		}
	});
}
void StepLoopBackwardV(TweenDataV* data)
{
	data->src = data->dst;
	data->handler = Timer::Delay(TWEEN_STEP, true, [data]() {
		data->src = data->dst - data->difference * data->easingFunc(data->accumulation / data->duration);
		data->accumulation += Time::deltaTime;
		if (data->accumulation >= data->duration)
		{
			data->src = data->original;
			if (data->callback)
				data->callback();
			data->accumulation = 0;
		}
	});
}


void StepLoopPingpongF(TweenDataF* data)
{
	data->handler = Timer::Delay(TWEEN_STEP, true, [data]() {
		if (data->accumulation < (data->duration / 2))
		{
			data->src = data->original + data->difference * data->easingFunc(data->accumulation / (data->duration / 2));
		}
		else
		{
			data->src = data->dst - data->difference * data->easingFunc((data->accumulation - (data->duration / 2)) / (data->duration / 2));
		}
		data->accumulation += Time::deltaTime;
		if (data->accumulation >= data->duration)
		{
			data->src = data->original;
			if (data->callback)
				data->callback();
			data->accumulation = 0;
		}
	});
}


void StepLoopPingpongV(TweenDataV* data)
{
	data->handler = Timer::Delay(TWEEN_STEP, true, [data]() {
		if (data->accumulation < (data->duration / 2))
		{
			data->src = data->original + data->difference * data->easingFunc(data->accumulation / (data->duration / 2));
		}
		else
		{
			data->src = data->dst - data->difference * data->easingFunc((data->accumulation - (data->duration / 2)) / (data->duration / 2));
		}
		data->accumulation += Time::deltaTime;
		if (data->accumulation >= data->duration)
		{
			data->src = data->original;
			if (data->callback)
				data->callback();
			data->accumulation = 0;
		}
	});
}



float easeInSine(float x)
{
	return (float)(1 - cos((x * PI) / 2));
}

float easeOutSine(float x)
{
	return (float)(sin((x * PI) / 2));
}

float easeInOutSine(float x)
{
	return (float)(-(cos(PI * x) - 1) / 2);
}

float easeInCubic(float x)
{
	return x * x * x;
}

float easeOutCubic(float x)
{
	return (float)(1 - pow(1 - x, 3));
}

float easeInOutCubic(float x)
{
	return x < 0.5 ? 4 * x * x * x : (float)(1 - pow(-2 * x + 2, 3) / 2);
}

float easeInQuint(float x)
{
	return x * x * x * x * x;
}

float easeOutQuint(float x)
{
	return (float)(1 - pow(1 - x, 5));
}

float easeInOutQuint(float x)
{
	return x < 0.5 ? 16 * x * x * x * x * x : (float)(1 - pow(-2 * x + 2, 5) / 2);
}

float easeInCirc(float x)
{
	return (float)(1 - sqrt(1 - pow(x, 2)));
}

float easeOutCirc(float x)
{
	return (float)(sqrt(1 - pow(x - 1, 2)));
}

float easeInOutCirc(float x)
{
	return x < 0.5 ? (float)(1 - sqrt(1 - pow(2 * x, 2))) / 2 : (float)(sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;
}


float easeInElastic(float x)
{
	const float c4 = (float)((2 * PI) / 3);
	return x == 0 ? 0 : x == 1 ? 1 : (float)(-pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4));
}


float easeOutElastic(float x)
{
	const float c4 = (float)((2 * PI) / 3);
	return x == 0 ? 0 : x == 1 ? 1 : (float)(pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1);
}

float easeInOutElastic(float x)
{
	const float c5 = (float)((2 * PI) / 4.5);
	return x == 0 ? 0 : x == 1 ? 1 : x < 0.5 ? (float)(-(pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2) : (float)((pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1);
}

float easeInQuad(float x)
{
	return x * x;
}

float easeOutQuad(float x)
{
	return 1 - (1 - x) * (1 - x);
}

float easeInOutQuad(float x)
{
	return x < 0.5 ? 2 * x * x : (float)(1 - pow(-2 * x + 2, 2) / 2);
}

float easeInQuart(float x)
{
	return x * x * x * x;
}

float easeOutQuart(float x)
{
	return (float)(1 - pow(1 - x, 4));
}

float easeInOutQuart(float x)
{
	return x < 0.5 ? 8 * x * x * x * x : (float)(1 - pow(-2 * x + 2, 4) / 2);
}

float easeInExpo(float x)
{
	return x == 0 ? 0 : (float)pow(2, 10 * x - 10);
}

float easeOutExpo(float x)
{
	return x == 1 ? 1 : (float)(1 - pow(2, -10 * x));
}

float easeInOutExpo(float x)
{
	return x == 0 ? 0 : x == 1 ? 1 : x < 0.5 ? (float)(pow(2, 20 * x - 10) / 2) : (float)((2 - pow(2, -20 * x + 10)) / 2);
}

float easeInBack(float x)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;
	return c3 * x * x * x - c1 * x * x;
}

float easeOutBack(float x)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;
	return (float)(1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2));
}

float easeInOutBack(float x)
{
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;
	return x < 0.5 ? (float)((pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2) : (float)((pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2);
}

float easeOutBounce(float x)
{
	const float n1 = 7.5625;
	const float d1 = 2.75;

	if (x < 1 / d1) {
		return n1 * x * x;
	}
	else if (x < 2 / d1) {
		return n1 * (x -= 1.5f / d1) * x + 0.75f;
	}
	else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25f / d1) * x + 0.9375f;
	}
	else {
		return n1 * (x -= 2.625f / d1) * x + 0.984375f;
	}
}

float easeInBounce(float x)
{
	return 1 - easeOutBounce(1 - x);
}

float easeInOutBounce(float x)
{
	return x < 0.5 ? (1 - easeOutBounce(1 - 2 * x)) / 2 : (1 + easeOutBounce(2 * x - 1)) / 2;
}

float easeLinear(float x)
{
	return x;
}