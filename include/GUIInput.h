
#ifndef _GUI_INPUT_H_
#define _GUI_INPUT_H_

class Widget;
class Menu;

class DLL_EXPORT Input
{
	public:
		Input (GUI::INPUT_TYPE::en t, Widget* w, Menu* m) : _type (t), _widget (NULL), _menu (NULL)
		{
			widget (w);
			menu (m);
		}
		Input (const Input& other) : _type (GUI::INPUT_TYPE::NONE), _widget (NULL), _menu (NULL)
		{
			type (other.type());
			widget (other.widget());
			menu (other.menu());
		}
		Input &operator = (const Input& other)
		{
			type (other.type());
			widget (other.widget());
			menu (other.menu());
			return *this;
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

		INPUT_TYPE::en type() const
		{
			return _type;
		}
		Widget* widget() const
		{
			return _widget;
		}
		Menu* menu() const
		{
			return _menu;
		}

	private:
		INPUT_TYPE::en _type; //input type
		Widget* _widget; //pointer to widget
		Menu* _menu; //optional pointer to menu
};
#endif
