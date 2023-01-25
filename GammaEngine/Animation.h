#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// <summary>
/// �ִϸ��̼� ������Ʈ
/// </summary>
namespace GammaEngine {
	
	

	struct GammaEngineAPI AnimationData {
		TimerHandler* handler;
		wstring& image;
		vector<wstring>& images;
		float playtime;
		int count;
		bool forward;

		AnimationData(wstring& img, vector<wstring>& imgs)
			:handler(nullptr),
			image(img),
			images(imgs),
			playtime(1.0f),
			count(0),
			forward(true){}
	};

	template class GammaEngineAPI std::function<void(AnimationData*)>;

	class GammaEngineAPI Animation : public Component
	{
	public:
		Animation(GameObject* t);
		~Animation();

	public:
		void Play(PLAYBACK);
		void AddFrame(wstring);

	private:
		static void PlayOnceForward(AnimationData* data);
		static void PlayOnceBackward(AnimationData* data);
		static void PlayOncePingpong(AnimationData* data);
		static void PlayLoopForward(AnimationData* data);
		static void PlayLoopBackward(AnimationData* data);
		static void PlayLoopPingpong(AnimationData* data);

	private:
		static function<void(AnimationData*)> PlayFunction[6];
		
	private: 
		vector<wstring>* images;
	};
}

