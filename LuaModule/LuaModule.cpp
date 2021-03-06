// LuaModule.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "../GDKInterface/GDKInteface.h"
#include "Info.h"
#include <string>
#include <sstream>

//API GDKModule* LuaModule;

struct LuaModule : public GDKModule {
	LuaModule() {
		strcpy_s(this->title, TITLE);
		strcpy_s(this->author, AUTHOR);
		strcpy_s(this->description, DESC);
		strcpy_s(this->version, VER);
		strcpy_s(this->site, SITE);
		OutputDebugString(L"Initialization of lua module\n");
	}

	void Run(AppInstance* instance) {
		OutputDebugString(L"Lua module loaded\n");
		stopped = false;
		std::wstringstream ss;
		ss << title << " by " << author << " ver " << version << "\nWas Loaded.";
		//MessageBox(NULL, ss.str().c_str(), L"GDK++", MB_OK);
	}

	bool HasSettings() 
	{
		return false;
	}

	void Settings() {}

	void Shutdown() {
		this->stopped = true;
		OutputDebugString(L"Lua module shutting down\n");
	}
};

//extern "C" BOOST_SYMBOL_EXPORT
API LuaModule plugin;
LuaModule plugin;