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

void InitEUI(std::string title, int w, int h);
void EditorWindow(void* loopArg);
void EditorMenu(nk_context *ctx);

void Exit() 
{
	nkc_stop_main_loop(EditorInstance::GetSingleton()->nkc_handle);
}

void About() 
{
	printf("About?:)");
}

void InitEUI(std::string title, int width, int heigth) 
{
	struct nkc nkcx; /* Allocate memory for Nuklear+ handle */
	EditorInstance::GetSingleton()->nkc_handle = &nkcx;
	EditorInstance::GetSingleton()->menuStrip = new MenuStrip();
	EditorInstance::GetSingleton()->menuStrip->AddItem("File/", "Open", Exit);
	EditorInstance::GetSingleton()->menuStrip->AddItem("File/", "Exit", Exit);
	EditorInstance::GetSingleton()->menuStrip->AddItem("Window/", "About", About);
	if (nkc_init(EditorInstance::GetSingleton()->nkc_handle, title.c_str(), width, heigth, NKC_WIN_NORMAL)) {
		printf("Successfull init. Starting 'infinite' main loop...\n");
		nkc_set_main_loop(EditorInstance::GetSingleton()->nkc_handle, EditorWindow, NULL);
	}
	else {
		printf("Can't init NKC\n");
	}
	
}

bool EditorSubMenu(nk_context *ctx, MenuItem* item) 
{
	if(item->subitems.size() > 0)
		for (auto subitem : item->subitems) 
		{
			if (nk_menu_begin_label(ctx, subitem->name.c_str(), NK_TEXT_ALIGN_LEFT, nk_vec2(110, 120)))
			{
				if (item->subitems.size() > 0)
				{
					EditorSubMenu(ctx, subitem);
				}
				else
				{
					subitem->callback();
				}
			}	
		}
	return true;
}

void EditorMenu(nk_context *ctx) 
{
	nk_menubar_begin(ctx);
		/* toolbar */
		//nk_layout_row_dynamic(ctx, 20, 24);
		nk_layout_row_begin(ctx, NK_STATIC, 25, 4);
		for (auto rootElement : EditorInstance::GetSingleton()->menuStrip->strip) 
		{
			printf("\n\n%s\n\n", rootElement->name);
			
			nk_layout_row_push(ctx, 45);
			if (nk_menu_begin_label(ctx, rootElement->name.c_str(), NK_TEXT_LEFT, nk_vec2(120, 200)))
			{
				static size_t prog = 40;
				static int slider = 10;
				static int check = nk_true;
				nk_layout_row_dynamic(ctx, 25, 1);
				//
				{
					EditorSubMenu(ctx, rootElement);
				}
				nk_menu_end(ctx);
			}
			
		}
	nk_menubar_end(ctx);
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

void EditorWindow(void* loopArg) 
{
	struct nk_context *ctx = nkc_get_ctx(EditorInstance::GetSingleton()->nkc_handle);
	union nkc_event e = nkc_poll_events(EditorInstance::GetSingleton()->nkc_handle);
	if ((e.type == NKC_EWINDOW) && (e.window.param == NKC_EQUIT)) {
		nkc_stop_main_loop(EditorInstance::GetSingleton()->nkc_handle);
	}
	if (NKBeginFullScreen()) {
		EditorMenu(ctx);
	}
	nk_end(ctx);
	nkc_render(EditorInstance::GetSingleton()->nkc_handle, nk_rgb(40, 40, 40));
}

#endif