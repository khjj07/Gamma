#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <functional>
#include <algorithm>
#include "Type.h"
#include "Util.h"
#include "Render.h"
//base
#include "Singleton.h"
#include "resource.h"
#include "WindowSystem.h"
#include "GraphicSystem.h"
#include "Screen.h"
#include "Input.h"
#include "EngineTime.h"
#include "TimerHandler.h"
#include "Timer.h"
#include "Tween.h"

//component
#include "Component.h"
#include "Transform.h"
#include "Camera.h"

//render
#include "Renderer.h"
#include "EllipseRenderer.h"
#include "RectangleRenderer.h"
#include "PolygonRenderer.h"
#include "BitmapRenderer.h"
#include "LineRenderer.h"
#include "TextRenderer.h"
#include "Animation.h"
#include "Animator.h"

//collision
#include "Collider.h"
#include "BoxCollider.h"
#include "LineCollider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"
#include "CollisionSystem.h"
#include "CollisionSpace.h"
#include "Rigidbody.h"

//Entity
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Engine.h"


//GRX
#include "Subject.h"
#include "ReactiveProperty.h"

//spine
#include "SpineModel.h"
#include "GammaTextureLoader.h"

#include "Debug.h"
