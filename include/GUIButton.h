
#ifndef _GUI_BUTTON_H_
#define _GUI_BUTTON_H_

class DLL_EXPORT Button : public GUI::Widget
{
	public:
		Button(GBox, ALLEGRO_FONT*, ALLEGRO_USTR*, ALLEGRO_COLOR);
		~Button();
		WIDGET_TYPE::en type(){ return WIDGET_TYPE::BUTTON; }

		void label(ALLEGRO_USTR* l)	{ if(_label) al_ustr_free(_label); _label = l; }
		void font(ALLEGRO_FONT* f) { _font = f; }
		void fontColor(ALLEGRO_COLOR fC) { _fontColor = fC; }

		ALLEGRO_USTR* label() { return _label; }
		ALLEGRO_FONT* font() { return _font; }
		ALLEGRO_COLOR fontColor() { return _fontColor; }


		void draw(GBox, Resource&);
		Input* getInput(GBox, Resource&, ALLEGRO_EVENT&, ALLEGRO_EVENT_QUEUE*);

	private:
		ALLEGRO_FONT* _font;
		ALLEGRO_USTR* _label;
		ALLEGRO_COLOR _fontColor;
};

#endif
