#include "stdafx.h"

BoxCollider::BoxCollider() :Collider()
{

}
BoxCollider::BoxCollider(Transform* t):Collider(t)
{

}


CollisionResponse BoxCollider::Collide(Collider* other, bool collided)
{
	BoxCollider* boxOther = dynamic_cast<BoxCollider*>(other);
	if (boxOther)
	{
		return Check(boxOther, collided);
	}
}


CollisionResponse BoxCollider::Check(BoxCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = Not;
	rect2D A,B;
	A.min.x = -bounds.x/2 * transform->scale.x + transform->position.x;
	A.min.y = -bounds.y/2 * transform->scale.y + transform->position.y;
	A.max.x = bounds.x/2 * transform->scale.x + transform->position.x;
	A.max.y = bounds.y/2 * transform->scale.y + transform->position.y;
	
	B.min.x = -other->bounds.x/2 * other->transform->scale.x + other->transform->position.x;
	B.min.y = -other->bounds.y/2 * other->transform->scale.y + other->transform->position.y;
	B.max.x = other->bounds.x/2 * other->transform->scale.x + other->transform->position.x;
	B.max.y = other->bounds.y/2 * other->transform->scale.y + other->transform->position.y;

	bool check = AABB_to_AABB(A, B);
	//AABB_to_AABB(shape + transform->position, other->shape + other->transform->position);
	result.other = other;


	if (!collided && check)
	{
		result.state = Enter;
	}
	else if (collided && check)
	{
		result.state = Stay;
	}
	else if (!collided && !check)
	{
		result.state = Not;
	}
	else if (collided && !check)
	{
		result.state = Exit;
	}

	return result;
}