#include "WorkSpace.h"
#include "GammaEngine.h"
#include "Mouse.h"
#include "Troops.h"

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

	for (int i = 0; i < 10; i++)
	{
		GameObject* troops = new GameObject();
		troops->AddComponent<RectangleRenderer>();
		troops->AddComponent<BoxCollider>();
		troops->AddComponent<Troops>();
		
		troops->GetComponent<RectangleRenderer>()->size = vector2(20, 20);
		troops->GetComponent<BoxCollider>()->SetBounds(vector2(20, 20));
		troops->transform->position = vector2(30 * i, 10);
		scene1->Hold(troops);
	}
	


	
	
	//Hold Object to Scene
	scene1->Hold(mouse);
	scene1->Hold(camera);
	

	//AddScene
	SceneManager::AddScene(scene1);
}