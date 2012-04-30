
#ifndef _GUI_WIDGET_H_
#define _GUI_WIDGET_H_

class DLL_EXPORT Widget
{
	public:
		Widget();
		virtual ~Widget();

		void setColors (ALLEGRO_COLOR fore, ALLEGRO_COLOR back);

		virtual WIDGET_TYPE::en type() const;

		virtual int id() const;
		virtual GBox box() const;

		virtual void id (int i);
		virtual void box (GBox b);

		virtual void draw (GBox menupos, Resource& res);
		virtual Input* getInput (GBox menupos, Resource& res, ALLEGRO_EVENT&, ALLEGRO_EVENT_QUEUE*);

	protected:
		int _id; //numeric index for this widget in the menu's widget array
		GBox _box; //geometric class to store the widget's coords

		int clicked; //clicked (true if mouse pressed on widget but not released yet)
		int hover; // hoovering (true if mouse is over the widget)

		ALLEGRO_COLOR foreColor; //foreground color (borders, whatever)
		ALLEGRO_COLOR backColor; //background color (backgrounds and stuff)

		//draw the default sizeable box with 4 borders and 4 corners and tiled seamless background
		void fillBox (GBox box, ALLEGRO_BITMAP* bd_t, ALLEGRO_BITMAP* bd_r, ALLEGRO_BITMAP* bd_b, ALLEGRO_BITMAP* bd_l, ALLEGRO_BITMAP* cr_tl, ALLEGRO_BITMAP* cr_tr, ALLEGRO_BITMAP* cr_br, ALLEGRO_BITMAP* cr_bl, ALLEGRO_BITMAP* bg, int flags);
		void fillBox_bg (ALLEGRO_BITMAP* bm, int _x, int _y, int _w, int _h);
	private:
};
#endif
