using namespace GammaEngine;

enum class TroopState
{
	Wait,
	MoveToTarget,
};
class Unit;
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
	void Join(Unit* unit);
	void SetArrangement(int column);
public:
	float speed;
	vector2 targetPoint;
	vector2 velocity;
	TroopState state = TroopState::Wait;
	vector<vector<vector2>*>* arrangement;
	vector<Unit*>* unitList;
	float offset;
};



