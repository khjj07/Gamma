#include "stdafx.h"
using namespace GammaEngine;

CollisionSpace* GammaEngine::CollisionSpace::root= nullptr;
int GammaEngine::CollisionSpace::maxDepth=10;
float GammaEngine::CollisionSpace::padding=30.0f;

GammaEngine::CollisionSpace::CollisionSpace()
{
	division1 = nullptr;
	division2 = nullptr;
	division3 = nullptr;
	division4 = nullptr;
	areaSize = 0.0f;
	if (root==nullptr)
	{
		root = this;
		root->colliderList = nullptr;
		root->removeBuffer = nullptr;
		root->areaSize = 10000.0f;
		root->center = vector2();
		root->depth = 0;
		root->division1 = new CollisionSpace();
		root->division2 = new CollisionSpace();
		root->division3 = new CollisionSpace();
		root->division4 = new CollisionSpace();

		root->division1->areaSize = areaSize / 2;
		root->division1->center = root->center + vector2(-root->division1->areaSize / 2, root->division1->areaSize / 2);
		root->division1->depth = 1;

		root->division2->areaSize = areaSize / 2;
		root->division2->center = root->center + vector2(root->division2->areaSize / 2, root->division2->areaSize / 2);
		root->division2->depth = 1;

		root->division3->areaSize = areaSize / 2;
		root->division3->center = root->center + vector2(root->division3->areaSize / 2, -root->division3->areaSize / 2);
		root->division3->depth = 1;

		root->division4->areaSize = areaSize / 2;
		root->division4->center = root->center + vector2(-root->division4->areaSize / 2, -root->division4->areaSize / 2);
		root->division4->depth = 1;

		auto temp = CollisionSystem::Instance()->colliderList;
		for (auto iter = temp->begin(); iter < temp->end(); iter++)
		{
			auto transform = (*iter)->transform;
			if (transform->position.x - padding < root->center.x && transform->position.y - padding < root->center.y)
			{
				root->division1->Add((*iter));
			}

			if (transform->position.x + padding > root->center.x && transform->position.y - padding < root->center.y)
			{
				root->division2->Add((*iter));
			}

			if (transform->position.x - padding < root->center.x && transform->position.y + padding > root->center.y)
			{
				root->division3->Add((*iter));
			}

			if (transform->position.x + padding > root->center.x && transform->position.y + padding > root->center.y)
			{
				root->division4->Add((*iter));
			}
		}
	}
	else
	{
		colliderList = nullptr;
		removeBuffer = nullptr;
	}

	
}

GammaEngine::CollisionSpace::~CollisionSpace()
{

}

void GammaEngine::CollisionSpace::Frame()
{
	Debug::DrawRectangle(vector2(areaSize, areaSize),center, 0, new Material());
	if (colliderList && colliderList->size() > 0)
	{
		for (auto iter = colliderList->begin(); iter < colliderList->end(); iter++)
		{
			auto transform = (*iter)->transform;
			if (transform->position.x - padding > root->center.x+areaSize/2 || transform->position.y - padding > root->center.y + areaSize / 2 || transform->position.x + padding < root->center.x - areaSize / 2 ||transform->position.y + padding < root->center.y - areaSize / 2)
			{
				removeBuffer->push_back((*iter));
			}
		}

		if (removeBuffer->size() > 0)
		{
			for (auto iter = removeBuffer->begin(); iter < removeBuffer->end(); iter++)
			{
				Remove(*iter);
				root->Add((*iter));
			}
			removeBuffer->clear();
		}
	
		for (auto iter1 = colliderList->begin(); iter1 < colliderList->end(); iter1++)
		{
			if ((*iter1)->gameObject->isEnabled)
			{
				auto col= *iter1;
				auto v = CollisionSystem::collidedList;
				auto collidedIter = find_if(v->begin(), v->end(), [col](Collided x) {return x.self == col; });
				int index = std::distance(v->begin(), collidedIter);
				for (auto iter2 = colliderList->begin(); iter2 < colliderList->end(); iter2++)
				{
					if ((*iter2)->gameObject->isEnabled && *iter1 != *iter2)
					{
						bool collided = false;
						if (find((*v)[index].list->begin(), (*v)[index].list->end(), (*iter2)) != (*v)[index].list->end())
						{
							collided = true;
						}
						CollisionResponse response = (*iter1)->Collide(*iter2, collided);
						if (response.state == CollisionState::Enter)
						{
							(*iter1)->gameObject->OnCollisionEnter(response);
							(*collidedIter).list->push_back(*iter2);
						}
						else if (response.state == CollisionState::Exit)
						{
							(*iter1)->gameObject->OnCollisionExit(response);
							(*collidedIter).list->erase(remove_if((*collidedIter).list->begin(), (*collidedIter).list->end(), [iter2](Collider* x) { if (x == *iter2) return true; else return false; }), (*collidedIter).list->end());
						}
						else if (response.state == CollisionState::Stay)
						{
							(*iter1)->gameObject->OnCollisionStay(response);
						}
					}

				}	
			}
		}

	}
	else
	{
		if (division1)
		{
			division1->Frame();
		}
		if (division2)
		{
			division2->Frame();
		}
		if (division3)
		{
			division3->Frame();
		}
		if (division4)
		{
			division4->Frame();
		}
	}
	
}
void GammaEngine::CollisionSpace::Remove(Collider* newCollider)
{
	colliderList->erase(remove(colliderList->begin(), colliderList->end(), newCollider), colliderList->end());
}


void GammaEngine::CollisionSpace::Add(Collider* newCollider)
{

	if (depth<maxDepth)
	{
		if (!division1)
		{
			division1 = new CollisionSpace();
			division1->areaSize = areaSize / 2;
			division1->center = center + vector2(-division1->areaSize / 2, division1->areaSize / 2);
			division1->depth = depth + 1;
		}

		if (!division2)
		{
			division2 = new CollisionSpace();
			division2->areaSize = areaSize / 2;
			division2->center = center + vector2(division2->areaSize / 2, division2->areaSize / 2);
			division2->depth = depth + 1;
		}

		if (!division3)
		{
			division3 = new CollisionSpace();
			division3->areaSize = areaSize / 2;
			division3->center = center + vector2(division3->areaSize / 2, -division3->areaSize / 2);
			division3->depth = depth + 1;
		}

		if (!division4)
		{
			division4 = new CollisionSpace();
			division4->areaSize = areaSize / 2;
			division4->center = center + vector2(-division4->areaSize / 2, -division4->areaSize / 2);
			division4->depth = depth + 1;
		}

		auto transform = newCollider->transform;
		if (transform->position.x - padding < center.x && transform->position.y - padding < center.y)
		{
			this->division1->Add(newCollider);
		}

		if (transform->position.x + padding > center.x && transform->position.y - padding < center.y)
		{
			this->division2->Add(newCollider);
		}

		if (transform->position.x - padding < center.x && transform->position.y + padding > center.y)
		{
			this->division3->Add(newCollider);
		}

		if (transform->position.x + padding > center.x && transform->position.y + padding > center.y)
		{
			this->division4->Add(newCollider);
		}
			
	}
	else
	{
		if (!colliderList)
		{
			colliderList = new vector<Collider*>();
			removeBuffer = new vector<Collider*>();
		}
		colliderList->push_back(newCollider);
	}
}