#pragma once

/// <summary>
/// 게임 엔진 class
/// </summary>
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
	vector<GameObject*> addBuffer;//오브젝트 생성을 위한 버퍼
	vector<GameObject*> removeBuffer;//제거될 오브젝트를 담은 버퍼
	vector<GameObject*>::iterator gameObjectIter;
};

extern void Instantiate(GameObject* obj);//현재 씬에 새로운 오브젝트를 생성하는 함수
extern void Destroy(GameObject* obj);//현재 씬에 있는 오브젝트를 제거하는 함수
