
#ifndef _GUI_MANAGER_H_
#define _GUI_MANAGER_H_

#include "GUIGlobals.h"

class DLL_EXPORT Manager
{
	public:
		Manager();
		~Manager();

		void gfxIdSize (GFX_ID::en);
		void loadGfxFolder (const char* dir, GFX_ID::en id);

		Widget* widget (int id) const;
		Widget* widget (Widget* w);

		void draw();
		Input* getInput (ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq);

	private:
		Resource res;
		std::vector<Widget*> _widget;
};

#endif
