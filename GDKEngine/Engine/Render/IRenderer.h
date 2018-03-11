#pragma once
#ifndef GDK_IRENDERER_H
#define GDK_IRENDERER_H
#define DEG_TO_RAD 0.01745329251994329576923690768489
#define TWO_PI 6.283185307179586476925286766559
#include "../API/Model/Scene.h"

class IRenderer 
{
public:
	enum RendererType
	{
		OpenGL,
		DirectX
	};

	Scene* currentScene;
	Transform* transform;
	float fov, aspectRatio, Near, Far;

	virtual bool	Init(HINSTANCE hInst, HWND renderWindow, int width, int height, bool bWindowed) = 0;
	virtual bool	Setup() = 0;
	virtual int		Run() = 0;
	virtual void	Render() = 0;
	virtual void	SwapBuffers() = 0;
	virtual void	Release() = 0;
	virtual void	Update(float deltaTime) = 0;
};
#endif // !GDK_IRENDERER_H

