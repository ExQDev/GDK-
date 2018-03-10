#pragma once
#ifndef GDK_RENDER_WINDOW_H
#define GDK_RENDER_WINDOW_H
#include "IRenderer.h"
#include "DirectX\DirectXRenderer.h"
#include "OpenGL\OpenGLRenderer.h"
#include <boost\thread.hpp>

struct RenderWindow
{
public:
	HWND renderWindowHandle;
	IRenderer* renderer;
	boost::thread *run;

	RenderWindow(IRenderer::RendererType renderertype, int X, int Y, int H, int W, HINSTANCE app, HWND parent)
	{
		renderWindowHandle = CreateWindowExW(
			WS_EX_OVERLAPPEDWINDOW,     // DWORD dwExStyle
			TEXT("GDKRenderWindow"),	// LPCWSTR lpClassName
			TEXT("GDK++ Render"),		// LPCWSTR lpWindowName
			WS_OVERLAPPEDWINDOW,        // DWORD dwStyle
			X,				            // int X
			Y,							// int Y
			W, H,
			parent,                     // HWND hWndParent
			NULL,                       // HMENU hMenu
			app,						// HINSTANCE hInstance
			NULL                        // LPVOID lpParam
		);

		if (renderWindowHandle == 0)
		{
			MessageBox(0, TEXT("Failed to create render window"), NULL, 0);
			return;
		}
		switch (renderertype)
		{
		case IRenderer::OpenGL:
			renderer = new OpenGLRenderer();
			break;
		case IRenderer::DirectX:
			renderer = new DirectXRenderer();
			break;
		default:
			MessageBox(renderWindowHandle, L"Renderer type not specified!", L"GDK++ Render", 0);
			return;
			break;
		}
		if (!renderer->Init(app, renderWindowHandle, W, H, true)) 
		{
			MessageBox(renderWindowHandle, L"Failed to init DX Renderer!", L"GDK++ Render", 0);
		}
		run = new boost::thread(boost::bind(&IRenderer::Run, renderer));
		// And show and update the window we just created
		ShowWindow(renderWindowHandle, 1);
		UpdateWindow(renderWindowHandle);
	}
};
#endif