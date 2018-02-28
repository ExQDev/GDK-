#pragma once
#ifndef GDK_INTERFACE_H
#define GDK_INTERFACE_H
#include <boost/dll.hpp>
using namespace boost;

#define API extern "C" BOOST_SYMBOL_EXPORT

class GDKModule {
public:
	char title[256];
	char description[4096];
	char author[256];
	char site[1024];
	char version[30];
	HINSTANCE hnst;

	virtual void Run(HINSTANCE hinst) = 0;
	virtual void Shutdown() = 0;
};

#endif