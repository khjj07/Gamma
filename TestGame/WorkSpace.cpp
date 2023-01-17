#include "WorkSpace.h"
#include "GammaEngine.h"

using namespace GammaEngine;
WorkSpace::WorkSpace()
{
	//Create Scene
	Scene* scene1 = new Scene();
	
	//Create and Config GameObjects
	GameObject* box=new GameObject();
	box->AddComponent<RectangleRenderer>();
	box->GetComponent<RectangleRenderer>()->size = vector2(100, 100);

	GameObject* camera = new GameObject();
	camera->AddComponent<Camera>();
	
	//Hold Object to Scene
	scene1->Hold(box);
	scene1->Hold(camera);

	//AddScene
	SceneManager::AddScene(scene1);
}