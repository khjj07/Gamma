#pragma once
using namespace GammaEngine;
class Troops;
enum class CommandType
{
	None,
	Move,
	Attack
};
struct Command
{
	Command():
		type(CommandType::None),
		coordinate(vector2()),
		troops(vector<Troops*>()) {}

	Command(CommandType type, vector2 coordinate, vector<Troops*> troops) :
		type(type),
		coordinate(coordinate),
		troops(troops) {}
	vector<Troops*> troops;
	CommandType type;
	vector2 coordinate;
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
	static void Hand(Troops* troops);
	static void Unhand(Troops* troops);
	static void MoveCommand(vector2 point);
private:
	static vector<Troops*> tempSelected;
	static vector<Troops*> selected;
public:
	static Subject<vector<Troops*> > selectSubject;
	static Subject<Command> commandSubject;
};



