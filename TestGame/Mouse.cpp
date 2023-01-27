#include "GammaEngine.h"
#include "Mouse.h"
#include "GameManager.h"
#include "Unit.h"

using namespace GammaEngine;

Mouse::Mouse(GameObject* t) : Component(t)
{

}

Mouse::~Mouse()
{

}

void Mouse::Start()
{
	
}

void Mouse::Update()
{
	 vector2 mousePos = Camera::main->ScreenToWorldPoint(Input::GetMousePosition());

	 if (Input::GetMouseButtonDown(1))
	 {
		 GameManager::MoveCommand(mousePos);
	 }

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
		 GameManager::ConfirmUnit();
		 drag = false;
		 startpoint = vector2();
		 endpoint = vector2();
	 }
	 if (Input::mouseScrollDelta > 0)
	 {
		 Camera::main->orthoScale -=0.1f;
	 }
	 if (Input::mouseScrollDelta < 0)
	 {
		 Camera::main->orthoScale += 0.1f;
	 }

	 GetComponent<RectangleRenderer>()->size = (endpoint - startpoint);
	 GetComponent<BoxCollider>()->SetBounds((endpoint - startpoint));
	 transform->position = (endpoint + startpoint) / 2;
}

void Mouse::OnCollisionEnter(CollisionResponse res)
{
// 	if (this->GetComponent<BoxCollider>()->InBound(res.other->transform->position));
		GameManager::Hand(res.other->GetComponent<Unit>());
}

void Mouse::OnCollisionExit(CollisionResponse res)
{
	GameManager::Unhand(res.other->GetComponent<Unit>());
}