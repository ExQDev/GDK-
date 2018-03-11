#pragma once
#ifndef GDK_GAMEOBJECT_H
#define GDK_GAMEOBJECT_H
#include "Transform.h"
#include "Layers.h"

class GameObject : public Component
{
public:
	Transform transform = { this };
	GameObject* parent;
	ID id;
	std::string name = "GameObject";
	std::string tag = "Untagged";
	int layer = Layer::DEFAULT;

	boost::container::list<Component*> components;
	boost::container::list<GameObject*> children;

	GameObject(std::string name) 
	{
		this->name = name;
		this->gameobject = this;
		this->transform = transform;
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
		for (auto x : children)
		{
			x->Destroy();
		}
		parent->gameobject->children.remove(this);
		delete this;
	}

private:

};
#endif // !GDK_GAMEOBJECT_H
