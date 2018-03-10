#pragma once
#ifndef GDK_CAMERA_H
#define GDK_CAMERA_H
#include "../../../Engine/Render/IRenderer.h"
#include <boost\thread.hpp>

class Camera : public Component
{
private:
	boost::thread* renderThread;

	
public:
	IRenderer * renderer;
	Texture renderTex;
	int r_width = 640, r_height = 480;
	Transform* transform;

	Camera()
	{}

	Camera(IRenderer *renderer) 
	{
		this->renderer = renderer;
	}

	void Init()
	{

	}
};
#endif // !GDK_CAMERA_H
