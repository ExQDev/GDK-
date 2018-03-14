#pragma once
#ifndef GDK_EDITOR_INSTANCE_H
#define GDK_EDITOR_INSTANCE_H
#include "../GDKEngine/Engine/API/Model/Include.h"
#include "../GDKEngine/Dependencies/nuklear_cross/nuklear_cross.h"
#include "EditorMenu\MenuStrip.h"

class EditorInstance : public AppInstance
{
protected:
	EditorInstance() {}
	~EditorInstance() {}
public:
	struct nkc* nkc_handle;
	MenuStrip* menuStrip;
	GameObject* selectedInHieararchy;

	static EditorInstance* GetSingleton() 
	{
		static EditorInstance instance;
		return &instance;
	}
};

#endif // !GDK_EDITOR_INSTANCE_H
