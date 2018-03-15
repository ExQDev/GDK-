#pragma once
#ifndef GDK_CAMERA_H
#define GDK_CAMERA_H
#include "../../../Engine/Render/IRenderer.h"
#include <boost\thread.hpp>
#include "GameObject.h"

class Camera : public Component
{
private:
	boost::thread* renderThread;

	
public:
	IRenderer * renderer = nullptr;
	Texture renderTex;
	int r_width = 640, r_height = 480;
	unsigned long int renderLayers;

	Camera()
	{}

	Camera(IRenderer *renderer) 
	{
		this->renderer = renderer;
		this->renderer->transform = transform;
		renderLayers = GDK_LAYER_DEFAULT | GDK_LAYER_SKY | GDK_LAYER_WATER;
#ifdef EDITOR
		renderLayers |= GDK_LAYER_EDITOR;
#endif // EDITOR

	}
	
	Camera(GameObject* parent, IRenderer *renderer) 
	{
		this->renderer = renderer;
		Init(parent);
	}

	void Init(GameObject* parent)
	{
		transform = &parent->transform;
		if(this->renderer)
			this->renderer->transform = transform;
		parent->components.push_back(this);
	}
	void FixedUpdate() {}
	void Update() {}
	void Reset() {}
	void Pause() {}
	void Destroy()
	{

	}
};
#endif // !GDK_CAMERA_H
