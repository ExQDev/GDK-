#pragma once
#ifndef GDK_EDITOR_MENU_ITEM_H
#define GDK_EDITOR_MENU_ITEM_H
#include <boost\container\list.hpp>

struct MenuItem
{
	std::string name;
	//boost::function<void> b_callback;
	typedef void (*mi_callback)();
	//std::function<void> callback;
	mi_callback callback;

	MenuItem(std::string name, mi_callback callback) 
	{
		this->name = name;
		this->callback = callback;
	}
};
#endif // !GDK_EDITOR_MENU_ITEM_H
