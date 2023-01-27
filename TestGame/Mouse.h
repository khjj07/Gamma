using namespace GammaEngine;

class Mouse : public GammaEngine::Component
{
public:
	Mouse(GameObject* t);
	~Mouse();
public:
	virtual void Start();
	virtual void Update();
	virtual void OnCollisionEnter(CollisionResponse res);
	virtual void OnCollisionExit(CollisionResponse res);
	bool drag = false;

private:
	vector2 startpoint;
	vector2 endpoint;
	bool cool = true;

};


	
