
#ifndef _GUI_BUTTON_H_
#define _GUI_BUTTON_H_

class DLL_EXPORT Button : public Widget
{
	public:
		Button (GBox b, ALLEGRO_FONT* f, ALLEGRO_USTR* l, ALLEGRO_COLOR fC);
		~Button();

		WIDGET_TYPE::en type() const;

		void label (ALLEGRO_USTR* l);
		void font (ALLEGRO_FONT* f);
		void fontColor (ALLEGRO_COLOR fC);

		ALLEGRO_USTR* label() const;
		ALLEGRO_FONT* font() const;
		ALLEGRO_COLOR fontColor() const;


		void draw (GBox, Resource&);
		Input* getInput (GBox, Resource&, ALLEGRO_EVENT&, ALLEGRO_EVENT_QUEUE*);

	private:
		ALLEGRO_FONT* _font;
		ALLEGRO_USTR* _label;
		ALLEGRO_COLOR _fontColor;
};

#endif
