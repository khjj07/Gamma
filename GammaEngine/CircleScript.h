#pragma once
#include "Component.h"
struct vector2;

class CircleScript : public Component
{
public:
	CircleScript();
	CircleScript(GameObject*);
	~CircleScript();
	virtual void Start();
	virtual void Update();
	virtual void OnCollisionEnter(CollisionResponse);
	virtual void OnCollisionStay(CollisionResponse);
	virtual void OnCollisionExit(CollisionResponse);
public:
	vector2 velocity;
	vector2 gravity = vector2::Down * 10;
	vector2 correction;
private:

};

