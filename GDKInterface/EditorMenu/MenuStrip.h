#pragma once
#ifndef GDK_EDITOR_MENU_STRIP_H
#define GDK_EDITOR_MENU_STRIP_H
#include "MenuItem.h"

struct MenuStrip
{
	boost::container::list<MenuItem*> strip;

	bool CheckItem(std::string name) 
	{
		for (auto x : strip) 
		{
			if (x->name == name)
				return true;
		}
		return false;
	}

	void AddItem(std::string name, MenuItem::mi_callback callback)
	{
		if(!CheckItem(name))
			strip.push_back(new MenuItem(name, callback));
	}
};
#endif // !GDK_EDITOR_MENU_STRIP_H
