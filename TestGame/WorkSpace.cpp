#include "WorkSpace.h"
#include "GammaEngine.h"
#include "Mouse.h"
#include "Unit.h"

using namespace GammaEngine;
WorkSpace::WorkSpace()
{
	//Create Scene
	Scene* scene1 = new Scene();

	//Camera
	GameObject* camera = new GameObject();
	camera->AddComponent<Camera>();

	//Create and Config GameObjects
	GameObject* mouse =new GameObject();
	mouse->AddComponent<RectangleRenderer>();
	mouse->AddComponent<BoxCollider>();
	mouse->AddComponent<Mouse>();
	mouse->GetComponent<BoxCollider>()->isKinematic=true;
	for (int k = 0; k < 1; k++)
	{
		GameObject* troops = new GameObject();
		troops->AddComponent<RectangleRenderer>();
		troops->AddComponent<Troops>();

		for (int i = 0; i < 10; i++)
		{
			GameObject* unit = new GameObject();
			unit->AddComponent<EllipseRenderer>();
			unit->AddComponent<CircleCollider>();
			unit->AddComponent<Rigidbody>();
			unit->AddComponent<Unit>();
			unit->AddComponent<BitmapRenderer>();
			unit->AddComponent<Animator>();
			troops->GetComponent<Troops>()->Join(unit->GetComponent<Unit>());
			unit->GetComponent<BitmapRenderer>()->offset = vector2(3, -3);
			unit->GetComponent<Rigidbody>()->useGravity = false;
			unit->GetComponent<EllipseRenderer>()->size = vector2(15, 15);
			unit->GetComponent<CircleCollider>()->radius = 7.5f;
			unit->GetComponent<Unit>()->speed = 50;
			unit->transform->position = vector2((float)(100 + 30 * (i % 10)), (float)(100 + 30 * (i / 10)));
			scene1->Hold(unit);
		}
	}
	
	
	//GameObject* stone = new GameObject();
	//stone->AddComponent<RectangleRenderer>();
	//stone->AddComponent<BoxCollider>();
	//stone->GetComponent<BoxCollider>()->SetBounds(vector2(200,200));
	//stone->GetComponent<RectangleRenderer>()->size=vector2(200,200);
	//stone->transform->position = vector2(400, 0);
	
	
	//Hold Object to Scene
	scene1->Hold(mouse);
	scene1->Hold(camera);
	

	//AddScene
	SceneManager::AddScene(scene1);
}