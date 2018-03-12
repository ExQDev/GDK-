#pragma once
#include <string>
#include <sstream>
#include <cmath>
#include <boost\container\list.hpp>
#include <Windows.h>

#include "ID.h"
#include "Vector.h"
#include "Color.h"
#include "Math.h"

#include "Component.h"

#include "Script.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshRenderer.h"




#include "Clock.h"
#include "Time.h"

#include "Transform.h"
#include "GameObject.h"


#include "Scene.h"
#include "Game.h"
#include "Package.h"
#include "Module.h"

#include "AppInstance.h"

// --------------Already defined troouble-----------------
//Vector3 toVector3(Vector2 *pthis)
//{
//	return Vector3(pthis->x, pthis->y, 0);
//}
//
//Vector4 toVector4(Vector2 *pthis)
//{
//	return Vector4(pthis->x, pthis->y, 0, 0);
//}
//
//Vector4 toVector4(Vector3 *pthis)
//{
//	return Vector4(pthis->x, pthis->y, pthis->z, 0);
//}
//
//Color toColor(Vector4 *pthis)
//{
//	return Color(pthis->x, pthis->y, pthis->z, pthis->w);
//}
