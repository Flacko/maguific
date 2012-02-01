
#include "GUIGlobals.h"

GUI::Menu::Menu (GBox _box)
{
	box (_box);
}
GUI::Menu::~Menu()
{
	_widget.clear();
}
GUI::WIDGET_TYPE::en GUI::Menu::type() const
{
	return GUI::WIDGET_TYPE::MENU;
}

void GUI::Menu::draw (GBox menupos, Resource& res)
{
#define BMP(x) res.getGfx(GUI::GFX_ID::menu_##x)
	fillBox (box(), BMP (bd_t), BMP (bd_r), BMP (bd_b), BMP (bd_l), BMP (cr_tl), BMP (cr_tr), BMP (cr_br), BMP (cr_bl), BMP (bg), 0);
#undef BMP
	for (std::vector<GUI::Widget*>::iterator it = _widget.begin(); it != _widget.end(); it++)
	{
		(*it)->draw (box(), res);
	}
}

GUI::Input* GUI::Menu::getInput (GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq)
{
	for (std::vector<GUI::Widget*>::iterator it = _widget.begin(); it != _widget.end(); it++)
	{
		GUI::Input* in = (*it)->getInput (box(), res, ev, eq);
		if (in)
		{
			in->menu (this);
			return in;
		}
	}
	return NULL;
}

GUI::Widget* GUI::Menu::widget (GUI::Widget* w)
{
	w->id (_widget.size());
	_widget.push_back (w);
	return w;
}

GUI::Widget* GUI::Menu::widget (int id) const
{
	if (id < 0)
	{
		id = _widget.size() - id;
	}
	if (id >= int (_widget.size()))
	{
		id = id % _widget.size();
	}
	return _widget[id];
}
