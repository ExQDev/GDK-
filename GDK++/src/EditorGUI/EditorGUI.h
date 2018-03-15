#pragma once
#ifndef GDK_EDITOR_UI_H
#define GDK_EDITOR_UI_H
#define NKC_IMPLEMENTATION
//#include <GDKEngine/Dependencies/nuklear_cross/nuklear.h>
#include "GDKEngine\Dependencies\nuklear_cross/nuklear_cross.h"
#include <GDKInterface/EditorInstance.h>
#include <GDKInterface/EditorMenu/MenuStrip.h>
#include <GDKEngine\Dependencies\nuklear_cross\stb_image.h>
#include <GDKEngine\Dependencies\lodepng\lodepng.h>
#include "../Modular.h"

static bool renderWindow = true, hierarchyWindow = true, pluginMGR;

void InitEUI(std::string title, int w, int h);
void EditorWindow(void* loopArg);
void EditorMenu(nk_context *ctx);

void Exit() 
{
	nkc_stop_main_loop(EditorInstance::GetSingleton()->nkc_handle);
}

void About() 
{
	printf("About?:)\n");
}

void TogglePluginMGR() 
{
	pluginMGR = true;
	nk_window_show(nkc_get_ctx(EditorInstance::GetSingleton()->nkc_handle), "Plugins", nk_show_states::NK_SHOWN);
}

void ToggleRenderWindow() 
{
	renderWindow = true;
	nk_window_show(nkc_get_ctx(EditorInstance::GetSingleton()->nkc_handle), "Render", nk_show_states::NK_SHOWN);
}

void ToggleHierarchyWindow() 
{
	hierarchyWindow = true;
	nk_window_show(nkc_get_ctx(EditorInstance::GetSingleton()->nkc_handle), "Hierarchy", nk_show_states::NK_SHOWN);
}

void InitMenu() 
{
	EditorInstance::GetSingleton()->menuStrip = new MenuStrip();
	EditorInstance::GetSingleton()->menuStrip->AddItem("File/", "Open", 0);
	//EditorInstance::GetSingleton()->menuStrip->AddItem("File/Open/", "Project", 0);
	EditorInstance::GetSingleton()->menuStrip->AddItem("File/", "Exit", Exit);
	
	EditorInstance::GetSingleton()->menuStrip->AddItem("", "Edit", 0);
	EditorInstance::GetSingleton()->menuStrip->AddItem("", "Assets", 0);
	//EditorInstance::GetSingleton()->menuStrip->AddItem("", "", Exit);

	EditorInstance::GetSingleton()->menuStrip->AddItem("Window/", "Plugin manager", TogglePluginMGR);
	EditorInstance::GetSingleton()->menuStrip->AddItem("Window/", "------------------", 0);
	EditorInstance::GetSingleton()->menuStrip->AddItem("Window/", "Render window", ToggleRenderWindow);
	EditorInstance::GetSingleton()->menuStrip->AddItem("Window/", "Hierarchy window", ToggleHierarchyWindow);
	EditorInstance::GetSingleton()->menuStrip->AddItem("Window/", "------------------", 0);
	EditorInstance::GetSingleton()->menuStrip->AddItem("Window/", "About", About);
}

void InitEUI(std::string title, int width, int heigth) 
{
	struct nkc nkcx; /* Allocate memory for Nuklear+ handle */
	EditorInstance::GetSingleton()->nkc_handle = &nkcx;
	InitMenu();
	if (nkc_init(EditorInstance::GetSingleton()->nkc_handle, title.c_str(), width, heigth, NKC_WIN_NORMAL)) {
		printf("Successfull init. Starting 'infinite' main loop...\n");
		nkc_set_main_loop(EditorInstance::GetSingleton()->nkc_handle, EditorWindow, NULL);
	}
	else {
		printf("Can't init NKC\n");
	}
	
}

void SubSubMenu(nk_context *ctx, MenuItem* item) 
{
	struct nk_rect bounds;
	
	
	nk_layout_row_static(ctx, 30, 150, 1);
	bounds = nk_widget_bounds(ctx);
	if (nk_contextual_begin(ctx, 0, nk_vec2(100, 300), bounds)) {
		//static size_t prog = 40;
		//static int slider = 10;

		
		/*for (auto itm : item->subitems)
		{
			if (nk_contextual_item_label(ctx, "", NK_TEXT_CENTERED))
		}*/
		
		if (item->subitems.size() > 0) {
			for (auto subitem : item->subitems)
			{
				if (subitem->subitems.size() > 0)
				{
					if (nk_contextual_item_label(ctx, ("[+] " + subitem->name).c_str(), NK_TEXT_ALIGN_LEFT))
					{
						SubSubMenu(ctx, subitem);
						nk_menu_end(ctx);
					}
				}
				else
				{
					if (nk_contextual_item_label(ctx, subitem->name.c_str(), NK_TEXT_LEFT))
						if (subitem->callback)
							subitem->callback();
				}
			}
		}
		
		nk_contextual_end(ctx);
	}
}

bool EditorSubMenu(nk_context *ctx, MenuItem* item)
{
	
	nk_layout_row_push(ctx, 45);
	if (nk_menu_begin_label(ctx, item->name.c_str(), NK_TEXT_LEFT, nk_vec2(120, 200)))
	{
		nk_layout_row_dynamic(ctx, 25, 1);

		if (item->subitems.size() > 0) {
			for (auto subitem : item->subitems)
			{
				if (subitem->subitems.size() > 0)
				{
					if (nk_menu_item_label(ctx, ("[+] " + subitem->name).c_str(), NK_TEXT_LEFT))
					{
						EditorSubMenu(ctx, subitem);
					}
				}
				else
				{
					if (nk_menu_item_label(ctx, subitem->name.c_str(), NK_TEXT_LEFT))
						if (subitem->callback)
							subitem->callback();
				}
			}
		}

		nk_menu_end(ctx);
	}
	return true;
}


void EditorMenu(nk_context *ctx) 
{
	nk_menubar_begin(ctx);
	nk_layout_row_begin(ctx, NK_STATIC, 25, 12);
	for (auto rootElement : EditorInstance::GetSingleton()->menuStrip->strip) 
	{
		EditorSubMenu(ctx, rootElement);			
	}	
	nk_menubar_end(ctx);
}

void PluginMGRWindow(nk_context* ctx) 
{
	if (nk_begin(ctx, "Plugins", nk_rect(850, 40, 320, 350), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_CLOSABLE))
	{
		static shared_ptr<GDKModule> selectedPlugin = nullptr;
		nk_layout_row_begin(ctx, NK_STATIC, 350, 2);
		nk_layout_row_push(ctx, 130);
		if (nk_group_begin(ctx, "PluginsList", 0)) {
			
			nk_layout_row_static(ctx, 18, 100, 1);
			for (shared_ptr<GDKModule> mod : modules) {
				if(mod)
					if (nk_select_label(ctx, mod.get()->title, NK_TEXT_LEFT, selectedPlugin == mod))
						selectedPlugin = mod;
			}
		} nk_group_end(ctx);
		nk_layout_row_push(ctx, 150);
		if (nk_group_begin(ctx, "PluginDetailes", 0)) {
			if (selectedPlugin) 
			{
				nk_layout_row_dynamic(ctx, 20, 1);
				nk_label(ctx, selectedPlugin->title, NK_TEXT_LEFT);
				
				nk_layout_row_dynamic(ctx, 18, 1);
				nk_label(ctx, selectedPlugin->author, NK_TEXT_LEFT);
				
				nk_layout_row_dynamic(ctx, 18, 1);
				nk_label(ctx, selectedPlugin->version, NK_TEXT_LEFT);
				
				nk_layout_row_dynamic(ctx, 18, 1);
				nk_label(ctx, selectedPlugin->site, NK_TEXT_LEFT);

				
				nk_layout_row_dynamic(ctx, 150, 1);
				nk_label_wrap(ctx, selectedPlugin->description);

				
				nk_layout_row_dynamic(ctx, 25, 2);
				if(selectedPlugin.get()->HasSettings())
				if (nk_button_label(ctx, "Settings"))
				{
					printf("Opening settings... [%s]\n", selectedPlugin.get()->title);
					selectedPlugin->Settings();
				}
				if (!selectedPlugin.get()->stopped)
				{
					if (nk_button_label(ctx, "Shutdown"))
					{
						printf("Shutting down... [%s]\n", selectedPlugin.get()->title);
						selectedPlugin->Shutdown();
					}
				}
				else
				{
					if (nk_button_label(ctx, "Run"))
					{
						printf("Starting... [%s]\n", selectedPlugin.get()->title);
						selectedPlugin->Run(EditorInstance::GetSingleton());
					}
				}
				


			}
		} nk_group_end(ctx);
	}
	
	nk_end(ctx);
}

void HierarchyWindow(nk_context* ctx) 
{
	if (nk_begin(ctx, "Hierarchy", nk_rect(0, 40, 250, 350), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_CLOSABLE))
	{
		nk_layout_row_static(ctx, 200, 200, 1);
		if (nk_group_begin(ctx, "HierarchyList", 0)) {
			
			nk_layout_row_static(ctx, 18, 100, 1);
			for (auto go : EditorInstance::GetSingleton()->currentScene->hierarchy) {
				if (nk_select_label(ctx, go->name.c_str(), NK_TEXT_CENTERED, EditorInstance::GetSingleton()->selectedInHieararchy == go))
					EditorInstance::GetSingleton()->selectedInHieararchy = go;
			}
		} nk_group_end(ctx);
	}
	
	nk_end(ctx);
}

void RenderWindow(nk_context* ctx) 
{
	if (nk_begin(ctx, "Render", nk_rect(250, 40, 600, 350), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_CLOSABLE) != NK_WINDOW_CLOSED) 
	{
		
	}
	nk_end(ctx);

}

bool NKBeginFullScreen()
{
	auto myapp = EditorInstance::GetSingleton();
	struct nk_context *ctx = nkc_get_ctx(myapp->nkc_handle);
	int x, y;
	nkc_get_desktop_size(myapp->nkc_handle, &x, &y);
	RECT rect;
	if (GetWindowRect(myapp->nkc_handle->window, &rect))
	{
		x = rect.right - rect.left;
		y = rect.bottom - rect.top;
	}
	//printf("%i, %i", x, y);
	//ctx->end->bounds.h;
	return nk_begin(ctx, " ", nk_rect(0, 0, x, y), NK_WINDOW_DYNAMIC | NK_WINDOW_SCROLL_AUTO_HIDE);
}

bool NKBeginWideScreen()
{
	auto myapp = EditorInstance::GetSingleton();
	struct nk_context *ctx = nkc_get_ctx(myapp->nkc_handle);
	int x, y;
	nkc_get_desktop_size(myapp->nkc_handle, &x, &y);
	RECT rect;
	if (GetWindowRect(myapp->nkc_handle->window, &rect))
	{
		x = rect.right - rect.left;
		y = rect.bottom - rect.top;
	}
	//printf("%i, %i", x, y);
	//ctx->end->bounds.h;
	return nk_begin(ctx, " ", nk_rect(0, 0, x, 40), NK_WINDOW_DYNAMIC | NK_WINDOW_SCROLL_AUTO_HIDE);
}

void EditorWindow(void* loopArg) 
{
	struct nk_context *ctx = nkc_get_ctx(EditorInstance::GetSingleton()->nkc_handle);
	union nkc_event e = nkc_poll_events(EditorInstance::GetSingleton()->nkc_handle);
	if ((e.type == NKC_EWINDOW) && (e.window.param == NKC_EQUIT)) {
		nkc_stop_main_loop(EditorInstance::GetSingleton()->nkc_handle);
	}
	if (NKBeginWideScreen()) {
		EditorMenu(ctx);
		nk_end(ctx);
	}
	
	if (renderWindow)
		RenderWindow(ctx);


	if (hierarchyWindow)
		HierarchyWindow(ctx);

	if (pluginMGR)
		PluginMGRWindow(ctx);

	nkc_render(EditorInstance::GetSingleton()->nkc_handle, nk_rgb(40, 40, 40));
}

#endif