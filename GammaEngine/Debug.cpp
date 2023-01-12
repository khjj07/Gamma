#include "stdafx.h"

using namespace GammaEngine;


vector<GammaEngine::DebugRect*> GammaEngine::Debug::rect;
vector<GammaEngine::DebugEllipse*>  GammaEngine::Debug::ellipse;
vector<GammaEngine::DebugLine*> GammaEngine::Debug::line;

GammaEngine::Debug::Debug()
{
;
}

GammaEngine::Debug::~Debug()
{

}

void GammaEngine::Debug::DrawRectangle(vector2 pos, vector2 size, float rotation, Material* material)
{
	DebugRect* debugShape = new DebugRect(pos, size, rotation, material);
	rect.push_back(debugShape);
}

void GammaEngine::Debug::DrawEllipse(vector2 pos, vector2 size, float rotation, Material* material)
{
	DebugEllipse* debugShape = new DebugEllipse(pos, size, rotation, material);
	ellipse.push_back(debugShape);
}

void GammaEngine::Debug::DrawLine(vector2 start, vector2 end, float thickness, Material* material)
{
	DebugLine* debugShape = new DebugLine(start, end, thickness, material);
	line.push_back(debugShape);
}

void GammaEngine::Debug::Render()
{
	
	for (auto iter = rect.begin(); iter != rect.end(); iter++)
	{
		DebugRect* debugShape = *iter;
		GraphicSystem::DrawRectangle(debugShape->size,debugShape->pos, vector2(1,1), debugShape->rotation, debugShape->material);
	}

	for (auto iter = ellipse.begin(); iter != ellipse.end(); iter++)
	{
		DebugEllipse* debugShape = *iter;
		GraphicSystem::DrawEllipse(debugShape->size, debugShape->pos, vector2(1, 1), debugShape->rotation, debugShape->material);
	}

	for (auto iter = line.begin(); iter != line.end(); iter++)
	{
		DebugLine* debugShape = *iter;
		GraphicSystem::DrawLine(debugShape->start, debugShape->end, debugShape->material);
	}
	for (auto iter = rect.begin(); iter != rect.end(); iter++)
	{
		delete* iter;
	}

	for (auto iter = ellipse.begin(); iter != ellipse.end(); iter++)
	{
		delete* iter;
	}

	for (auto iter = line.begin(); iter != line.end(); iter++)
	{
		delete* iter;
	}

	rect.clear();
	ellipse.clear();
	line.clear();

}