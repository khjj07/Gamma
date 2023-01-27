using namespace GammaEngine;



enum class UnitState
{
	Wait,
	MoveToTarget,
};

class Troops;
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
	void Move(vector2);
public:
	float speed;
	vector2 targetPoint;
	UnitState state= UnitState::Wait;
	Troops* troops;

};



