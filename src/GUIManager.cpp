
#include "GUIGlobals.h"

GUI::Manager::Manager()
{
}

GUI::Manager::~Manager()
{
	for (std::vector<Widget*>::iterator it = _widget.begin(); it != _widget.end(); it++)
	{
		GUI::Widget* w = (GUI::Widget*) (*it);
		delete (w);
		w = NULL;
	}
	_widget.clear();
}

void GUI::Manager::draw()
{
	for (std::vector<Widget*>::iterator it = _widget.begin(); it != _widget.end(); it++)
	{
		(*it)->draw (GBox(), res);
	}
}

GUI::Input* GUI::Manager::getInput (ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq)
{
	for (std::vector<Widget*>::iterator it = _widget.begin(); it != _widget.end(); it++)
	{
		Input* in = (*it)->getInput (GBox(), res, ev, eq);
		if (in)
		{
			if (in->valid())
			{
				return in;
			}
			else
			{
				delete in;
				in = NULL;
			}
		}
	}
	return NULL;
}

GUI::Widget* GUI::Manager::widget (int id) const
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

GUI::Widget* GUI::Manager::widget (GUI::Widget* w)
{
	w->id (_widget.size());
	_widget.push_back (w);
	return w;
}

void GUI::Manager::loadGfxFolder (const char* dir, GFX_ID::en id)
{
	ALLEGRO_PATH* path = al_create_path (dir);
	res.loadGfxFolder (path, id);
	al_destroy_path (path);
}

void GUI::Manager::gfxIdSize (GFX_ID::en size)
{
	res.setGfxIdSize (size);
}
