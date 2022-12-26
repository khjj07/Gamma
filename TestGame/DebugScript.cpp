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
		swprintf_s(str, L"fps = %d \n�����̽� : ���� �ٲٱ�(�簢��,��)\n����� ��Ŭ�� : ���� ����\n���� ��Ŭ�� : ���� ����\nWASD : ���õ� ���� �̵�\nQE : ���õ� ����ȸ��\n����Ű : ī�޶� �̵�\n���콺 ��ũ�� : ī�޶� ����/�ܾƿ�", frameCnt);
		fps = wstring(str);
		frameCnt = 0;
		accum = 0;
	}
	transform->GetComponent<TextRenderer>()->text = fps;
	frameCnt++;
	accum += Time::deltaTime;
}