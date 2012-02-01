
#include "GUIGlobals.h"

GUI::Scroll::Scroll (GBox b, int v, int m, int f, int bH) : _timer(NULL), _increase(NULL), _decrease(NULL)
{
	_rot = f & FLAG::SCROLL_HORIZONTAL;
	_flip = f & FLAG::SCROLL_FLIP;
	max (m);
	value (v);

	_buttonHeight = bH ;
	_increase = new Button (GBox (), NULL, NULL, al_map_rgb (0, 0, 0));
	_decrease = new Button (GBox (), NULL, NULL, al_map_rgb (0, 0, 0));
	_increase->id (1);
	_decrease->id (2);
	box(b);
}
GUI::Scroll::~Scroll()
{
	delete _decrease;
	delete _increase;
}

void GUI::Scroll::box (GBox b)
{
	_box = b;
	_increase->box (GBox (_box.x, _box.y, _rot ? _buttonHeight : _box.w, _rot ? _box.h : _buttonHeight));
	_decrease->box (GBox (_rot ? _box.x + _box.w - _buttonHeight : _box.x, _rot ? _box.y : _box.y + _box.h - _buttonHeight, _rot ? _buttonHeight : _box.w, _rot ? _box.h : _buttonHeight));
	(_rot ? _box.x : _box.y) += _buttonHeight;
	(_rot ? _box.w : _box.h) -= _buttonHeight * 2;
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
	fillBox (increase, BMP (bd_t), BMP (bd_r), BMP (bd_b), BMP (bd_l), BMP (cr_tl), BMP (cr_tr), BMP (cr_br), BMP (cr_bl), BMP (bg), _rot ? FLAG::FILLBOX_ROTATE | FLAG::FILLBOX_FLIP_H : 0);
	fillBox (decrease, BMP (bd_t), BMP (bd_r), BMP (bd_b), BMP (bd_l), BMP (cr_tl), BMP (cr_tr), BMP (cr_br), BMP (cr_bl), BMP (bg), FLAG::FILLBOX_FLIP_V | (_rot ? FLAG::FILLBOX_ROTATE : 0));
	al_hold_bitmap_drawing (true);
	al_draw_tinted_rotated_bitmap (BMP (fg), foreColor, al_get_bitmap_width (BMP (fg)) / 2, al_get_bitmap_height (BMP (fg)) / 2, increase.x + increase.w / 2, increase.y + increase.h / 2, _rot ? 3.14159268 / 2 : 0, _rot ? ALLEGRO_FLIP_VERTICAL : 0);
	al_draw_tinted_rotated_bitmap (BMP (fg), foreColor, al_get_bitmap_width (BMP (fg)) / 2, al_get_bitmap_height (BMP (fg)) / 2, decrease.x + decrease.w / 2, decrease.y + decrease.h / 2, _rot ? 3.14159268 / 2 : 0, _rot ? 0 : ALLEGRO_FLIP_VERTICAL);
	al_hold_bitmap_drawing (false);
#undef BMP
#define BMP(x) res.getGfx(GFX_ID::scroll_bar_##x)
	fillBox (dbox, BMP (bd_t), BMP (bd_r), BMP (bd_b), BMP (bd_l), BMP (cr_tl), BMP (cr_tr), BMP (cr_br), BMP (cr_bl), BMP (bg), 0);
#undef BMP
#define BMP(x) res.getGfx(GFX_ID::scroll_grip_##x)
	float gripHeight = float (_rot ? dbox.w : dbox.h) / _max;
	float minGripHeight = std::max (BH (BMP (cr_bl)) + BH (BMP (cr_tl)), BH (BMP (cr_tr)) + BH (BMP (cr_br)));
	if (gripHeight < minGripHeight) gripHeight = minGripHeight;
	GBox grip (dbox.x, dbox.y, _rot ? gripHeight : dbox.w, _rot ? dbox.h : gripHeight);
	(_rot ? dbox.w : dbox.h) -= gripHeight;
	(_rot ? grip.x : grip.y) = (_rot ? (dbox.x + dbox.w) : (dbox.y + dbox.h)) - float (_value) / float (_max) * (_rot ? dbox.w : dbox.h);
	fillBox (grip, BMP (bd_t), BMP (bd_r), BMP (bd_b), BMP (bd_l), BMP (cr_tl), BMP (cr_tr), BMP (cr_br), BMP (cr_bl), BMP (bg), 0);
#undef BMP
}

GUI::Input* GUI::Scroll::getInput (GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq)
{
	GBox colbox (_box >> menupos);

	Input* in = _increase->getInput (menupos, res, ev, eq) ? : _decrease->getInput (menupos, res, ev, eq);
	if (in)
	{
		Input* r = new Input (in->type(), this, NULL);
		if (in->type() == INPUT_TYPE::MOUSE_RELEASE || in->type() == INPUT_TYPE::MOUSE_UP)
		{
			if (_timer)
			{
				al_destroy_timer (_timer);
				_timer = NULL;
			}
			selected = false;
		}
		if (in->type() == INPUT_TYPE::MOUSE_DOWN)
		{
			selected = in->widget()->id();
			if (_timer)
			{
				al_destroy_timer (_timer);
				_timer = NULL;
			}
			_timer = al_create_timer (0.3);
			al_register_event_source (eq, al_get_timer_event_source (_timer));
			al_start_timer (_timer);
			if (selected == 1) increase();
			else if (selected == 2) decrease();
		}
		delete in;
		return r;
	}

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
		GPoint mouse (ev.mouse.x, ev.mouse.y);
		if (colbox.collides (mouse))
		{
			selected = 3;
			_value = _max - float (_rot ? (mouse.x - colbox.x) : (mouse.y - colbox.y)) / (_rot ? colbox.w : colbox.h) * _max;
			return new Input (INPUT_TYPE::MOUSE_DOWN, this, NULL);
		}
	}
	else if (ev.type == ALLEGRO_EVENT_TIMER)
	{
		if (ev.timer.source == _timer)
		{
			if (selected == 1) increase();
			else if (selected == 2) decrease();
			return new Input (INPUT_TYPE::MOUSE_HOLD, this, NULL);
		}
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		GPoint mouse(ev.mouse.x, ev.mouse.y);
		if (selected)
		{
			if (selected == 3)
			{
				_value = _max - float (_rot ? (mouse.x - colbox.x) : (mouse.y - colbox.y)) / (_rot ? colbox.w : colbox.h) * _max;
				if(_value > _max) _value = _max;
				else if(_value < 0) _value = 0;
				return new Input (INPUT_TYPE::MOUSE_DRAG, this, NULL);
			}
		}
		else
		{
			if(hover)
			{
				if( !(colbox.collides(mouse) && _increase->box().collides(mouse) && _decrease->box().collides(mouse)) )
				{
					hover = false;
					return new Input(INPUT_TYPE::MOUSE_LEAVE, this, NULL);
				}
			}
			else
			{
				if(colbox.collides(mouse) || _increase->box().collides(mouse) || _decrease->box().collides(mouse))
				{
					hover = true;
					return new Input(INPUT_TYPE::MOUSE_HOVER, this, NULL);
				}
			}
		}
	}
	return NULL;
}
