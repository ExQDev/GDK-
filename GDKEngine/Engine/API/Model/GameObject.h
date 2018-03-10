#pragma once
#ifndef GDK_GAMEOBJECT_H
#define GDK_GAMEOBJECT_H

class GameObject : public Component
{
public:
	Transform transform = { this };
	GameObject* parent;
	ID id;
	GameObject() {}
	~GameObject() {}

	void Init(GameObject* parent) 
	{
		this->parent = parent;
	}

	void Destroy() 
	{
	
	}

private:

};
#endif // !GDK_GAMEOBJECT_H
