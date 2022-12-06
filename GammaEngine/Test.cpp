#include "stdafx.h"
#include "Test.h"
#include "TestScript.h"
Test::Test()
{
	transform->position.x = -500;
	transform->position.y = -500;
	AddComponent<RectangleRenderer>();
	AddComponent<LineRenderer>();
	AddComponent<TestScript>();
	AddComponent<BoxCollider>();
	GetComponent<RectangleRenderer>()->size=vector2(100,100);
	GetComponent<RectangleRenderer>()->order = 10;
	GetComponent<BoxCollider>()->bounds=vector2(100,100);

	/*
	ID2D1GradientStopCollection* pGradientStops = NULL;

	D2D1_GRADIENT_STOP gradientStops[2];
	gradientStops[0].color = ColorF(ColorF::Yellow, 1);
	gradientStops[0].position = 0.0f;
	gradientStops[1].color = ColorF(ColorF::ForestGreen, 1);
	gradientStops[1].position = 1.0f;
	GetComponent<FillEllipseRenderer>()->renderTarget->CreateGradientStopCollection(
		gradientStops,
		2,
		D2D1_GAMMA_2_2,
		D2D1_EXTEND_MODE_CLAMP,
		&pGradientStops
	);
	GetComponent<FillEllipseRenderer>()->SetBrush<ID2D1LinearGradientBrush>(pGradientStops);
	*/
	

}

Test::~Test()
{
}