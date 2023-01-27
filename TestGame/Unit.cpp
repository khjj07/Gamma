#include "GammaEngine.h"
#include "Unit.h"
#include "Troops.h"
#include "GameManager.h"

using namespace GammaEngine;

Unit::Unit(GameObject* t) :
	Component(t),
	speed(50)
{

}

Unit::~Unit()
{

}

void Unit::Start()
{
	GetComponent<BitmapRenderer>()->LoadBitmapImage(L"Spearman\\Idle\\Spearman_Idle1.png");
	Animation* idle = new Animation();
	idle->AddFrame(L"Spearman\\Idle\\Spearman_Idle1.png");
	idle->AddFrame(L"Spearman\\Idle\\Spearman_Idle2.png");
	idle->AddFrame(L"Spearman\\Idle\\Spearman_Idle3.png");
	idle->AddFrame(L"Spearman\\Idle\\Spearman_Idle4.png");
	idle->AddFrame(L"Spearman\\Idle\\Spearman_Idle5.png");
	idle->SetFPS(1.0f);
	Animation* run = new Animation();
	run->AddFrame(L"Spearman\\Run\\Spearman_run1.png");
	run->AddFrame(L"Spearman\\Run\\Spearman_run2.png");
	run->AddFrame(L"Spearman\\Run\\Spearman_run3.png");
	run->AddFrame(L"Spearman\\Run\\Spearman_run4.png");
	run->AddFrame(L"Spearman\\Run\\Spearman_run5.png");
	run->AddFrame(L"Spearman\\Run\\Spearman_run6.png");
	run->AddFrame(L"Spearman\\Run\\Spearman_run7.png");
	run->AddFrame(L"Spearman\\Run\\Spearman_run8.png");
	run->AddFrame(L"Spearman\\Run\\Spearman_run9.png");
	run->AddFrame(L"Spearman\\Run\\Spearman_run10.png");
	run->SetFPS(1.0f);

	GetComponent<Animator>()->AddAnimation(wstring(L"Idle"), idle);
	GetComponent<Animator>()->AddAnimation(wstring(L"Run"), run);

	GetComponent<Animator>()->Play(wstring(L"Idle"),PLAYBACK::LOOP_FORWARD);
}

void Unit::Move(vector2 v)
{
	if (vector2::Distance(v, transform->position) > 10)
	{
		state = UnitState::MoveToTarget;
		targetPoint = v;
	}
	else
	{
		state = UnitState::Wait;
	}
}

void Unit::Update()
{
	if (state == UnitState::MoveToTarget && GetComponent<Animator>()->GetCurrentAnimation() == wstring(L"Idle"))
	{
		GetComponent<Animator>()->Play(wstring(L"Run"), PLAYBACK::LOOP_FORWARD);
	}
	else if (state == UnitState::Wait && GetComponent<Animator>()->GetCurrentAnimation() == wstring(L"Run"))
	{
		GetComponent<Animator>()->Play(wstring(L"Idle"), PLAYBACK::LOOP_FORWARD);
	}

	if (state == UnitState::MoveToTarget )
	{
		vector2 direction = vector2::Normalize(targetPoint - transform->position);
		float distance = vector2::Distance(targetPoint, transform->position);
		GetComponent<Rigidbody>()->ApplyForce(direction * speed);
		if (vector2::Distance(targetPoint, transform->position) < 20)
		{
			state = UnitState::Wait;
		}
	}
}

void Unit::OnCollisionStay(CollisionResponse)
{
	//GetComponent<EllipseRenderer>()->SetPen(vector4(1, 1, 0, 1));
}

void Unit::OnCollisionExit(CollisionResponse)
{
	
}