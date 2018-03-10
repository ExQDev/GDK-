#pragma once
#ifndef GDK_TRANSFORM_H
#define GDK_TRANSFORM_H

class Transform : public Component
{
public:
	Vector3 position;
	Quaternion rotation;
	Vector3 scale;
	GameObject *go;

	Transform(GameObject* parent) 
	{
		Init(parent);
	}

	void Init(GameObject* parent) 
	{
		go = parent;
	}

	void Destroy() 
	{
	
	}

	void Update() 
	{
	
	}

	void FixedUpdate() 
	{
	
	}

	void Pause() 
	{
	
	}

	void Reset() 
	{
		position = Vector3::zero;
		rotation = { 0,0,0,0 };
		scale = Vector3::one;
	}
};

#endif // !GDK_TRANSFORM_H
