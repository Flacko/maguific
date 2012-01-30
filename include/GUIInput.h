
#ifndef _GUI_INPUT_H_
#define _GUI_INPUT_H_

class Widget;
class Menu;

class DLL_EXPORT Input
{
	public:
		Input (GUI::INPUT_TYPE::en t, Widget* w)
		{
			type (t);
			widget (w);
		}
		Input (GUI::INPUT_TYPE::en t, Widget* w, Menu* m)
		{
			type (t);
			widget (w);
			menu (m);
		}
		~Input()
		{
			widget (NULL);
			menu (NULL);
		}

		void type (INPUT_TYPE::en t)
		{
			_type = t;
		}
		void widget (Widget* w)
		{
			_widget = w;
		}
		void menu (Menu* m)
		{
			_menu = m;
		}

		INPUT_TYPE::en type()
		{
			return _type;
		}
		Widget* widget()
		{
			return _widget;
		}
		Menu* menu()
		{
			return _menu;
		}

	private:
		INPUT_TYPE::en _type; //input type
		Widget* _widget; //pointer to widget
		Menu* _menu;
};
#endif
