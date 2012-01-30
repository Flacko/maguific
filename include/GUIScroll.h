
#ifndef _GUI_SCROLL_H_
#define _GUI_SCROLL_H_

class DLL_EXPORT Scroll : public GUI::Widget
{
	public:
		Scroll (GBox, int, int, int, int);
		~Scroll();
		int value()
		{
			return (_flip ? _max - _value : _value);
		}
		void value (int v)
		{
			_value = (_flip ? _max - v : v);
		}

		int max()
		{
			return _max;
		}
		void max (int m)
		{
			_max = m;
		}
		int buttonHeight()
		{
			return _buttonHeight;
		}
		void buttonHeight (int bh)
		{
			_buttonHeight = bh;
			box (_box);
		}
		void box (GBox b)
		{
			_box = b;
			_increase->box (GBox (_box.x, _box.y, _rot ? _buttonHeight : _box.w, _rot ? _box.h : _buttonHeight));
			_decrease->box (GBox (_rot ? _box.x + _box.w - _buttonHeight : _box.x, _rot ? _box.y : _box.y + _box.h - _buttonHeight, _rot ? _buttonHeight : _box.w, _rot ? _box.h : _buttonHeight));
			(_rot ? _box.x : _box.y) += _buttonHeight;
			(_rot ? _box.w : _box.h) -= _buttonHeight * 2;
		}
		GBox box()
		{
			return _box;
		}
		void increase()
		{
			_value++;
			if (_value > _max) _value = _max;
		}
		void decrease()
		{
			_value--;
			if (_value < 0) _value = 0;
		}

		void draw (GBox menupos, Resource& res);
		Input* getInput (GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq);

	private:
		Button* _increase;
		Button* _decrease;
		int _max;
		int _value;
		int _buttonHeight;
		bool _rot;
		bool _flip;
		ALLEGRO_TIMER* _timer;
};
#endif
