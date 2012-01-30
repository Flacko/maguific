
#include "GUIGlobals.h"

GUI::CheckBox::CheckBox(GBox b, bool v)
{
	init();
	box(b);
	value(v);
}
void GUI::CheckBox::draw(GBox menupos, Resource& res)
{
	GBox dbox(box() >> menupos);
	#define BMP(x) res.getGfx(GFX_ID::checkbox_##x)
	al_draw_tinted_bitmap(BMP(bg),backColor, dbox.x, dbox.y, 0);
	if(value())
	{
		al_draw_tinted_bitmap(BMP(fg),foreColor,
			dbox.x+al_get_bitmap_width(BMP(bg))/2-al_get_bitmap_width(BMP(fg))/2,
			dbox.y+al_get_bitmap_height(BMP(bg))/2-al_get_bitmap_height(BMP(fg))/2, 0);
	}
	#undef BMP
}

GUI::Input* GUI::CheckBox::getInput(GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq)
{
	GBox colbox(box() >> menupos);
	if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		if(selected)
		{
			selected = false;
			if(colbox.collides(GPoint(ev.mouse.x, ev.mouse.y)))
			{
				value(!value());
				return new Input(INPUT_TYPE::MOUSE_RELEASE, this, NULL);
			}
			return new Input(INPUT_TYPE::MOUSE_UP, this, NULL);
		}
	}
	else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		if(colbox.collides(GPoint(ev.mouse.x, ev.mouse.y)))
		{
			selected = true;
			return new Input(INPUT_TYPE::MOUSE_DOWN, this, NULL);
		}
	}
	else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		if(colbox.collides(GPoint(ev.mouse.x,ev.mouse.y)))
		{
			if(!hover)
			{
				hover = true;
				return new Input(INPUT_TYPE::MOUSE_HOVER, this, NULL);
			}
		}
		else
		{
			if(hover)
			{
				hover = false;
				return new Input(INPUT_TYPE::MOUSE_LEAVE, this, NULL);
			}
		}
	}
	return 0;
}