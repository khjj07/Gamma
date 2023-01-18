#include "GammaEngine.h"
#include "DragArea.h"

using namespace GammaEngine;

DragArea::DragArea(GameObject* t) : Component(t)
{

}

DragArea::~DragArea()
{

}

 void DragArea::Update()
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
	 }

	 GetComponent<RectangleRenderer>()->size = (endpoint - startpoint);
	 transform->position = (endpoint + startpoint) / 2;
}