#pragma once
#include "Component.h"
class TestScript : public Component
{
public:
	TestScript();
	TestScript(Transform *);
	~TestScript();
	virtual void Start();
	virtual void LateUpdate();
	virtual void OnCollisionEnter(CollisionResponse response);
	virtual void OnCollisionExit(CollisionResponse response);
private:

};

