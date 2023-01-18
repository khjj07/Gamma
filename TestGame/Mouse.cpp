#include "GammaEngine.h"
#include "Mouse.h"
#include "GameManager.h"
#include "Troops.h"

using namespace GammaEngine;

Mouse::Mouse(GameObject* t) : Component(t)
{

}

Mouse::~Mouse()
{

}

 void Mouse::Update()
{
	 vector2 mousePos = Camera::main->ScreenToWorldPoint(Input::GetMousePosition());
	 if (Input::GetMouseButtonDown(0))
	 {
		 startpoint = mousePos;
		 drag = true;
	 }

	 if(drag)
	 {
		 endpoint = mousePos;
	 }

	 if (drag && Input::GetMouseButtonUp(0))
	 {
		 drag = false;
		 startpoint = vector2();
		 endpoint = vector2();
		 GameManager::ConfirmUnit();
	 }

	 GetComponent<RectangleRenderer>()->size = (endpoint - startpoint);
	 GetComponent<BoxCollider>()->SetBounds((endpoint - startpoint)/2);
	 transform->position = (endpoint + startpoint) / 2;
}

void Mouse::OnCollisionEnter(CollisionResponse res)
{
// 	if (this->GetComponent<BoxCollider>()->InBound(res.other->transform->position));
		GameManager::Hand(res.other->GetComponent<Troops>());
}

void Mouse::OnCollisionExit(CollisionResponse res)
{
	GameManager::Unhand(res.other->GetComponent<Troops>());
}