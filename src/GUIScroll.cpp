

#include "GUIGlobals.h"

GUI::Scroll::Scroll (GBox b, int v, int m, int bH, int f) : _timer (NULL), _increase (NULL), _decrease (NULL)
{
	_rot = f & FLAG::SCROLL_HORIZONTAL;
	_flip = f & FLAG::SCROLL_FLIP;
	max (m);
	value (v);

	_buttonWidth = bH ;
	_increase = new Button (GBox (), NULL, NULL, al_map_rgb (0, 0, 0));
	_decrease = new Button (GBox (), NULL, NULL, al_map_rgb (0, 0, 0));
	_increase->id (1);
	_decrease->id (2);
	box (b);
}
GUI::Scroll::~Scroll()
{
	delete _increase;
	delete _decrease;
	_increase = NULL;
	_decrease = NULL;
	if (_timer) al_destroy_timer (_timer);
}

GUI::WIDGET_TYPE::en GUI::Scroll::type() const
{
	return WIDGET_TYPE::SCROLL;
}
int GUI::Scroll::value() const
{
	return _value;
}
int GUI::Scroll::max() const
{
	return _max;
}
int GUI::Scroll::buttonWidth() const
{
	return _buttonWidth;
}

GUI::GBox GUI::Scroll::box() const
{
	GBox b = _box;
	(_rot ? b.x : b.y) -= _buttonWidth;
	(_rot ? b.w : b.h) += _buttonWidth * 2;
	return b;
}

void GUI::Scroll::box (GBox b)
{
	_box = b;
	_increase->box (GBox (_box.x, _box.y, _rot ? _buttonWidth : _box.w, _rot ? _box.h : _buttonWidth));
	_decrease->box (GBox (_rot ? _box.x + _box.w - _buttonWidth : _box.x, _rot ? _box.y : _box.y + _box.h - _buttonWidth, _rot ? _buttonWidth : _box.w, _rot ? _box.h : _buttonWidth));
	(_rot ? _box.x : _box.y) += _buttonWidth;
	(_rot ? _box.w : _box.h) -= _buttonWidth * 2;
}

void GUI::Scroll::value (int v)
{
	_value = v;
	if (_value > _max) _value = _max;
	if (_value < 0) _value = 0;
}
void GUI::Scroll::max (int m)
{
	if (m < 0) m = 0;
	_max = m;
	value (_value);
}
void GUI::Scroll::buttonWidth (int bH)
{
	_buttonWidth = bH;
	box (box());
}

void GUI::Scroll::increase()
{
	value (value() + (_flip ? 1 : -1));
}
void GUI::Scroll::decrease()
{
	value (value() + (_flip ? -1 : 1));
}

void GUI::Scroll::draw (GBox menupos, Resource& res)
{
	GBox dbox (_box >> menupos);
	int (*BW) (ALLEGRO_BITMAP*) = al_get_bitmap_width;
	int (*BH) (ALLEGRO_BITMAP*) = al_get_bitmap_height;
	if (_rot) std::swap (BW, BH);

#define BMP(x) res.getGfx(GFX_ID::scroll_button_##x)
	GBox increase (_increase->box() >> menupos);
	GBox decrease (_decrease->box() >> menupos);
	fillBoxShort (increase, _rot ? (FLAG::FILLBOX_ROTATE | FLAG::FILLBOX_FLIP_H) : NULL);
	fillBoxShort (decrease, FLAG::FILLBOX_FLIP_V | (_rot ? FLAG::FILLBOX_ROTATE : 0));
	al_hold_bitmap_drawing (true);
	al_draw_tinted_rotated_bitmap (BMP (fg), foreColor, al_get_bitmap_width (BMP (fg)) / 2, al_get_bitmap_height (BMP (fg)) / 2, increase.x + increase.w / 2, increase.y + increase.h / 2, _rot ? 3.14159268 / 2 : 0, _rot ? ALLEGRO_FLIP_VERTICAL : 0);
	al_draw_tinted_rotated_bitmap (BMP (fg), foreColor, al_get_bitmap_width (BMP (fg)) / 2, al_get_bitmap_height (BMP (fg)) / 2, decrease.x + decrease.w / 2, decrease.y + decrease.h / 2, _rot ? 3.14159268 / 2 : 0, _rot ? 0 : ALLEGRO_FLIP_VERTICAL);
	al_hold_bitmap_drawing (false);
#undef BMP
#define BMP(x) res.getGfx(GFX_ID::scroll_bar_##x)
	fillBoxShort (dbox, NULL);
#undef BMP
#define BMP(x) res.getGfx(GFX_ID::scroll_grip_##x)
	float gripHeight = float (_rot ? dbox.w : dbox.h) / (_max + 1);
	float minGripHeight = std::max (BH (BMP (cr_bl)) + BH (BMP (cr_tl)), BH (BMP (cr_tr)) + BH (BMP (cr_br)));
	if (gripHeight < minGripHeight) gripHeight = minGripHeight;
	GBox grip (dbox.x, dbox.y, (_rot ? gripHeight : dbox.w), (_rot ? dbox.h : gripHeight));
	(_rot ? dbox.w : dbox.h) -= gripHeight;
	float v = _flip ? value() : _max - value();
	(_rot ? grip.x : grip.y) = (_rot ? (dbox.x + dbox.w) : (dbox.y + dbox.h)) - v / float (_max) * (_rot ? dbox.w : dbox.h);
	fillBoxShort (grip, NULL);
#undef BMP
}

GUI::Input* GUI::Scroll::getInput (GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq)
{
	GBox colbox (_box);

	Input* in = _increase->getInput (menupos, res, ev, eq);
	if (!in) in = _decrease->getInput (menupos, res, ev, eq);

	if (in)
	{
		GUI::INPUT_TYPE::en t = in->type();
		int i = in->widget()->id();
		delete in;
		in = NULL;

		if (t == INPUT_TYPE::MOUSE_CLICK or t == INPUT_TYPE::MOUSE_UP)
		{
			if (_timer)
			{
				al_destroy_timer (_timer);
				_timer = NULL;
			}
			clicked = false;
			return new Input (t, this, NULL);
		}
		else if (t == INPUT_TYPE::MOUSE_DOWN)
		{
			clicked = i;
			if (_timer)
			{
				al_destroy_timer (_timer);
				_timer = NULL;
			}
			_timer = al_create_timer (0.3);
			al_register_event_source (eq, al_get_timer_event_source (_timer));
			al_start_timer (_timer);
			if (clicked == 1)
			{
				increase();
			}
			else if (clicked == 2)
			{
				decrease();
			}
			return new Input (t, this, NULL);
		}
	}

	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		if (clicked)
		{
			clicked = false;
			if (colbox.collides (GPoint (ev.mouse.x - menupos.x, ev.mouse.y - menupos.y)))
			{
				return new Input (INPUT_TYPE::MOUSE_CLICK, this, NULL);
			}
			return new Input (INPUT_TYPE::MOUSE_UP, this, NULL);
		}
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		GPoint mouse (ev.mouse.x - menupos.x, ev.mouse.y - menupos.y);
		if (colbox.collides (mouse))
		{
			clicked = 3;
			float nv = float (_rot ? (mouse.x - colbox.x) : (mouse.y - colbox.y)) / float (_rot ? colbox.w : colbox.h) * _max;
			value (_flip ? _max - nv : nv);
			return new Input (INPUT_TYPE::MOUSE_DOWN, this, NULL);
		}
	}
	else if (ev.type == ALLEGRO_EVENT_TIMER)
	{
		if (ev.timer.source == _timer)
		{
			if (clicked == 1) increase();
			else if (clicked == 2) decrease();
			return new Input (INPUT_TYPE::MOUSE_HOLD, this, NULL);
		}
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		GPoint mouse (ev.mouse.x - menupos.x, ev.mouse.y - menupos.y);
		if (clicked)
		{
			if (clicked == 3)
			{
				float nv = float (_rot ? (mouse.x - colbox.x) : (mouse.y - colbox.y)) / float (_rot ? colbox.w : colbox.h) * _max + (_flip ? -0.5 : 0.5);
				value (_flip ? _max - nv : nv);
				return new Input (INPUT_TYPE::MOUSE_DRAG, this, NULL);
			}
		}
		else
		{
			if (hover)
			{
				if (! (colbox.collides (mouse) or _increase->box().collides (mouse) or _decrease->box().collides (mouse)))
				{
					hover = false;
					return new Input (INPUT_TYPE::MOUSE_LEAVE, this, NULL);
				}
			}
			else
			{
				if (colbox.collides (mouse) || _increase->box().collides (mouse) || _decrease->box().collides (mouse))
				{
					hover = true;
					return new Input (INPUT_TYPE::MOUSE_HOVER, this, NULL);
				}
			}
		}
	}
	return NULL;
}
