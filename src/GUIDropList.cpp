
#include "GUIGlobals.h"

GUI::DropList::DropList (GBox b, ALLEGRO_FONT* f, ALLEGRO_USTR* l, ALLEGRO_COLOR fC, Scroll* sC, int sO) : _font (NULL), _label (NULL), _scroll (NULL)
{
	box (b);
	selection (-1);
	label (l);
	font (f);
	fontColor (fC);
	shownOptions (sO);
	scroll (sC);
	_expand = false;
}

GUI::DropList::~DropList()
{
	delete _scroll;
	_scroll = NULL;
	_font = NULL;
	if (_label) al_destroy_ustr (_label);
	_label = NULL;
	for (std::vector<ALLEGRO_USTR*>::iterator it = _options.begin(); it != _options.end(); it++)
	{
		al_destroy_ustr (*it);
		(*it) = NULL;
	}
}

GUI::WIDGET_TYPE::en GUI::DropList::type()
{
	return WIDGET_TYPE::DROPLIST;
}

void GUI::DropList::fontColor (ALLEGRO_COLOR fC)
{
	_fontColor = fC;
}

ALLEGRO_COLOR GUI::DropList::fontColor() const
{
	return _fontColor;
}

void GUI::DropList::font (ALLEGRO_FONT* f)
{
	_font = f;
}

ALLEGRO_FONT* GUI::DropList::font() const
{
	return _font;
}

void GUI::DropList::selection (int s)
{
	_selection = s;
	if (_options.size() == 0)
		_selection = -1;
	else if (_selection >= (int) _options.size())
		_selection = _options.size() - 1;
	recalculateScrollMax();
}

int GUI::DropList::selection() const
{
	return _selection;
}

void GUI::DropList::label (ALLEGRO_USTR* l)
{
	al_destroy_ustr (_label);
	_label = l;
}

ALLEGRO_USTR* GUI::DropList::label() const
{
	return _label;
}

void GUI::DropList::scroll (Scroll* sc)
{
	if (_scroll) delete _scroll;
	_scroll = sc;
	GBox tmp = _scroll->box();
	_scroll->box (GBox (_box.w - tmp.w, _box.h, tmp.w, tmp.h));
	_scroll->value (0);
	recalculateScrollMax();
}

GUI::Scroll* GUI::DropList::scroll() const
{
	return _scroll;
}

void GUI::DropList::shownOptions (int sO)
{
	_shownOptions = sO;
}

int GUI::DropList::shownOptions() const
{
	return _shownOptions;
}


ALLEGRO_USTR* GUI::DropList::getOption (int i) const
{
	return _options[i];
}
void GUI::DropList::addOption (ALLEGRO_USTR* o)
{
	_options.push_back (o);
	recalculateScrollMax();
}
void GUI::DropList::removeOption (int i)
{
	_options.erase (_options.begin() + i);
	recalculateScrollMax();
}

void GUI::DropList::recalculateScrollMax()
{
	if (_scroll)
	{
		int newmax = _options.size() - _shownOptions;
		int val = _scroll->value();
		if (_selection > -1) newmax--;
		_scroll->max (newmax);
		_scroll->value (val);
	}
}

void GUI::DropList::draw (GBox menupos, Resource& res)
{
#define BW al_get_bitmap_width
#define BH al_get_bitmap_height

	GBox dbox (_box >> menupos);

#define BMP(x) res.getGfx(GFX_ID::droplist_##x)
	fillBoxShort (dbox, NULL);
	al_draw_tinted_bitmap (BMP (fg), foreColor, dbox.x + dbox.w - BW (BMP (fg)), dbox.y + dbox.h / 2 - BH (BMP (fg)) / 2, 0);

	ALLEGRO_USTR* todraw = _label;
	if (_selection > -1 and _selection < (int) _options.size()) todraw = _options[_selection];
	if (todraw)
	{
		al_draw_ustr (_font, _fontColor, dbox.x + BW (BMP (bd_l)), dbox.y + dbox.h / 2 - al_get_font_line_height (_font) / 2, ALLEGRO_ALIGN_LEFT, todraw);
	}
	todraw = NULL;
#undef BMP
#define BMP(x) res.getGfx(GFX_ID::droplist_option_##x)
	if (_expand)
	{
		int offset = _scroll->value();
		if (offset > _selection and _selection > -1) offset++;
		GBox bop = GBox (dbox.x, dbox.y + dbox.h, (dbox.w) - (_scroll->box().w), _scroll->box().h / _shownOptions);
		int shown = 1;
		for (int i = offset; i < (int) _options.size(); i++)
		{
			if (shown > _shownOptions) break;
			if (i == _selection) continue;
			fillBoxShort (bop, NULL);
			al_draw_ustr (_font, _fontColor, bop.x + BW (BMP (bd_l)), bop.y + bop.h / 2 - al_get_font_line_height (_font) / 2, ALLEGRO_ALIGN_LEFT, _options[i]);
			bop.y += bop.h;
			shown ++;
		}
		if ( (int) _options.size() > _shownOptions) _scroll->draw (dbox, res);
	}
#undef BMP

#undef BH
#undef BW
}

GUI::Input* GUI::DropList::getInput (GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq)
{
	GBox colbox (_box >> menupos);
	if (_expand)
	{
		if ( (int) _options.size() > _shownOptions)
		{
			Input* in = _scroll->getInput (colbox, res, ev, eq);
			if (in)
			{
				in->widget (this);
				return in;
			}
		}
	}
	if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		GPoint mouse = GPoint (ev.mouse.x, ev.mouse.y);
		if (colbox.collides (mouse))
		{
			hover = true;
			return new GUI::Input (INPUT_TYPE::MOUSE_HOVER, this, NULL);
		}
		else
		{
			if (hover)
			{
				hover = false;
				return new GUI::Input (INPUT_TYPE::MOUSE_LEAVE, this, NULL);
			}
		}
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		GPoint mouse = GPoint (ev.mouse.x, ev.mouse.y);
		if (colbox.collides (mouse))
		{
			clicked = 1;
		}
		if (_expand)
		{
			GBox sb = _scroll->box();
			GBox bop = GBox (colbox.x, colbox.y + colbox.h, (colbox.w) - (sb.w), sb.h / _shownOptions);
			if (mouse.y > colbox.y + colbox.h and mouse.y < colbox.y + colbox.h + sb.h)
			{
				int offset = _scroll->value();
				if (offset > _selection and _selection > -1) offset++;
				int op = (mouse.y - colbox.y - colbox.h) / bop.h;
				if (_selection > -1 and _selection <= offset + op) op++;
				clicked = offset + op + 2;
			}
		}
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		GPoint mouse = GPoint (ev.mouse.x, ev.mouse.y);
		if (clicked == 1)
		{
			if (colbox.collides (mouse))
			{
				_expand = !_expand;
				clicked = 0;
				return new GUI::Input (INPUT_TYPE::MOUSE_CLICK, this, NULL);
			}
		}
		else if (clicked >= 2)
		{
			GBox bop = GBox (colbox.x, colbox.y + colbox.h, (colbox.w) - (_scroll->box().w), _scroll->box().h / _shownOptions);
			int offset = _scroll->value();
			int mult = clicked - offset - 2;
			if (_selection > -1 and _selection < clicked - 2) mult--;
			bop.y += bop.h * mult;
			if (bop.collides (mouse))
			{
				selection (clicked - 2);
				clicked = 0;
				_expand = !_expand;
				recalculateScrollMax();
				return new GUI::Input (INPUT_TYPE::MOUSE_CLICK, this, NULL);
			}
			return new GUI::Input (INPUT_TYPE::MOUSE_UP, this, NULL);
		}
		clicked = 0;
	}
	return NULL;
}
