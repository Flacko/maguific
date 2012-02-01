
#include <cstdio>
#include "GUIGlobals.h"

GUI::Widget::Widget() : _id(-1), selected(false), hover(false)
{
	foreColor = al_map_rgb(0xFF,0xFF,0xFF);
	backColor = al_map_rgb(0xFF,0xFF,0xFF);
}

GUI::WIDGET_TYPE::en GUI::Widget::type() const
{
	return GUI::WIDGET_TYPE::NONE;
}

int GUI::Widget::id() const
{
	return _id;
}

GUI::GBox GUI::Widget::box() const
{
	return _box;
}

void GUI::Widget::id (int i)
{
	_id = i;
}

void GUI::Widget::box (GUI::GBox b)
{
	_box = b;
}

void GUI::Widget::setColors (ALLEGRO_COLOR f, ALLEGRO_COLOR b)
{
	foreColor = f;
	backColor = b;
}

void GUI::Widget::draw (GBox menupos, Resource& res)
{
	GBox b (box() >> menupos);
	al_draw_rectangle (b.x, b.y, b.x + b.w, b.y + b.h, foreColor, 1.0);
}

GUI::Input* GUI::Widget::getInput (GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq)
{
	return NULL;
}

void GUI::Widget::fillBox_bg (ALLEGRO_BITMAP* bm, int _x, int _y, int _w, int _h)
{
	int bmw = al_get_bitmap_width (bm);
	int bmh = al_get_bitmap_height (bm);
	int ofx = bmw - (_x % bmw);
	int ofy = bmw - (_y % bmh);
	al_draw_tinted_bitmap_region (bm, backColor, bmw - ofx, bmh - ofy, (ofx > _w) ? _w : ofx, (ofy > _h) ? _h : ofy, _x, _y, 0);
	for (int y = _y + ofy; y <= _y + _h; y += bmh)
		al_draw_tinted_bitmap_region (bm, backColor, bmw - ofx, 0, (ofx >= _w) ? _w : ofx, (y + bmh > _y + _h) ? (_h - ofy) % bmh : bmh, _x, y, 0);
	for (int x = _x + ofx; x <= _x + _w; x += bmw)
		al_draw_tinted_bitmap_region (bm, backColor, 0, bmh - ofy, (x + bmw > _x + _w) ? (_w - ofx) % bmw : bmw, (ofy > _h) ? _h : ofy, x, _y, 0);
	for (int x = _x + ofx; x <= _x + _w; x += bmw)
		for (int y = _y + ofy; y <= _y + _h; y += bmh)
			al_draw_tinted_bitmap_region (bm, backColor, 0, 0, (x + bmw > _x + _w) ? (_w - ofx) % bmw : bmw, (y + bmh > _y + _h) ? (_h - ofy) % bmh : bmh, x, y, 0);
}

void GUI::Widget::fillBox (GBox box, ALLEGRO_BITMAP* bd_t, ALLEGRO_BITMAP* bd_r, ALLEGRO_BITMAP* bd_b, ALLEGRO_BITMAP* bd_l, ALLEGRO_BITMAP* cr_tl, ALLEGRO_BITMAP* cr_tr, ALLEGRO_BITMAP* cr_br, ALLEGRO_BITMAP* cr_bl, ALLEGRO_BITMAP* bg, int flags)
{
	int (*BW) (ALLEGRO_BITMAP*) = al_get_bitmap_width;
	int (*BH) (ALLEGRO_BITMAP*) = al_get_bitmap_height;
	//rotate 90degrees if the 4th bit is set
	bool rotate = flags & FLAG::FILLBOX_ROTATE;
	int drawflags = 0;
	if (flags & FLAG::FILLBOX_ROTATE) //90 degree rotate
	{
		BW = al_get_bitmap_height;
		BH = al_get_bitmap_width;
		std::swap (bd_t, bd_r);
		std::swap (bd_b, bd_l);
		std::swap (bd_t, bd_b);
		std::swap (cr_tl, cr_tr);
		std::swap (cr_br, cr_bl);
		std::swap (cr_tl, cr_br);
	}
	if (flags & FLAG::FILLBOX_FLIP_H) // h-flip
	{
		drawflags |= rotate ? ALLEGRO_FLIP_VERTICAL : ALLEGRO_FLIP_HORIZONTAL;
		std::swap (bd_l, bd_r);
		std::swap (cr_tl, cr_tr);
		std::swap (cr_bl, cr_br);
	}
	if (flags & FLAG::FILLBOX_FLIP_V) // v-flip
	{
		drawflags |= rotate ? ALLEGRO_FLIP_HORIZONTAL : ALLEGRO_FLIP_VERTICAL;
		std::swap (bd_b, bd_t);
		std::swap (cr_tl, cr_bl);
		std::swap (cr_tr, cr_br);
	}

#define DRAW(bm,color,x,y) al_draw_tinted_rotated_bitmap(bm, color, 0, al_get_bitmap_height(bm)*rotate, x, y, (3.14159268/2)*rotate, drawflags)
	int maxLeftPadding = std::max (std::max (BW (bd_l), BW (cr_tl)), BW (cr_bl));
	int maxRightPadding = std::max (std::max (BW (bd_r), BW (cr_tr)), BW (cr_br));
	int maxTopPadding = std::max (std::max (BH (bd_t), BH (cr_tl)), BH (cr_tr));
	int maxBottomPadding = std::max (std::max (BH (cr_bl), BH (cr_br)), BH (bd_b));

	//draw the background taking care not to draw under borders and corners
	al_hold_bitmap_drawing (true);
	fillBox_bg (bg, box.x + maxLeftPadding, box.y + maxTopPadding, box.w - maxRightPadding - maxLeftPadding, box.h - maxTopPadding - maxBottomPadding);
	fillBox_bg (bg, box.x + BW (bd_l), box.y + BH (cr_tl), maxLeftPadding - BW (bd_l), box.h - BH (cr_tl) - BH (cr_bl));
	fillBox_bg (bg, box.x + box.w - maxRightPadding, box.y + BH (cr_tr), maxRightPadding - BW (bd_r), box.h - BH (cr_tr) - BH (cr_br));
	fillBox_bg (bg, box.x + BW (cr_tl), box.y + BH (bd_t), box.w - BW (cr_tl) - BW (cr_tr), maxTopPadding - BH (bd_t));
	fillBox_bg (bg, box.x + BW (cr_bl), box.y + box.h - maxBottomPadding, box.w - BW (cr_bl) - BW (cr_br), maxBottomPadding - BH (bd_b));
	al_hold_bitmap_drawing (false);

	//draw the left border and fill in the remaining gap with background
	al_hold_bitmap_drawing (true);
	for (int y = box.y + BH (cr_tl); y <= box.y + box.h - BH (cr_bl) - BH (bd_l); y += BH (bd_l))
	{
		DRAW (bd_l, foreColor, box.x, y);
	}
	{
		int remainder = (box.h - BH (cr_bl) - BH (cr_tl)) % BH (bd_l);
		ALLEGRO_BITMAP* sbm = al_create_sub_bitmap (bd_l, 0, 0, rotate ? remainder : BW (bd_l), rotate ? BW (bd_l) : remainder);
		DRAW (sbm, foreColor, box.x, box.y + box.h - BH (cr_bl) - remainder);
		al_destroy_bitmap (sbm);
	}
	al_hold_bitmap_drawing (false);

	//right border
	al_hold_bitmap_drawing (true);
	for (int y = box.y + BH (cr_tr); y <= box.y + box.h - BH (cr_br) - BH (bd_r); y += BH (bd_r))
	{
		DRAW (bd_r, foreColor, box.x + box.w - BW (bd_r), y);
	}
	{
		int remainder = (box.h - BH (cr_br) - BH (cr_tr)) % BH (bd_r);
		ALLEGRO_BITMAP* sbm = al_create_sub_bitmap (bd_r, 0, 0, rotate ? remainder : BW (bd_r), rotate ? BW (bd_r) : remainder);
		DRAW (sbm, foreColor, box.x + box.w - BW (bd_r), box.y + box.h - BH (cr_br) - remainder);
		al_destroy_bitmap (sbm);
	}
	al_hold_bitmap_drawing (false);

	//top border
	al_hold_bitmap_drawing (true);
	for (int x = box.x + BW (cr_tl); x <= box.x + box.w - BW (cr_tr) - BW (bd_t); x += BW (bd_t))
	{
		DRAW (bd_t, foreColor, x, box.y);
	}
	{
		int remainder = (box.w - BW (cr_tl) - BW (cr_tr)) % BW (bd_t);
		ALLEGRO_BITMAP* sbm = al_create_sub_bitmap (bd_t, 0, 0, rotate ? BH (bd_t) : remainder, rotate ? remainder : BH (bd_t));
		DRAW (sbm, foreColor, box.x + box.w - BW (cr_tr) - remainder, box.y);
		al_destroy_bitmap (sbm);
	}
	al_hold_bitmap_drawing (false);

	//bottom border
	al_hold_bitmap_drawing (true);
	for (int x = box.x + BW (cr_bl); x <= box.x + box.w - BW (cr_br) - BW (bd_b); x += BW (bd_b))
	{
		DRAW (bd_b, foreColor, x, box.y + box.h - BH (bd_b));
	}
	{
		int remainder = (box.w - BW (cr_bl) - BW (cr_br)) % BW (bd_b);
		ALLEGRO_BITMAP* sbm = al_create_sub_bitmap (bd_b, 0, 0, rotate ? BH (bd_b) : remainder, rotate ? remainder : BH (bd_b));
		DRAW (sbm, foreColor, box.x + box.w - BW (cr_br) - remainder, box.y + box.h - BH (bd_b));
		al_destroy_bitmap (sbm);
	}
	al_hold_bitmap_drawing (false);

	//corners
	al_hold_bitmap_drawing (true);
	DRAW (cr_tl, foreColor, box.x, box.y);
	DRAW (cr_tr, foreColor, box.x + box.w - BW (cr_tr), box.y);
	DRAW (cr_bl, foreColor, box.x, box.y + box.h - BH (cr_bl));
	DRAW (cr_br, foreColor, box.x + box.w - BW (cr_br), box.y + box.h - BH (cr_br));
	al_hold_bitmap_drawing (false);

	BW = NULL;
	BH = NULL;

#undef DRAW
}
