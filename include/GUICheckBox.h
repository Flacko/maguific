
#ifndef _GUI_CHECKBOX_H_
#define _GUI_CHECKBOX_H_

class DLL_EXPORT CheckBox : public GUI::Widget
{
	public:
		CheckBox(GBox _box, bool v);
		void value(bool v) { _value = v; }
		bool value() { return _value; }

		GUI::WIDGET_TYPE::en type(){ return GUI::WIDGET_TYPE::CHECKBOX; }
		void draw(GBox menupos, Resource& res);
		Input* getInput(GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE*);
	private:
		bool _value;
};

#endif
