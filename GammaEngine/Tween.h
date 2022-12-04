#pragma once
#include <functional>
using namespace std;
#define TWEEN_STEP 0.01
class TimerHandler;
enum PLAYBACK
{
	ONCE_FORWARD,
	ONCE_BACKWARD,
	ONCE_PINGPONG,
	LOOP_FORWARD,
	LOOP_BACKWARD,
	LOOP_PINGPONG
};

enum EASING
{
	LINEAR,
	INBACK,
	OUTBACK,
	INOUTBACK,
	INBOUNCE,
	OUTBOUNCE,
	INOUTBOUNCE,
	INELASTIC,
	OUTELASTIC,
	INOUTELASTIC,
	INSINE,
	OUTSINE,
	INOUTSINE,
	INEXPO,
	OUTEXPO,
	INOUTEXPO,
	INCIRC,
	OUTCIRC,
	INOUTCIRC,
	INQUAD,
	OUTQUAD,
	INOUTQUAD,
	INCUBIC,
	OUTCUBIC,
	INOUTCUBIC,
	INQUART,
	OUTQUART,
	INOUTQUART,
	INQUINT,
	OUTQUINT,
	INOUTQUINT
};
struct TweenData
{
	float duration;
	function<void()> callback;
	float accumulation;
	TimerHandler* handler;
};

struct TweenDataF :public TweenData
{
	function<float(float)> easingFunc;
	float& src;
	float dst;
	float original;
	float difference;
	TweenDataF(float& s,float d, function<float(float)> ef, float dur, function<void()> cb):src(s)
	{
		original = s;
		difference = d - s;
		dst = d;
		easingFunc = ef;
		duration = dur;
		callback = cb;
		accumulation = 0;
	};
};

struct TweenDataV :public TweenData
{
	function<float(float)> easingFunc;
	vector2& src;
	vector2 dst;
	vector2 original;
	vector2 difference;
	TweenDataV(vector2& s, vector2 d, function<float(float)> ef, float dur, function<void()> cb) :src(s)
	{
		original = s;
		difference = d - s;
		dst = d;
		easingFunc = ef;
		duration = dur;
		callback = cb;
		accumulation = 0;
	};
};

class Tween
{
public:
	Tween();
	~Tween();
public:
	static void CancelAnimate(TweenData* data);
	static TweenData* Animate(float& src,PLAYBACK playback,float dst, EASING easing,float duration,float delay=0,function<void()> callback=nullptr);
	static TweenData* Animate(vector2& src,PLAYBACK playback,vector2 dst, EASING easing,float duration,float delay=0,function<void()> callback=nullptr);
private:
	static function<float(float)> easingFuction[31];
	static function<void(TweenDataF*)> stepF[6];
	static function<void(TweenDataV*)> stepV[6];

};



static void StepOnceForwardF(TweenDataF* data);
static void StepOnceBackwardF(TweenDataF* data);
static void StepOncePingpongF(TweenDataF* data);
static void StepLoopForwardF(TweenDataF* data);
static void StepLoopBackwardF(TweenDataF* data);
static void StepLoopPingpongF(TweenDataF* data);


static void StepOnceForwardV(TweenDataV* data);
static void StepOnceBackwardV(TweenDataV* data);
static void StepOncePingpongV(TweenDataV* data);
static void StepLoopForwardV(TweenDataV* data);
static void StepLoopBackwardV(TweenDataV* data);
static void StepLoopPingpongV(TweenDataV* data);


static float easeLinear(float x);
static float easeInSine(float x);
static float easeOutSine(float x);
static float easeInOutSine(float x);
static float easeInCubic(float x);
static float easeOutCubic(float x);
static float easeInOutCubic(float x);
static float easeInQuint(float x);
static float easeOutQuint(float x);
static float easeInOutQuint(float x);
static float easeInCirc(float x);
static float easeOutCirc(float x);
static float easeInOutCirc(float x);
static float easeInElastic(float x);
static float easeOutElastic(float x);
static float easeInOutElastic(float x);
static float easeInQuad(float x);
static float easeOutQuad(float x);
static float easeInOutQuad(float x);
static float easeInQuart(float x);
static float easeOutQuart(float x);
static float easeInOutQuart(float x);
static float easeInExpo(float x);
static float easeOutExpo(float x);
static float easeInOutExpo(float x);
static float easeInBack(float x);
static float easeOutBack(float x);
static float easeInOutBack(float x);
static float easeOutBounce(float x);
static float easeInBounce(float x);
static float easeInOutBounce(float x);