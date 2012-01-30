
#include <cstdio>
#include "GUIGlobals.h"

GUI::Menu::Menu(GBox _box)
{
	init();
	box(_box);
}
GUI::Menu::~Menu()
{
	widget.clear();
}
GUI::WIDGET_TYPE::en GUI::Menu::type()
{
	return GUI::WIDGET_TYPE::MENU;
}

void GUI::Menu::draw(Resource& res)
{
	#define BMP(x) res.getGfx(GUI::GFX_ID::menu_##x)
	fillBox(box(), BMP(bd_t),BMP(bd_r),BMP(bd_b),BMP(bd_l),BMP(cr_tl),BMP(cr_tr),BMP(cr_br),BMP(cr_bl), BMP(bg),0);
	#undef BMP
	for(std::vector<GUI::Widget*>::iterator it = widget.begin(); it!=widget.end(); it++)
	{
		(*it)->draw(box(),res);
	}
}

GUI::Input* GUI::Menu::getInput(Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq)
{
	for(std::vector<GUI::Widget*>::iterator it = widget.begin(); it!=widget.end(); it++)
	{
		GUI::Input* in = (*it)->getInput(box(),res,ev, eq);
		if(in)
		{
			in->menu(this);
			return in;
		}
	}
	return NULL;
}

GUI::Widget* GUI::Menu::addWidget(GUI::Widget* wdg)
{
	wdg->id(widget.size());
	widget.push_back(wdg);
	return wdg;
}

GUI::Widget* GUI::Menu::getWidget(int id)
{
	return widget[id];
}
