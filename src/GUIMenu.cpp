
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
	return WIDGET_TYPE::MENU;
}

void GUI::Menu::draw (GBox menupos, Resource& res)
{
#define BMP(x) res.getGfx(GFX_ID::menu_##x)
	fillBox (box(), BMP (bd_t), BMP (bd_r), BMP (bd_b), BMP (bd_l), BMP (cr_tl), BMP (cr_tr), BMP (cr_br), BMP (cr_bl), BMP (bg), 0);
#undef BMP
	for (std::vector<Widget*>::iterator it = _widget.begin(); it != _widget.end(); it++)
	{
		(*it)->draw (box(), res);
	}
}

GUI::Input* GUI::Menu::getInput (GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq)
{
	for (std::vector<Widget*>::iterator it = _widget.begin(); it != _widget.end(); it++)
	{
		GUI::Input* in = (*it)->getInput (box(), res, ev, eq);
		if (in)
		{
			if(in->menu() == NULL)
			{
				in->menu (this);
			}
			return in;
		}
	}
	if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		GPoint mouse(ev.mouse.x-menupos.x, ev.mouse.y-menupos.y);
		bool collides = _box.collides(mouse);
		if(hover)
		{
			if(!collides)
			{
				hover = false;
				return new Input(INPUT_TYPE::MOUSE_LEAVE, this, NULL);
			}
		}
		else if(!hover)
		{
			if(collides)
			{
				hover = true;
				return new Input(INPUT_TYPE::MOUSE_HOVER, this, NULL);
			}
		}
	}
	else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		GPoint mouse(ev.mouse.x-menupos.x, ev.mouse.y-menupos.y);

		if(_box.collides(mouse) and !selected)
		{
			selected = true;
			return new Input(INPUT_TYPE::MOUSE_DOWN, this, NULL);
		}
	}
	else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		GPoint mouse(ev.mouse.x-menupos.x, ev.mouse.y-menupos.y);
		bool collides = _box.collides(mouse);
		if(selected)
		{
			selected = false;

			if(collides)
				return new Input(INPUT_TYPE::MOUSE_RELEASE, this, NULL);

			else if(!collides)
				return new Input(INPUT_TYPE::MOUSE_UP, this, NULL);
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
