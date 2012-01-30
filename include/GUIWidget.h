
#ifndef _GUI_WIDGET_H_
#define _GUI_WIDGET_H_

class DLL_EXPORT Widget
{
	public:

		ALLEGRO_COLOR foreColor; //foreground color (borders, whatever)
		ALLEGRO_COLOR backColor; //background color (backgrounds and stuff)

		void init();
		virtual void setColors(ALLEGRO_COLOR, ALLEGRO_COLOR);

		virtual void id(int i){ _id = i; }
		virtual int id(){ return _id; }

		virtual void box(GUI::GBox b) { _box = b; }
		virtual GUI::GBox box() { return _box; }

		virtual GUI::WIDGET_TYPE::en type() { return GUI::WIDGET_TYPE::NONE; }

		virtual void draw(GUI::GBox menupos, GUI::Resource& res); //relative from parent menu coordinates (menupos)
		virtual GUI::Input* getInput(GUI::GBox menupos, GUI::Resource& res, ALLEGRO_EVENT&, ALLEGRO_EVENT_QUEUE*);

	protected:
		int _id; //numeric index for this widget in the menu's widget array
		GUI::GBox _box; //geometric class to store the widget's coords

		char selected; //selected (mouse pressed on widget but not released yet)
		char hover; // hoovering (mouse is over the widget)

		//draw the default sizeable box with 4 borders and 4 corners and tiled seamless background
		void fillBox(GUI::GBox box, ALLEGRO_BITMAP* bd_t, ALLEGRO_BITMAP* bd_r, ALLEGRO_BITMAP* bd_b, ALLEGRO_BITMAP* bd_l, ALLEGRO_BITMAP* cr_tl, ALLEGRO_BITMAP* cr_tr, ALLEGRO_BITMAP* cr_br, ALLEGRO_BITMAP* cr_bl, ALLEGRO_BITMAP* bg, int flags);
		void fillBox_bg(ALLEGRO_BITMAP* bm, int _x, int _y, int _w, int _h);
	private:
};
#endif
