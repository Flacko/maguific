
#ifndef _GUI_CHECKBOX_H_
#define _GUI_CHECKBOX_H_

class DLL_EXPORT CheckBox : public Widget
{
	public:
		CheckBox (GBox _box, bool v);

		WIDGET_TYPE::en type() const
		{
			return GUI::WIDGET_TYPE::CHECKBOX;
		}

		void value (bool v)
		{
			_value = v;
		}
		bool value() const
		{
			return _value;
		}

		void draw (GBox menupos, Resource& res);
		Input* getInput (GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE*);
	private:
		bool _value;
};

#endif
