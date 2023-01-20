#include "GammaEngine.h"
#include "GameManager.h"
#include "Troops.h"
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

void GameManager::Hand(Troops* troops)
{
	tempSelected.push_back(troops);

}

void  GameManager::Unhand(Troops* troops)
{
	tempSelected.erase(remove(tempSelected.begin(), tempSelected.end(), troops), tempSelected.end());
}