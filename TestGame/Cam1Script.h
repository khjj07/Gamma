#pragma once
using namespace GammaEngine;
class Cam1Script : public GammaEngine::Component
{
public:
	Cam1Script(GameObject*);
	~Cam1Script();
	virtual void Update();
private:
	float speed = 300;
};

