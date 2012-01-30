
#ifndef _GUI_MENU_H_
#define _GUI_MENU_H_

class DLL_EXPORT Menu : public GUI::Widget
{
	public:
		Menu (GBox b);
		~Menu();
		GUI::WIDGET_TYPE::en type();

		GUI::Widget* addWidget (GUI::Widget* w);
		GUI::Widget* getWidget (int wid);

		void draw (Resource& res);
		Input* getInput (Resource& res, ALLEGRO_EVENT&, ALLEGRO_EVENT_QUEUE*);

	private:
		std::vector<GUI::Widget*> widget;
};

#endif // CMENU
