
#ifndef _GUI_RESOURCE_H_
#define _GUI_RESOURCE_H_

class DLL_EXPORT Resource
{
	public:
		Resource();
		~Resource();

		void setGfxIdSize (GFX_ID::en size);
		ALLEGRO_BITMAP* getGfx (GFX_ID::en id);
		void loadGfxFolder (ALLEGRO_PATH* path, GFX_ID::en offset);
	private:
		std::vector<ALLEGRO_BITMAP*> gfx;
};

#endif
