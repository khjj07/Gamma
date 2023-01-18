#include "GammaEngine.h"
#include "GameManager.h"
#include "Troops.h"
using namespace GammaEngine;

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

}

void GameManager::Hand(Troops* troops)
{
	hand.push_back(troops);
}

void  GameManager::Unhand(Troops* troops)
{
	hand.erase(remove(hand.begin(), hand.end(), troops), hand.end());
}