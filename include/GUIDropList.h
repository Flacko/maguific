
#ifndef _GUI_DROPLIST_H_
#define _GUI_DROPLIST_H_

class DLL_EXPORT DropList : public Widget
{
	public:
		DropList(GBox b, ALLEGRO_FONT* f, int s, int bW);
		~DropList();

		void options(ALLEGRO_USTR* o);
		ALLEGRO_USTR* options(int i) const;

		void options(std::vector<ALLEGRO_USTR*> o);
		std::vector<ALLEGRO_USTR*> options() const;

		void enabled(int i, bool e);
		bool enabled(int i) const;

		void selection(int s);
		int selection() const;

		void font(ALLEGRO_FONT* f);
		ALLEGRO_FONT* font() const;

		void buttonWidth(int bW);
		int buttonWidth() const;

		void clear();

		void draw (GBox menupos, Resource& res);
		Input* getInput (GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq);

	private:
		ALLEGRO_FONT* _font;
		int _selection;
		int _buttonWidth;

		std::set<int> _enabled;
		std::vector<ALLEGRO_USTR> _options;

		Scroll* _scroll;
		Button* _button;
};

#endif
