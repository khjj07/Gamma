#pragma once
using namespace GammaEngine;
class Troops;

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

private:
	static vector<Troops*> hand;
};



