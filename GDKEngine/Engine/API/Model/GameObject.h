#pragma once
#ifndef GDK_GAMEOBJECT_H
#define GDK_GAMEOBJECT_H
#include "Transform.h"

class GameObject : public Component
{
public:
	Transform transform = { this };
	GameObject* parent;
	ID id;
	std::string name = "GameObject";
	std::string tag = "Untagged";
	boost::container::list<Component*> components;

	GameObject(std::string name) 
	{
		this->name = name;
	}
	~GameObject() {}

	void Init(GameObject* parent) 
	{
		this->parent = parent;
	}
	void FixedUpdate() {}
	void Update() {}
	void Reset() {}
	void Pause() {}
	void Destroy() 
	{
	
	}

private:

};
#endif // !GDK_GAMEOBJECT_H
