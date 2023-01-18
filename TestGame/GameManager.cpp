#include "GammaEngine.h"
#include "GameManager.h"
#include "Troops.h"
using namespace GammaEngine;

vector<Troops*> GameManager::tempSelected;
vector<Troops*> GameManager::selected;
Subject<Troops*> GameManager::selectSubject;
 Subject<Troops*> GameManager::unselectSubject;
GameManager::GameManager(GameObject* t) : Component(t)
{

}

GameManager::~GameManager()
{

}

void GameManager::Update()
{

}

void GameManager::ConfirmUnit()
{
	selected = tempSelected;
}

void GameManager::Hand(Troops* troops)
{
	selectSubject.OnNext(troops);
	tempSelected.push_back(troops);
}

void  GameManager::Unhand(Troops* troops)
{
	tempSelected.erase(remove(tempSelected.begin(), tempSelected.end(), troops), tempSelected.end());
}