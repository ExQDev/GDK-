#pragma once
#ifndef GDK_SCENE_H
#define GDK_SCENE_H

class Scene
{
public:
	std::string name = "Default scene";
	boost::container::list<GameObject*> hierarchy;

};

#endif // !GDK_SCENE_H
