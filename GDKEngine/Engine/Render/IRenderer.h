#pragma once
#include <Windows.h>

class IRenderer 
{
	virtual void Init(HWND hwnd);
	virtual void SwapBuffers();
	virtual void DrawLine();
	virtual void DrawMesh();
	virtual void DrawString();
	virtual void DrawSurface();
	virtual void DrawImage();
	virtual void Release();
};