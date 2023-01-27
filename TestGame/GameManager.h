#pragma once
using namespace GammaEngine;
class Unit;
class Troops;
enum class CommandType
{
	None,
	Move,
	Attack,
	Arrangement
};
struct Command
{
	Command():
		type(CommandType::None),
		coordinate(vector2()),
		troops(vector<Troops*>()),
		value(0) {}


	Command(CommandType type, vector2 coordinate, vector<Troops*> troops) :
		type(type),
		coordinate(coordinate),
		troops(troops) {}

	Command(CommandType type, int value, vector<Troops*> troops) :
		type(type),
		value(value),
		troops(troops) {}

	vector<Troops*> troops;
	CommandType type;
	vector2 coordinate;
	int value;
};


class GameManager : public GammaEngine::Component, Singleton<GameManager>
{
public:
	GameManager(GameObject* t);
	~GameManager();
public:
	virtual void Update();
	
public:
	static void ConfirmUnit();
	static void Hand(Troops* unit);
	static void Unhand(Troops* unit);
	static void MoveCommand(vector2 point);
	static void SetArrangement(int);

private:
	static vector<Troops*> tempSelected;
	static vector<Troops*> selected;

public:
	static Subject<vector<Troops*> > selectSubject;
	static Subject<Command> commandSubject;
};



