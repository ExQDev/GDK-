#pragma once
#ifndef GDK_MODULAR_H
#define GDK_MODULAR_H
#include "../../GDKInterface/GDKInteface.h"

#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost\filesystem.hpp>
namespace bfs = boost::filesystem;

#include <boost\container\list.hpp>
namespace bc = boost::container;

#include <boost\dll.hpp>
#include <boost\thread.hpp>

#ifdef USE_WINAPI
#include <Windows.h>
#endif // USE_WINAPI


static bc::list<boost::shared_ptr<GDKModule>> modules;

void InitModules(EditorInstance* instance) 
{
	if (!bfs::exists(bfs::path(bfs::current_path().concat("/modules"))))
	{
		bfs::create_directory(bfs::current_path().concat("/modules"));
		OutputDebugStringA("directory created!");
	}

	for (auto & p : boost::filesystem::directory_iterator(bfs::current_path().concat("/modules")))
	{
		if (!bfs::is_directory(p.path()))
		{
			OutputDebugStringA(p.path().extension().concat("\n").generic_string().c_str());
			if (p.path().extension() == ".dll")
			{
				OutputDebugStringA(bfs::path(p.path()).concat("\n").generic_string().c_str());
				boost::shared_ptr<GDKModule> plugin;
				plugin = dll::import<GDKModule>(p.path(), "plugin");
				modules.push_back(plugin);
				boost::thread(boost::bind(&GDKModule::Run, plugin.get(), instance));
			}
		}
	}
}
void UnloadModules() 
{
	for (auto i : modules)
	{
		if (i) {
			i.get()->Shutdown();
		}
	}
	modules.clear();
}
#endif // !GDK_MODULAR_H

