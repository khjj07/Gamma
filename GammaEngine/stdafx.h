// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <d3d9.h>
#include <d2d1_1.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vector>
#include  <algorithm>
#include "Type.h"
#include "Util.h"
//base
#include "Singleton.h"
#include "resource.h"
#include "WindowSystem.h"
#include "DirectXModule.h"
#include "Screen.h"
#include "Input.h"
#include "Time.h"
#include "TimerHandler.h"
#include "Timer.h"
#include "Tween.h"

#include "Component.h"
#include "Camera.h"
//render
#include "Renderer.h"
#include "EllipseRenderer.h"
#include "RectangleRenderer.h"
#include "BitmapRenderer.h"
#include "LineRenderer.h"
#include "TextRenderer.h"
//collision
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"
#include "CollisionSystem.h"
#include "Physics.h"


#include "Transform.h"

#include "GameObject.h"
#include "Scene.h"
#include "Engine.h"



using namespace std;
using namespace D2D1;