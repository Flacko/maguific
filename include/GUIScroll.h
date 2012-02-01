
#ifndef _GUI_SCROLL_H_
#define _GUI_SCROLL_H_

class DLL_EXPORT Scroll : public GUI::Widget
{
	public:
		Scroll (GBox, int, int, int, int);
		~Scroll();

		WIDGET_TYPE::en type() const
		{
			return WIDGET_TYPE::SCROLL;
		}
		int value() const
		{
			return (_flip ? _max - _value : _value);
		}
		int max() const
		{
			return _max;
		}
		int buttonHeight() const
		{
			return _buttonHeight;
		}
		GBox box() const
		{
			return _box;
		}

		void value (int v)
		{
			_value = (_flip ? _max - v : v);
		}
		void max (int m)
		{
			_max = m;
		}
		void buttonHeight (int bh)
		{
			_buttonHeight = bh;
			box (_box);
		}

		void box (GBox b);

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
		ALLEGRO_TIMER* _timer;
		Button* _increase;
		Button* _decrease;
		int _max;
		int _value;
		int _buttonHeight;
		bool _rot;
		bool _flip;
};
#endif
