using namespace GammaEngine;

class Troops;

enum class UnitState
{
	Wait,
	MoveToTarget,
};

class Unit : public GammaEngine::Component
{
public:
	Unit(GameObject* t);
	~Unit();
public:
	virtual void Start();
	virtual void Update();
	virtual void OnCollisionStay(CollisionResponse);
	virtual void OnCollisionExit(CollisionResponse);
public:
	float speed;
	vector2 targetPoint;
	UnitState state= UnitState::Wait;
	Troops* troops;

};



