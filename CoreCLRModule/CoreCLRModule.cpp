// CoreCLRModule.cpp : Defines the exported functions for the DLL application.
#include "../GDKInterface/GDKInteface.h"
#include <Windows.h>

struct CoreCLRModule : public GDKModule 
{
	CoreCLRModule() 
	{
		strcpy_s(title, "CoreCLR Runtime module");
		strcpy_s(author, "ExQDev Team");
		strcpy_s(description, "Module that allows to load CLR Core .Net assemblies. Now just experimental.");
		strcpy_s(version, "1.0.0.0");
		strcpy_s(site, "https://exqdev.org");
	}

	void Run(HINSTANCE hinst) 
	{
		this->hnst = hinst;
		OutputDebugString(L"CoreCLR Runtime plugin loaded\n");
	}

	void Shutdown()
	{
		OutputDebugString(L"CoreCLR Runtime plugin unloaded\n");
	}
	
};

API CoreCLRModule plugin;
CoreCLRModule plugin;