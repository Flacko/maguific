
#ifndef _GUI_RESOURCE_H_
#define _GUI_RESOURCE_H_

class DLL_EXPORT Resource
{
	public:
		Resource();
		~Resource();

		void setGfxIdSize (GUI::GFX_ID::en size);
		ALLEGRO_BITMAP* getGfx (GUI::GFX_ID::en id);
		void loadGfxFolder (ALLEGRO_PATH* path, GUI::GFX_ID::en offset);
	private:
		std::vector<ALLEGRO_BITMAP*> gfx;
};

#endif
