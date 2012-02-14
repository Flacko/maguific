
#ifndef _GUI_INPUT_H_
#define _GUI_INPUT_H_

class Widget;
class Menu;

class DLL_EXPORT Input
{
	public:
		Input (INPUT_TYPE::en t, Widget* w, Menu* m);
		Input (const Input& other);
		Input &operator = (const Input& other);
		~Input();

		bool valid();

		void type (INPUT_TYPE::en t);
		void widget (Widget* w);
		void menu (Menu* m);

		INPUT_TYPE::en type() const;
		Widget* widget() const;
		Menu* menu() const;

	private:
		INPUT_TYPE::en _type; //input type
		Widget* _widget; //pointer to widget
		Menu* _menu; //optional pointer to menu
};
#endif
