#pragma once
#include "Component.h"
#include "Type.h"

class BoxScript : public Component
{
public:
	BoxScript(GameObject*);
	~BoxScript();
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

