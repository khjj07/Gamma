#include "GammaEngine.h"
#include "Troops.h"
#include "GameManager.h"

using namespace GammaEngine;

Troops::Troops(GameObject* t) : Component(t)
{

}

Troops::~Troops()
{

}

void Troops::Start()
{
	GameManager::selectSubject
		.Where([this](auto x){
			return find(x.begin(), x.end(), this) == x.end() ? false : true;
		}).Subscribe([this](auto x) {
			GetComponent<RectangleRenderer>()->SetPen(vector4(1, 0, 0, 1));
		});

	GameManager::selectSubject
		.Where([this](auto x) {
			return find(x.begin(), x.end(), this) == x.end() ? true : false;
		}).Subscribe([this](auto x) {
			GetComponent<RectangleRenderer>()->SetPen(vector4(0, 0, 0, 1));
		});

		GameManager::commandSubject
			.Subscribe([this](auto x) {
				Tween::Animate(transform->position,PLAYBACK::ONCE_FORWARD,x.coordinate,EASING::INBACK,2);
			});
}

void Troops::Update()
{

}

void Troops::OnCollisionStay(CollisionResponse)
{
	//GetComponent<RectangleRenderer>()->SetPen(vector4(1, 1, 0, 1));
}

void Troops::OnCollisionExit(CollisionResponse)
{
	
}