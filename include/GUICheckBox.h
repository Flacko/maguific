
#ifndef _GUI_CHECKBOX_H_
#define _GUI_CHECKBOX_H_

class DLL_EXPORT CheckBox : public Widget
{
	public:
		CheckBox (GBox b, bool v);

		WIDGET_TYPE::en type() const;

		void value (bool v);
		bool value() const;

		void draw (GBox menupos, Resource& res);
		Input* getInput (GBox menupos, Resource& res, ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE*);
	private:
		bool _value;
};

#endif
