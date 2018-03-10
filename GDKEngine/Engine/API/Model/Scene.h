#pragma once
#ifndef GDK_SCENE_H
#define GDK_SCENE_H
#include <boost\container\list.hpp>

class Scene 
{
public:
	boost::container::list<GameObject*> hierarchy;

};

#endif // !GDK_SCENE_H
