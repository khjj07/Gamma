#include "GammaEngine.h"
#include "Troops.h"
#include "Unit.h"
#include "GameManager.h"

using namespace GammaEngine;

Troops::Troops(GameObject* t) :
	Component(t),
	speed(200),
	offset(20)
{
	arrangement = new vector<vector<vector2>*>();
	unitList = new vector<Unit*>();
}

Troops::~Troops()
{

}

void Troops::Start()
{

	GameManager::selectSubject
		.Where([this](auto x) {
		return find(x.begin(), x.end(), this) == x.end() ? false : true;
			}).Subscribe([this](auto x) {
				GetComponent<RectangleRenderer>()->SetPen(vector4(1, 0, 0, 1));
				});
	GameManager::selectSubject
			.Where([this](auto x) {
				return find(x.begin(), x.end(), this) == x.end() ? true : false;
			})
			.Subscribe([this](auto x) {
					GetComponent<RectangleRenderer>()->SetPen(vector4(0, 0, 0, 1));
			});

	GameManager::commandSubject
				.Where([this](auto x) {
					return x.type == CommandType::Move && (find(x.troops.begin(), x.troops.end(), this) == x.troops.end() ? false : true);
				})
				.Subscribe([this](auto x) {
						targetPoint = x.coordinate;
						state = TroopState::MoveToTarget;
				});
	GameManager::commandSubject
				.Where([this](auto x) {
					return x.type == CommandType::Arrangement && (find(x.troops.begin(), x.troops.end(), this) == x.troops.end() ? false : true);
				})
				.Subscribe([this](auto x) {
					SetArrangement(x.value);
				});
			

}

void Troops::Update()
{
	if (state == TroopState::MoveToTarget)
	{
		vector2 direction = vector2::Normalize(targetPoint - transform->position);
		float distance = vector2::Distance(targetPoint, transform->position);
		velocity = speed * direction;
		if (vector2::Distance(targetPoint, transform->position) < 20)
		{
			state = TroopState::Wait;
		}
	}
	else
	{
		velocity = vector2();
	}

	transform->position = transform->position + velocity * Time::deltaTime;

	for (int y = 0; y < arrangement->size(); y++)
	{
		for (int x = 0; x < (*arrangement)[y]->size(); x++)
		{
			Debug::DrawRectangle(vector2(10, 10), transform->position + (*(*arrangement)[y])[x], transform->rotation, new Material(vector4(0, 0, 1, 1)));
		}
	}
	vector2 bounds = vector2((*arrangement)[arrangement->size() - 1]->size() * offset, arrangement->size() * offset);
	GetComponent<RectangleRenderer>()->size = bounds;
	GetComponent<BoxCollider>()->SetBounds(bounds);

	int row = 0, column = 0;
	for (int i = 0; i < unitList->size(); i++)
	{
		(*unitList)[i]->Move(transform->position + (*(*arrangement)[column])[row]);
		if ((*arrangement)[column]->size() - 1 <= row)
		{
			column++;
			row = 0;
		}
		else
		{
			row++;
		}
	}
}

void Troops::Join(Unit* unit)
{
	unitList->push_back(unit);
	SetArrangement(floor(sqrt(unitList->size())));
}

void Troops::SetArrangement(int column)
{
	if (column != 0 &&unitList->size() >= column )
	{
		for (auto iter = arrangement->begin(); iter < arrangement->end(); iter++)
		{
			delete (*iter);
		}
		arrangement->clear();
		for (int i = 0; i < column; i++)
		{
			arrangement->push_back(new vector<vector2>(unitList->size() / column));
		}

		for (int i = 1; i < 1 + unitList->size() - column * (unitList->size() / column); i++)
		{
			(*arrangement)[arrangement->size() - i]->push_back(vector2());
		}

		for (int y = 0; y < arrangement->size(); y++)
		{
			for (int x = 0; x < (*arrangement)[y]->size(); x++)
			{
				if (arrangement->size() % 2 == 0)
				{
					if ((*arrangement)[y]->size() % 2 == 0)
					{
						(*(*arrangement)[y])[x] = offset * vector2(x - (int)(*arrangement)[y]->size() / 2 + 0.5f, y - (int)arrangement->size() / 2+0.5f);
					}
					else
					{
						(*(*arrangement)[y])[x] = offset * vector2(x - (int)(*arrangement)[y]->size() / 2, y - (int)arrangement->size() / 2 + 0.5f);
					}
				}
				else
				{
					if ((*arrangement)[y]->size() % 2 == 0)
					{
						(*(*arrangement)[y])[x] = offset * vector2(x - (int)(*arrangement)[y]->size() / 2 + 0.5f, y - (int)arrangement->size() / 2);
					}
					else
					{
						(*(*arrangement)[y])[x] = offset * vector2(x - (int)(*arrangement)[y]->size() / 2, y - (int)arrangement->size() / 2);
					}
				}
				
			}
		}
	}
}


void Troops::OnCollisionStay(CollisionResponse)
{
	//GetComponent<EllipseRenderer>()->SetPen(vector4(1, 1, 0, 1));
}

void Troops::OnCollisionExit(CollisionResponse)
{

}

