#pragma 
class GameObject;
class Component;
class Transform;
class Debug : public GameObject
{
public:
	Debug();
	~Debug();

private:

};

class DebugScript : public Component
{
public:
	DebugScript();
	DebugScript(Transform*);
	~DebugScript();
	virtual void Update();
public:
	string fps;
private:

};