using namespace GammaEngine;

enum class TroopState
{
	Wait,
	MoveToTarget,
};

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
public:
	float speed;
	vector2 targetPoint;
	TroopState state=TroopState::Wait;

};



