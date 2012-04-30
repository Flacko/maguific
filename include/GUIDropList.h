
#ifndef _GUI_DROPLIST_H_
#define _GUI_DROPLIST_H_

class DLL_EXPORT DropList : public Widget
{
	public:
		DropList (GBox b, ALLEGRO_FONT* f, ALLEGRO_USTR* l, ALLEGRO_COLOR fC, Scroll* sC, int sO);
		~DropList();
		WIDGET_TYPE::en type();

		void addOption (ALLEGRO_USTR* o);
		void removeOption (int i);
		ALLEGRO_USTR* getOption (int i) const;


		void selection (int s);
		int selection() const;

		void font (ALLEGRO_FONT* f);
		ALLEGRO_FONT* font() const;

		void fontColor (ALLEGRO_COLOR fC);
		ALLEGRO_COLOR fontColor() const;

		void scroll (Scroll* s);
		Scroll* scroll() const;

		void label (ALLEGRO_USTR* l);
		ALLEGRO_USTR* label() const;

		void shownOptions (int sO);
		int shownOptions() const;

		void draw (GBox menupos, Resource& res);
		Input* getInput (GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq);

	private:
		void recalculateScrollMax();
		ALLEGRO_FONT* _font;
		ALLEGRO_COLOR _fontColor;
		int _expand;
		int _selection;
		int _shownOptions;

		std::vector<ALLEGRO_USTR*> _options;
		ALLEGRO_USTR* _label;

		Scroll* _scroll;
};

#endif
