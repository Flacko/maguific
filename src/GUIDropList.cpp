
#include "GUIGlobals.h"

GUI::DropList::DropList(GBox b, ALLEGRO_FONT* f, int s, int bW) : _scroll(NULL), _button(NULL), _font(NULL)
{
	box(b);
	selection(s);
	font(f);
	buttonWidth(bW);
}
