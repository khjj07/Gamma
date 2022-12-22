#include "stdafx.h"
using namespace GammaEngine;

GammaEngine::CollisionSystem::CollisionSystem()
{
}

GammaEngine::CollisionSystem::~CollisionSystem()
{
}

void GammaEngine::CollisionSystem::Frame()
{
	vector<Collider*>::iterator iter1,iter2;
	vector<Collided>::iterator collidedIter;

	collidedIter= collidedList.begin();
	for (iter1 = colliderList.begin(); iter1 < colliderList.end(); iter1++)
	{
		if ((*iter1)->gameObject->isEnabled)
		{
			for (iter2 = colliderList.begin(); iter2 < colliderList.end(); iter2++)
			{
				if ((*iter2)->gameObject->isEnabled && *iter1 != *iter2)
				{
					bool collided=false;
					if (find((*collidedIter).list.begin(), (*collidedIter).list.end(), (*iter2)) != (*collidedIter).list.end())
					{
						collided = true;
					}
					CollisionResponse response = (*iter1)->Collide(*iter2, collided);
					if (response.state == CollisionState::Enter)
					{
						(*iter1)->gameObject->OnCollisionEnter(response);
						(*collidedIter).list.push_back(*iter2);
					}
					else if (response.state == CollisionState::Exit)
					{
						(*iter1)->gameObject->OnCollisionExit(response);
						(*collidedIter).list.erase(remove_if((*collidedIter).list.begin(), (*collidedIter).list.end(), [iter2](Collider* x) { if (x == *iter2) return true; else return false; }), (*collidedIter).list.end());
					}
					else if (response.state == CollisionState::Stay)
					{
						(*iter1)->gameObject->OnCollisionStay(response);
					}
				}

			}
			collidedIter++;
		}
		
	}
}