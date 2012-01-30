#include <cstdio>
#include "GUIGlobals.h"

GUI::Resource::Resource()
{
	setGfxIdSize(GFX_ID::size);
}

GUI::Resource::~Resource()
{
	for(std::vector<ALLEGRO_BITMAP*>::iterator it = gfx.begin(); it != gfx.end(); it++)
	{
		if(*it)
		{
			al_destroy_bitmap(*it);
			*it = NULL;
		}
	}
	gfx.clear();
}

ALLEGRO_BITMAP* GUI::Resource::getGfx(GFX_ID::en id)
{
	return gfx[id];
}

void GUI::Resource::setGfxIdSize(GFX_ID::en size)
{
	if(size_t(size) >= gfx.size())
	{
		gfx.resize(size);
	}
}

void GUI::Resource::loadGfxFolder(ALLEGRO_PATH* path, GFX_ID::en offset)
{
	const char* pattern[]={
		"bd_t.bmp",
		"bd_r.bmp",
		"bd_b.bmp",
		"bd_l.bmp",
		"cr_tl.bmp",
		"cr_tr.bmp",
		"cr_bl.bmp",
		"cr_br.bmp",
		"bg.bmp",
		"fg.bmp"
	};
	const int pattern_size = sizeof(pattern)/sizeof(char*);

	for(int j=0; j<pattern_size; j++)
	{
		al_set_path_filename(path,pattern[j]);
		gfx[offset+j+1] = al_load_bitmap(al_path_cstr(path,'/'));
		if(gfx[offset+j+1] == NULL)
		{
			printf("Failed to load: %s\n",al_path_cstr(path,'/'));
		}
		else
		{
			al_convert_mask_to_alpha(gfx[offset+j+1],al_map_rgb(0xFF,0x00,0xFF));
		}
		al_set_path_filename(path,"");
	}
}
