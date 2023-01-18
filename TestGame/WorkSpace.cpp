#include "WorkSpace.h"
#include "GammaEngine.h"
#include "DragArea.h"

using namespace GammaEngine;
WorkSpace::WorkSpace()
{
	//Create Scene
	Scene* scene1 = new Scene();
	
	//Create and Config GameObjects
	GameObject* dragArea=new GameObject();
	dragArea->AddComponent<RectangleRenderer>();
	dragArea->AddComponent<DragArea>();
	dragArea->GetComponent<RectangleRenderer>()->size = vector2(100, 100);

	GameObject* camera = new GameObject();
	camera->AddComponent<Camera>();
	
	//Hold Object to Scene
	scene1->Hold(dragArea);
	scene1->Hold(camera);

	//AddScene
	SceneManager::AddScene(scene1);
}