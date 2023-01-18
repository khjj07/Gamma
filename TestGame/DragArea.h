using namespace GammaEngine;

class DragArea : public GammaEngine::Component
{
public:
	DragArea(GameObject* t);
	~DragArea();
public:
	virtual void Update();

private:
	vector2 startpoint;
	vector2 endpoint;
	bool drag = false;

};


	
