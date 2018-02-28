#pragma once

class Vector2
{
public:
	double x, y;
};

class Vector3 : public Vector2 
{
public:
	double z;
};

class Vector4 : public Vector3
{
public:
	double w;
};
