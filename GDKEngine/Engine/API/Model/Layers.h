#pragma once
#ifndef GDK_LAYERS_H
#define GDK_LAYERS_H

const unsigned int  	GDK_LAYER_DEFAULT	= 1,
						GDK_LAYER_EDITOR	= 2,
						GDK_LAYER_SKY		= 4,
						GDK_LAYER_WATER		= 8,
						GDK_LAYER_CUSTOM	= 16;

//--------------------------- USAGE -------------------------------
// enum MyLayers
// {
//	  MY_LAYER = GDK_LAYER_CUSTOM << 1,
//	  My_NEXT_LAYER = MY_LAYER << 1,
//	  ...
// }
//-----------------------------------------------------------------

enum Layer 
{
	L_DEFAULT = GDK_LAYER_DEFAULT,
	L_EDITOR = GDK_LAYER_EDITOR,
	L_SKY	= GDK_LAYER_SKY,
	L_WATER = GDK_LAYER_WATER,
	L_CUSTOM = GDK_LAYER_CUSTOM
};
#endif