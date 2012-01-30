
#ifndef _GUI_MANAGER_H_
#define _GUI_MANAGER_H_

#include "GUIGlobals.h"

class DLL_EXPORT Manager
{
	public:
		Manager();
		~Manager();

		void setGfxIdSize (GFX_ID::en);
		void loadGfxFolder (const char* dir, GFX_ID::en id);

		GUI::Widget* getWidget (int mid, int wid);
		Menu* getMenu (int mid);
		Menu* addMenu (Menu* m);

		void draw();
		Input* getInput (ALLEGRO_EVENT& ev, ALLEGRO_EVENT_QUEUE* eq);

	private:
		Resource res;
		std::vector<Menu*> menus;
};

#endif
