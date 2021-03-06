// MonoHostModule.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "../GDKInterface/GDKInteface.h"
//#include <Windows.h>

#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost\filesystem.hpp>
namespace bfs = boost::filesystem;

#include <boost\container\list.hpp>
namespace bc = boost::container;

#include <boost\property_tree\ini_parser.hpp>
#include <boost\property_tree\json_parser.hpp>
#include <boost\property_tree\ptree.hpp>
namespace bpt = boost::property_tree;


#pragma comment(lib, "mono.lib")
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/exception.h>
#include <mono/metadata/mono-debug.h>

MonoDomain* domain;
bc::list<MonoAssembly*> assemblies;
	
void InitModules()
{
	
	mono_set_dirs("lib", "");
	mono_config_parse(NULL);

	domain = mono_jit_init("gdkmonohost");

	if (!domain)
	{
		OutputDebugString(L"Unable to initialize mono jit.\n");
		return;
	}

	for (auto & p : boost::filesystem::directory_iterator(bfs::current_path().concat("/monodlls")))
	{
		if (!bfs::is_directory(p.path()))
		{
			OutputDebugString(p.path().extension().concat("\n").c_str());
			if (p.path().extension() == ".dll")
			{
				auto assembly = mono_domain_assembly_open(domain, bfs::path(p.path()).string().c_str());
				if (!assembly)
				{
					std::wstringstream wss;
					wss << "Couldn`t load the " << bfs::path(p.path()).filename() << " module!\n";
					OutputDebugString(wss.str().c_str());
				}
				else
				{
					//auto asmptr = shared_ptr<MonoAssembly>(assembly);
					assemblies.push_back(assembly);
				}
			}
		}
	}
}

void UnloadModules() {
	mono_jit_cleanup(domain);
	mono_domain_unload(domain);
	/*for (auto i : modules)
	{
	if (i) {
	i.get()->Shutdown();
	}
	}
	modules.clear();*/
}

struct MonoHostModule : public GDKModule 
{
public:

	MonoHostModule() 
	{
		strcpy_s(this->title, "Mono runtime module");
		strcpy_s(this->author, "ExQDev Team");
		strcpy_s(this->version, "1.0.0.0");
		strcpy_s(this->site, "https://exqdev.org");
		strcpy_s(this->description, "Mono runtime module for the GDK++ engine allows to run .net code on the mono backend.");
	}

	void Run(AppInstance* instance) 
	{
		this->instance = instance;
		this->stopped = false;
		//OutputDebugString(bfs::current_path().c_str());
		if (!bfs::exists(bfs::path(bfs::current_path().concat("\\monodlls"))))
		{
			bfs::create_directory(bfs::current_path().concat("\\monodlls"));
			OutputDebugString(L"directory created!\n");
		}
		/*bpt::read_json("monohost.json", pt);
		auto runtimeVer = pt.get<std::string>("runtimeVer");
		if (!runtimeVer.length())
			runtimeVer = "v4.0.30319";*/
		InitModules();
		OutputDebugString(L"Mono runtime module loaded.\n");
	}

	bool HasSettings() { return false; }

	void Settings() 
	{}


	void Shutdown()
	{
		this->stopped = true;
		UnloadModules();
		OutputDebugString(L"Mono runtime module unloaded.\n");
	}
};

API MonoHostModule plugin;
MonoHostModule plugin;