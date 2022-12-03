#pragma once
#include "Component.h"
class TestScript : public Component
{
public:
	TestScript();
	TestScript(Transform *);
	~TestScript();
	virtual void Update();
	virtual void OnCollisionEnter();
	virtual void OnCollisionExit();
private:

};

