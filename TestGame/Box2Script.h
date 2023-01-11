#pragma once
using namespace GammaEngine;
class Box2Script : public GammaEngine::Component
{
public:
	Box2Script(GameObject*);
	~Box2Script();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void OnCollisionStay(CollisionResponse);
	virtual void OnCollisionExit(CollisionResponse);
private:

};

