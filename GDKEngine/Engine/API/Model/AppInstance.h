#pragma once
#ifndef GDK_APPINSTANCE_H
#define GDK_APPINSTANCE_H

class AppInstance
{
protected:
	AppInstance() 
	{
		currentScene = new Scene();
	}
	~AppInstance() {}
public:
	
	Scene* currentScene;
	static AppInstance* GetSingleton() 
	{
		static AppInstance instance;
		return &instance;
	}
};

#endif // !GDK_APPINSTANCE_H
