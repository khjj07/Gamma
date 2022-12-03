#pragma once
#include <vector>
using namespace std;
class GameObject;
class Scene;
class Engine : public Singleton<Engine>
{
public:
	Engine();
	~Engine();
public:
	void Initialize(Scene*);
	bool Frame();
public:
	Scene* currentScene;
	Scene* nextScene;
	vector<GameObject*> addBuffer;
	vector<GameObject*> removeBuffer;
	vector<GameObject*>::iterator gameObjectIter;
};

extern void Instantiate(GameObject* obj);


extern void Destroy(GameObject* obj);
