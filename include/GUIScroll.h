
#ifndef _GUI_SCROLL_H_
#define _GUI_SCROLL_H_

class DLL_EXPORT Scroll : public Widget
{
	public:
		Scroll (GBox b, int v, int m, int bH, int f);
		~Scroll();

		WIDGET_TYPE::en type() const;

		void value (int v);
		int value() const;

		void max (int m);
		int max() const;

		void buttonHeight (int bh);
		int buttonHeight() const;

		void box (GBox b);
		GBox box() const;

		void increase();
		void decrease();

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
