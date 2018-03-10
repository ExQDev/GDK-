#pragma once
#ifndef GDK_COMPONENT_H
#define GDK_COMPONENT_H
class GameObject;
class Transform;
class Script;
class Camera;
class Light;


class Component
{
public:
	bool enabled;
	virtual void Init(GameObject* parent) = 0;
	virtual void Destroy() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Pause() = 0;
	virtual void Reset() = 0;
};
#endif