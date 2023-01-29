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

void Mouse::Start()
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

	 if (drag)
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

	 if (alt && Input::GetMouseButtonUp(1))
	 {
		 alt = false;
	 }
	 
	
	 if (Input::GetKey(VK_LMENU) && Input::GetMouseButton(1))
	 {
		 if (alt)
		 {
			 GameManager::SetArrangement(abs(floor((mousePos.x - altpoint.x) / 10)));
		 }
		 else
		 {
			 alt = true;
			 altpoint = mousePos;
		 }
		
	 }
	 else if (!Input::GetKey(VK_LMENU) && Input::GetMouseButtonDown(1))
	 {
		 GameManager::MoveCommand(mousePos);
	 }

	 GetComponent<RectangleRenderer>()->size = (endpoint - startpoint);
	 GetComponent<BoxCollider>()->SetBounds((endpoint - startpoint));
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