#pragma once
#include <Windows.h>

class IRenderer 
{
	enum RendererType
	{
		OpenGL,
		DirectX
	};
	virtual void Init(HWND hwnd) = 0;
	virtual void SwapBuffers() = 0;
	virtual void DrawLine() = 0;
	virtual void DrawMesh() = 0;
	virtual void DrawString() = 0;
	virtual void DrawSurface() = 0;
	virtual void DrawImage() = 0;
	virtual void Release() = 0;
};