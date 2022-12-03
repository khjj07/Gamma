#pragma once
#include "Component.h"
class Cam1Script : public Component
{
public:
	Cam1Script();
	Cam1Script(Transform*);
	~Cam1Script();
	virtual void Update();
private:

};

