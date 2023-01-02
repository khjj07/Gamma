#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// <summary>
/// ��ġ ũ�� ȸ�� ������ �����ϴ� ������Ʈ
/// </summary>
namespace GammaEngine {
	class GammaEngineAPI Animation : public Component
	{
	public:
		Animation(GameObject* t);
		~Animation();

	public:
		void Play(PLAYBACK);
		void AddFrame(wstring);

	private:
		static void PlayOnceForward(wstring& image, float playtime, vector<wstring>& images, int& count);
		static void PlayOnceBackward(wstring& image, float playtime, vector<wstring>& images, int& count);
		static void PlayOncePingpong(wstring& image, float playtime, vector<wstring>& images, int& count);
		static void PlayLoopForward(wstring& image, float playtime, vector<wstring>& images, int& count);
		static void PlayLoopBackward(wstring& image, float playtime, vector<wstring>& images, int& count);
		static void PlayLoopPingpong(wstring& image, float playtime, vector<wstring>& images, int& count);

	public:
		float playtime;

	private:
		static function<void(wstring&, float, vector<wstring>&, int&)> PlayFunction[6];
		wstring& image;
	private: 
		vector<wstring> images;
		int count;
	};
}

