#pragma once
#ifndef GDK_INTERFACE_H
#define GDK_INTERFACE_H
#include <boost/dll.hpp>
using namespace boost;

#include "EditorInstance.h"

#define API extern "C" BOOST_SYMBOL_EXPORT

class GDKModule {
public:
	//Title of the plugin
	char title[256];
	
	//Description of the plugin
	char description[4096];
	
	//Author name
	char author[256];

	//Author or plugin site
	char site[1024];

	//Plugin version
	char version[30];

	//Main process instance. Used by plugin from code.
	AppInstance* instance;

	//Function for run plugin. Runs in the background thread.
	virtual void Run(AppInstance* instance) = 0;

	//Function that calls before plugin unloading. E.g. when app closes.
	virtual void Shutdown() = 0;
};

#endif