
#ifndef _GUI_MENU_H_
#define _GUI_MENU_H_

class DLL_EXPORT Menu : public GUI::Widget
{
	public:
		Menu (GBox b);
		~Menu();
		GUI::WIDGET_TYPE::en type() const;

		GUI::Widget* widget (int wid) const;
		GUI::Widget* widget (GUI::Widget* w);

		void draw (GBox menupos, Resource& res);
		Input* getInput (GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq);

	private:
		std::vector<GUI::Widget*> _widget;
};

#endif // CMENU
