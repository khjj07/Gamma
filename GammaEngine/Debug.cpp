#include "stdafx.h"
#include "Debug.h"

Debug::Debug()
{
	AddComponent<TextRenderer>();
	AddComponent<DebugScript>();
	GetComponent<TextRenderer>()->size = vector2(500, 1000);
}

Debug::~Debug()
{

}

DebugScript::DebugScript() :Component()
{

}

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
		char str[1024];
		sprintf_s(str, sizeof(str), "fps = %d \n���콺 ��Ŭ�� : box ����\n���콺 ��Ŭ�� : circle ����\n���콺 ��ũ�� : ����/�ܾƿ�", frameCnt);
		fps = string(str);
		frameCnt = 0;
		accum = 0;
	}
	transform->GetComponent<TextRenderer>()->text = fps;
	frameCnt++;
	accum += Time::deltaTime;
}