#include "GammaEngine.h"
#include "GameManager.h"
#include "Unit.h"
using namespace GammaEngine;

vector<Troops*> GameManager::tempSelected;
vector<Troops*> GameManager::selected;
Subject<vector<Troops*> > GameManager::selectSubject;
Subject<Command> GameManager::commandSubject;
GameManager::GameManager(GameObject* t) : Component(t)
{

}

GameManager::~GameManager()
{

}

void GameManager::Update()
{

}

void GameManager::MoveCommand(vector2 point)
{
	commandSubject.OnNext(Command(CommandType::Move,point,selected));
}

void GameManager::ConfirmUnit()
{
	selected = tempSelected;
	selectSubject.OnNext(selected);
}

void GameManager::Hand(Unit* unit)
{
	tempSelected.push_back(unit);

}

void  GameManager::Unhand(Unit* unit)
{
	tempSelected.erase(remove(tempSelected.begin(), tempSelected.end(), unit), tempSelected.end());
}