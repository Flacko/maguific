
#ifndef _GUI_MENU_H_
#define _GUI_MENU_H_

class DLL_EXPORT Menu : public Widget
{
	public:
		Menu (GBox b);
		~Menu();
		WIDGET_TYPE::en type() const;

		Widget* widget (int wid) const;
		Widget* widget (Widget* w);

		void draw (GBox menupos, Resource& res);
		Input* getInput (GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq);

	private:
		std::vector<Widget*> _widget;
};

#endif // CMENU
