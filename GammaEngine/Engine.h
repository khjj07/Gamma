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
extern bool CompareTag(GameObject* gameObject, string tag);//태그가 일치하면 true 반환
extern bool CompareTag(GameObject* gameObject, char* tag);//태그가 일치하면 true 반환
extern bool CompareTags(GameObject* gameObject, vector<string> tags);//태그가 하나라도 일치하면 true 반환
extern bool CompareTags(GameObject* gameObject, vector<char*> tags);//태그가 하나라도 일치하면 true 반환