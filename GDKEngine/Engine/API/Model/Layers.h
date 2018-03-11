#pragma once
#ifndef GDK_LAYERS_H
#define GDK_LAYERS_H

const unsigned long int	GDK_LAYER_DEFAULT	= 1,
						GDK_LAYER_EDITOR	= 2,
						GDK_LAYER_SKY		= 4,
						GDK_LAYER_WATER		= 8,
						GDK_LAYER_CUSTOM	= 16;

//--------------------------- USAGE -------------------------------
// enum MyLayers
// {
//	  MY_LAYER = GDK_LAYER_CUSTOM << 1;
// }
//-----------------------------------------------------------------

enum Layer 
{
	DEFAULT = GDK_LAYER_DEFAULT,
	EDITOR = GDK_LAYER_EDITOR,
	SKY	= GDK_LAYER_SKY,
	WATER = GDK_LAYER_WATER,
	CUSTOM = GDK_LAYER_CUSTOM,
	CUSTOM1 = CUSTOM << 1
};
#endif