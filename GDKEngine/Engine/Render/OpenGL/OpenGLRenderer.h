#pragma once
#include "../IRenderer.h"

class OpenGLRenderer : public IRenderer 
{
public:
	//IRenderer implementation for OpenGL
	OpenGLRenderer() 
	{
	
	}
	bool Setup() { return true; }
	int Run() { return -1; }
	void Render() {}
	bool Init(HINSTANCE hInst, HWND renderWindow, int width, int height, bool bWindowed) 
	{
		return false;
	}
	void SwapBuffers() {};
	void Release() {}
	void Update(float deltaTime) 
	{
	
	}
};