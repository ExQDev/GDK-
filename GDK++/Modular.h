#pragma once
#include "../GDKInterface/GDKInteface.h"

#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost\filesystem.hpp>
namespace bfs = boost::filesystem;

#include <boost\container\list.hpp>
namespace bc = boost::container;


#include <boost\dll.hpp>
#include <boost\thread.hpp>

#include <Windows.h>

static bc::list<boost::shared_ptr<GDKModule>> modules;

void InitModules(HINSTANCE hInst);
void UnloadModules();