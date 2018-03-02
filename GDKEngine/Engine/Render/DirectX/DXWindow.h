#pragma once
#ifndef DXWINDOW_H
#define DXWINDOW_H

struct DXWindow
{
public:
	HWND g_MainWindowHandle;

	WNDPROC CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {}
	DXWindow(int X, int Y, int H, int W, HINSTANCE app, HWND parent) 
	{
		g_MainWindowHandle = CreateWindowExW(
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

		if (g_MainWindowHandle == 0)
		{
			MessageBox(0, TEXT("Failed to create render window"), NULL, 0);
			return;
		}

		// And show and update the window we just created
		ShowWindow(g_MainWindowHandle, 1);
		UpdateWindow(g_MainWindowHandle);
	}
};
#endif // !DXWINDOW_H
