#pragma once
using namespace GammaEngine;
enum CreateMode
{
	box,
	circle
};

class CursorSript : public GammaEngine::Component
{
public:
	CursorSript(GameObject*);
	~CursorSript();
	virtual void Start();
	virtual void Update();
private:
	CreateMode mode= CreateMode::box;
};

