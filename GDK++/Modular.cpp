#include "Modular.h"

void InitModules(HINSTANCE hInst)
{
	if (!bfs::exists(bfs::path(bfs::current_path().concat("/modules"))))
	{
		bfs::create_directory(bfs::current_path().concat("/modules"));
		OutputDebugString(L"directory created!");
	}

	for (auto & p : boost::filesystem::directory_iterator(bfs::current_path().concat("/modules")))
	{
		if (!bfs::is_directory(p.path()))
		{
			OutputDebugString(p.path().extension().concat("\n").c_str());
			if (p.path().extension() == ".dll")
			{
				OutputDebugString(bfs::path(p.path()).concat("\n").c_str());
				boost::shared_ptr<GDKModule> plugin;
				plugin = dll::import<GDKModule>(p.path(), "plugin");
				modules.push_back(plugin);
				boost::thread(boost::bind(&GDKModule::Run, plugin.get(), hInst));
			}
		}
	}
}

void UnloadModules() {
	for (auto i : modules)
	{
		if (i) {
			i.get()->Shutdown();
		}
	}
	modules.clear();
}