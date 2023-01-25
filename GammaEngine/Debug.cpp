#include "stdafx.h"

using namespace GammaEngine;


vector<GammaEngine::DebugRect*>* GammaEngine::Debug::rect;
vector<GammaEngine::DebugEllipse*>* GammaEngine::Debug::ellipse;
vector<GammaEngine::DebugLine*>* GammaEngine::Debug::line;

GammaEngine::Debug::Debug()
{
	rect = new vector<DebugRect*>();
	ellipse = new vector<DebugEllipse*>();
	line = new vector<DebugLine*>();
}

GammaEngine::Debug::~Debug()
{

}

void GammaEngine::Debug::DrawRectangle(vector2 size, vector2 pos, float rotation, Material* material)
{
	DebugRect* debugShape = new DebugRect(size, Camera::main->Projection()*Matrix3x3::Rotate(rotation)* Matrix3x3::Translation(pos.x,pos.y), material);
	rect->push_back(debugShape);
}

void GammaEngine::Debug::DrawEllipse(vector2 size, vector2 pos, float rotation, Material* material)
{
	DebugEllipse* debugShape = new DebugEllipse(size, Matrix3x3::Rotate(rotation) * Matrix3x3::Translation(pos.x, pos.y) * Camera::main->Projection(), material);
	ellipse->push_back(debugShape);
}

void GammaEngine::Debug::DrawLine(vector2 start, vector2 end, Material* material)
{
	DebugLine* debugShape = new DebugLine(start, end, material);
	line->push_back(debugShape);
}

void GammaEngine::Debug::Render()
{
	
	for (auto iter = rect->begin(); iter != rect->end(); iter++)
	{
		DebugRect* debugShape = *iter;
		GraphicSystem::DrawRectangle(debugShape->size,debugShape->matrix, debugShape->material);
	}

	for (auto iter = ellipse->begin(); iter != ellipse->end(); iter++)
	{
		DebugEllipse* debugShape = *iter;
		GraphicSystem::DrawEllipse(debugShape->size, debugShape->matrix, debugShape->material);
	}

	for (auto iter = line->begin(); iter != line->end(); iter++)
	{
		DebugLine* debugShape = *iter;
		GraphicSystem::DrawLine(debugShape->start, debugShape->end, debugShape->material);
	}

	for (auto iter = rect->begin(); iter != rect->end(); iter++)
	{
		delete* iter;
	}

	for (auto iter = ellipse->begin(); iter != ellipse->end(); iter++)
	{
		delete* iter;
	}

	for (auto iter = line->begin(); iter != line->end(); iter++)
	{
		delete* iter;
	}

	rect->clear();
	ellipse->clear();
	line->clear();

}