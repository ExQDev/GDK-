#pragma once
#ifndef GDK_LIGHT_H
#define GDK_LIGHT_H

class Light : public Component 
{
	enum LightType 
	{
		directional,
		point,
		area,
		spot
	};
public:
	float intensity, brightness;
	Color color;
	LightType lightType = LightType::directional;
};
#endif // !GDK_LIGHT_H
