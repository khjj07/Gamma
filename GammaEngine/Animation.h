#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// <summary>
/// 애니메이션 컴포넌트
/// </summary>
namespace GammaEngine {
	
	

	struct GammaEngineAPI AnimationData {
		TimerHandler* handler;
		wstring& image;
		vector<wstring>& images;
		float playtime;
		int count;
		bool forward;

		AnimationData(wstring& img, vector<wstring>& imgs,float fps)
			:handler(nullptr),
			image(img),
			images(imgs),
			playtime(fps),
			count(0),
			forward(true){}
	};

	template class GammaEngineAPI std::function<void(AnimationData*)>;

	class GammaEngineAPI Animation
	{
	public:
		Animation();
		~Animation();

	public:
		void Play(wstring& ,PLAYBACK);
		void Pause();
		void AddFrame(wstring);
		void SetFPS(float);

	private:
		static void PlayOnceForward(AnimationData* data);
		static void PlayOnceBackward(AnimationData* data);
		static void PlayOncePingpong(AnimationData* data);
		static void PlayLoopForward(AnimationData* data);
		static void PlayLoopBackward(AnimationData* data);
		static void PlayLoopPingpong(AnimationData* data);
	public:
		float fps;
	private:
		static function<void(AnimationData*)> PlayFunction[6];
		TimerHandler* handler;
	private: 
		vector<wstring>* images;

	};
}

