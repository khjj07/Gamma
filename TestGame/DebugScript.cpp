#include "GammaEngine.h"
#include "DebugScript.h"
using namespace GammaEngine;
DebugScript::DebugScript(GameObject* t) :Component(t)
{

}

DebugScript::~DebugScript()
{

}

void DebugScript::Update()
{
	transform->position = Camera::main->ScreenToWorldPoint(vector2(1400, 10));
	//transform->scale = Camera::main->ScreenToWorldScale(vector2(1, 1));

	static int frameCnt = 0;
	static double accum = 0;
	if (accum >= 1)
	{
		wchar_t str[300];
		swprintf_s(str, L"fps = %d \n스페이스 : 도형 바꾸기(사각형,원)\n빈공간 좌클릭 : 도형 생성\n도형 좌클릭 : 도형 선택\nWASD : 선택된 도형 이동\nQE : 선택된 도형회전\n방향키 : 카메라 이동\n마우스 스크롤 : 카메라 줌인/줌아웃", frameCnt);
		fps = wstring(str);
		frameCnt = 0;
		accum = 0;
	}
	transform->GetComponent<TextRenderer>()->text = fps;
	frameCnt++;
	accum += Time::deltaTime;
}