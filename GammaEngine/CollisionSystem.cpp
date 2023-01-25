#include "stdafx.h"
using namespace GammaEngine;

vector<Collided>* GammaEngine::CollisionSystem::collidedList;

GammaEngine::CollisionSystem::CollisionSystem()
{
	collidedList = new vector<Collided>();
	colliderList = new vector<Collider*>();
}

GammaEngine::CollisionSystem::~CollisionSystem()
{

}

void GammaEngine::CollisionSystem::Initialize()
{
	CollisionSpace* collisionSpace = new CollisionSpace();
}

void GammaEngine::CollisionSystem::Frame()
{
	CollisionSpace* current = CollisionSpace::root;
	current->Frame();
}