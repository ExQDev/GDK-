#pragma once
#ifndef GDK_DXMODEL_H
#define GDK_DXMODEL_H

#ifdef USE_DX10
#include <D3D10.h>
#include <D3D10shader.h>
#else
#ifdef USE_DX9
#include <d3d9.h>
#include <d3dx9.h>

const D3DXCOLOR WHITE(D3DCOLOR_XRGB(255, 255, 255));
const D3DXCOLOR BLACK(D3DCOLOR_XRGB(0, 0, 0));
const D3DXCOLOR RED(D3DCOLOR_XRGB(255, 0, 0));
const D3DXCOLOR GREEN(D3DCOLOR_XRGB(0, 255, 0));
const D3DXCOLOR BLUE(D3DCOLOR_XRGB(0, 0, 255));
const D3DXCOLOR YELLOW(D3DCOLOR_XRGB(255, 255, 0));
const D3DXCOLOR CYAN(D3DCOLOR_XRGB(0, 255, 255));
const D3DXCOLOR MAGENTA(D3DCOLOR_XRGB(255, 0, 255));

struct VertexXYZColor
{
	float x, y, z;  // Vertex position.
	D3DCOLOR color;
	static const DWORD VertexFormat = D3DFVF_XYZ | D3DFVF_DIFFUSE; // Flexible vertex format definition for this vertex type
};

typedef struct CVF
{
	D3DVECTOR position;
	D3DVECTOR normal;
	D3DCOLOR  diffuse;
	float     u, v;   // 1st set, 2D
	float     t;      // 2nd set, 1D
} CustomVertexFormat;
#endif // USE_DX9
#endif // USE_DX10



#endif // !GDK_DXMODEL_H
