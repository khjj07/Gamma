#include "GammaEngine.h"
#include "Troops.h"
#include "GameManager.h"

using namespace GammaEngine;

Troops::Troops(GameObject* t) :
	Component(t),
	speed(10)
{

}

Troops::~Troops()
{

}

void Troops::Start()
{

	GameManager::selectSubject
		.Where([this](auto x) {
		return find(x.begin(), x.end(), this) == x.end() ? false : true;
	}).Subscribe([this](auto x) {
		GetComponent<EllipseRenderer>()->SetPen(vector4(1, 0, 0, 1));
	});

	GameManager::selectSubject
		.Where([this](auto x) {
		return find(x.begin(), x.end(), this) == x.end() ? true : false;
	}).Subscribe([this](auto x) {
		GetComponent<EllipseRenderer>()->SetPen(vector4(0, 0, 0, 1));
	});

	GameManager::commandSubject
		.Where([this](auto x) {
		return find(x.troops.begin(), x.troops.end(), this) == x.troops.end() ? false : true;
	})
		.Subscribe([this](auto x) {
		targetPoint = x.coordinate;
		state = TroopState::MoveToTarget;
	});
}

void Troops::Update()
{
	if (state == TroopState::MoveToTarget)
	{
		vector2 direction = vector2::Normalize(targetPoint - transform->position);
		float distance = vector2::Distance(targetPoint, transform->position);
		velocity = speed * direction;
		if (vector2::Distance(targetPoint, transform->position) < 20)
		{
			state = TroopState::Wait;
		}
	}
	else
	{
		velocity = vector2();
	}
	
	transform->position = velocity * Time::deltaTime;
}

void Troops::Join(Unit* unit)
{

}


void Troops::OnCollisionStay(CollisionResponse)
{
	//GetComponent<EllipseRenderer>()->SetPen(vector4(1, 1, 0, 1));
}

void Troops::OnCollisionExit(CollisionResponse)
{

}

