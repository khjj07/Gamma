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
	GameManager::selectSubject.Where([this](Troops* x) {
		return x==this;
		})
		.Subscribe([this](Troops* x) {
			GetComponent<RectangleRenderer>()->SetPen(vector4(1, 0, 0, 1));
		});
	GameManager::unselectSubject.Subscribe([this](Troops* x) {
		if (this == x)
		{
			GetComponent<RectangleRenderer>()->SetPen(vector4(0, 0, 0, 1));
		}
	});
}

void Troops::Update()
{

}
void Troops::OnCollisionStay(CollisionResponse)
{
	
	
}

void Troops::OnCollisionExit(CollisionResponse)
{
	
}