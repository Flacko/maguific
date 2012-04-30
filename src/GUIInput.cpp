
#include "GUIGlobals.h"

GUI::Input::Input (INPUT_TYPE::en t, Widget* w, Menu* m) : _type (t), _widget (NULL), _menu (NULL)
{
	widget (w);
	menu (m);
}
GUI::Input::Input (const Input& other) : _type (INPUT_TYPE::NONE), _widget (NULL), _menu (NULL)
{
	type (other.type());
	widget (other.widget());
	menu (other.menu());
}
GUI::Input::Input& GUI::Input::operator = (const Input& other)
{
	type (other.type());
	widget (other.widget());
	menu (other.menu());
	return *this;
}

GUI::Input::~Input()
{
	widget (NULL);
	menu (NULL);
}

bool GUI::Input::valid()
{
	if (_widget == NULL or _type == INPUT_TYPE::NONE)
	{
		return false;
	}
	return true;
}

void GUI::Input::type (INPUT_TYPE::en t)
{
	_type = t;
}
void GUI::Input::widget (Widget* w)
{
	_widget = w;
}
void GUI::Input::menu (Menu* m)
{
	_menu = m;
}
GUI::INPUT_TYPE::en GUI::Input::type() const
{
	return _type;
}
GUI::Widget* GUI::Input::widget() const
{
	return _widget;
}
GUI::Menu* GUI::Input::menu() const
{
	return _menu;
}
