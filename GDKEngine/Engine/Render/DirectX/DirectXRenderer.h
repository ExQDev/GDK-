#pragma once
#ifndef GDK_DXRENDERER_H
#define GDK_DXRENDERER_H
#include "../IRenderer.h"
#include <d3d9.h>
#include <d3dx9.h>

class DirectXRenderer : public IRenderer 
{
	IDirect3D9* _d3d9;
	IDirect3DDevice9* Device = 0;

	DirectXRenderer()
	{
		
	}

	bool Display(float timeDelta) {
		if (Device) {
			Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
				0x00000000, 1.0f, 0);
			// Swap the back and front buffers. 
			Device->Present(0, 0, 0, 0);
		}
		return     true;
	}
};
#endif // !GDK_DXRENDERER_H

