
#include <allegro.hpp>
#include <cstdio>
#include "GUIGlobals.h"

GUI::Manager::Manager()
{
}

GUI::Manager::~Manager()
{
	menus.clear();
}

void GUI::Manager::draw()
{
	for(std::vector<GUI::Menu*>::iterator it=menus.begin(); it!=menus.end(); it++)
	{
		(*it)->draw(res);
	}
}
GUI::Input* GUI::Manager::getInput(ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq)
{
	for(std::vector<GUI::Menu*>::iterator it=menus.begin(); it!=menus.end(); it++)
	{
		GUI::Input* in = (*it)->getInput(res,ev,eq);
		if(in)
		{
				return in;
		}
	}
	return NULL;
}

GUI::Menu* GUI::Manager::addMenu(GUI::Menu* men)
{
	men->id(menus.size());
	menus.push_back(men);
	return men;
}
GUI::Menu* GUI::Manager::getMenu(int id)
{
	return menus[id];
}

void GUI::Manager::loadGfxFolder(const char* dir, GFX_ID::en id)
{
	ALLEGRO_PATH* path = al_create_path(dir);
	res.loadGfxFolder(path,id);
	al_destroy_path(path);
}

void GUI::Manager::setGfxIdSize(GFX_ID::en size)
{
	res.setGfxIdSize(size);
}

GUI::Widget* GUI::Manager::getWidget(int mid, int wid)
{
	return getMenu(mid)->getWidget(wid);
}
