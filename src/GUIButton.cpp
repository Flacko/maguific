
#include "GUIGlobals.h"

GUI::Button::Button (GBox b, ALLEGRO_FONT* f, ALLEGRO_USTR* l, ALLEGRO_COLOR fC) : _font (NULL), _label (NULL)
{
	box (b);
	font (f);
	label (l);
	fontColor (fC);
}

GUI::Button::~Button()
{
	if (_label) al_ustr_free (_label);
	_font = NULL;
}

void GUI::Button::draw (GBox menupos, Resource& res)
{
	GBox dbox (box() >> menupos);
#define BMP(x) res.getGfx(GUI::GFX_ID::button_##x)
	fillBox (dbox, BMP (bd_t), BMP (bd_r), BMP (bd_b), BMP (bd_l), BMP (cr_tl), BMP (cr_tr), BMP (cr_br), BMP (cr_bl), BMP (bg), 0);
#undef BMP
	if (_label)
	{
		al_draw_ustr (_font, _fontColor, dbox.x + dbox.w / 2, dbox.y + dbox.h / 2 - al_get_font_line_height (_font) / 2, ALLEGRO_ALIGN_CENTRE, _label);
	}
}

GUI::Input* GUI::Button::getInput (GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq)
{
	GBox colbox (box() >> menupos);
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		if (selected)
		{
			selected = false;
			if (colbox.collides (GPoint (ev.mouse.x, ev.mouse.y)))
			{
				return new Input (INPUT_TYPE::MOUSE_RELEASE, this, NULL);
			}
			return new Input (INPUT_TYPE::MOUSE_UP, this, NULL);
		}
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		if (colbox.collides (GPoint (ev.mouse.x, ev.mouse.y)))
		{
			selected = true;
			return new Input (INPUT_TYPE::MOUSE_DOWN, this, NULL);
		}
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		if (colbox.collides (GPoint (ev.mouse.x, ev.mouse.y)))
		{
			if (!hover)
			{
				hover = true;
				return new Input (INPUT_TYPE::MOUSE_HOVER, this, NULL);
			}
		}
		else
		{
			if (hover)
			{
				hover = false;
				return new Input (INPUT_TYPE::MOUSE_LEAVE, this, NULL);
			}
		}
	}
	return NULL;
}
