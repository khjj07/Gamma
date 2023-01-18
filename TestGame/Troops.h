using namespace GammaEngine;

class Troops : public GammaEngine::Component
{
public:
	Troops(GameObject* t);
	~Troops();
public:
	virtual void Start();
	virtual void Update();
	virtual void OnCollisionStay(CollisionResponse);
	virtual void OnCollisionExit(CollisionResponse);
private:
	

};



