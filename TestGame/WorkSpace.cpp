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

	mouse->GetComponent<BoxCollider>()->isKinematic=true;

	for (int i = 0; i < 400; i++)
	{
		GameObject* troops = new GameObject();
		troops->AddComponent<EllipseRenderer>();
		troops->AddComponent<CircleCollider>();
		troops->AddComponent<Rigidbody>();
		troops->AddComponent<Troops>();
		troops->AddComponent<BitmapRenderer>();
		troops->AddComponent<Animation>();

		troops->GetComponent<Rigidbody>()->useGravity = false;
		troops->GetComponent<EllipseRenderer>()->size = vector2(20, 20);
		troops->GetComponent<CircleCollider>()->radius=10;
		troops->GetComponent<Troops>()->speed = 100;
		troops->transform->position = vector2(30 * (i%10), 30 * (i/10));
		scene1->Hold(troops);
	}
	


	
	
	//Hold Object to Scene
	scene1->Hold(mouse);
	scene1->Hold(camera);
	

	//AddScene
	SceneManager::AddScene(scene1);
}