#pragma once
using namespace GammaEngine;
class CircleScript : public GammaEngine::Component
{
public:
	CircleScript(GameObject*);
	~CircleScript();
	virtual void Start();
	virtual void Update();
//	virtual void OnCollisionEnter(CollisionResponse);
	virtual void OnCollisionStay(CollisionResponse);
	virtual void OnCollisionExit(CollisionResponse);
public:
	vector2 velocity;
	vector2 gravity = vector2::Down * 3;
	vector2 correction;
private:

};

