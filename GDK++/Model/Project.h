#pragma once
#ifndef GDK_PROJECT_H
#define GDK_PROJECT_H
class Project 
{
	
public:
	enum RENDERER 
	{
		DirectX9,
		DirectX11,
		DirectX12,
		OpenGL2,
		OpenGL3,
		OpenGL3_3,
		OpenGL4
	};
	enum PLATFORM 
	{
		WIN,
		MAC,
		LINUX
	};
	std::string name = "New Project";
	RENDERER Renderer = RENDERER::OpenGL3;
	PLATFORM Platform = PLATFORM::WIN;

};
#endif // !GDK_PROJECT_H
