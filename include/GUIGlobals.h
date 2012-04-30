
#include <algorithm>
#include <allegro.hpp>
#include <vector>
#include <set>
#include <cstdio>

#ifndef _GUI_GLOBALS_H_
#define _GUI_GLOBALS_H_

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#define al_destroy_ustr(x) if(x){al_ustr_free(x); x=NULL;}

#define fillBoxShort(a,b) fillBox (a, BMP (bd_t), BMP (bd_r), BMP (bd_b), BMP (bd_l), BMP (cr_tl), BMP (cr_tr), BMP (cr_br), BMP (cr_bl), BMP (bg),  b)

namespace GUI
{
	struct DLL_EXPORT FLAG
	{
		enum en
		{
			FILLBOX_FLIP_H = 1,
			FILLBOX_FLIP_V = 2,
			FILLBOX_ROTATE = 4,
			SCROLL_FLIP = 1,
			SCROLL_HORIZONTAL = 2
		};
	};
	struct DLL_EXPORT GFX_ID
	{
		enum en
		{
			MENU,
			menu_bd_t, menu_bd_r,
			menu_bd_b, menu_bd_l,
			menu_cr_tl, menu_cr_tr,
			menu_cr_bl, menu_cr_br,
			menu_bg, menu_fg,

			BUTTON,
			button_bd_t, button_bd_r,
			button_bd_b, button_bd_l,
			button_cr_tl, button_cr_tr,
			button_cr_bl, button_cr_br,
			button_bg, button_fg,

			CHECKBOX,
			checkbox_bd_t, checkbox_bd_r,
			checkbox_bd_b, checkbox_bd_l,
			checkbox_cr_tl, checkbox_cr_tr,
			checkbox_cr_bl, checkbox_cr_br,
			checkbox_bg, checkbox_fg,

			SCROLL_BUTTON,
			scroll_button_bd_t, scroll_button_bd_r,
			scroll_button_bd_b, scroll_button_bd_l,
			scroll_button_cr_tl, scroll_button_cr_tr,
			scroll_button_cr_bl, scroll_button_cr_br,
			scroll_button_bg, scroll_button_fg,

			SCROLL_GRIP,
			scroll_grip_bd_t, scroll_grip_bd_r,
			scroll_grip_bd_b, scroll_grip_bd_l,
			scroll_grip_cr_tl, scroll_grip_cr_tr,
			scroll_grip_cr_bl, scroll_grip_cr_br,
			scroll_grip_bg, scroll_grip_fg,

			SCROLL_BAR,
			scroll_bar_bd_t, scroll_bar_bd_r,
			scroll_bar_bd_b, scroll_bar_bd_l,
			scroll_bar_cr_tl, scroll_bar_cr_tr,
			scroll_bar_cr_bl, scroll_bar_cr_br,
			scroll_bar_bg, scroll_bar_fg,

			DROPLIST,
			droplist_bd_t, droplist_bd_r,
			droplist_bd_b, droplist_bd_l,
			droplist_cr_tl, droplist_cr_tr,
			droplist_cr_bl, droplist_cr_br,
			droplist_bg, droplist_fg,

			DROPLIST_OPTION,
			droplist_option_bd_t, droplist_option_bd_r,
			droplist_option_bd_b, droplist_option_bd_l,
			droplist_option_cr_tl, droplist_option_cr_tr,
			droplist_option_cr_bl, droplist_option_cr_br,
			droplist_option_bg, droplist_option_fg,

			size //keep track of the enum size so it's easier to extend this enum
		};
	};
	struct DLL_EXPORT WIDGET_TYPE
	{
		enum en
		{
			NONE,
			MENU,
			BUTTON,
			CHECKBOX,
			SCROLL,
			DROPLIST,
			size
		};
	};
	struct DLL_EXPORT INPUT_TYPE
	{
		enum en
		{
			NONE, //no interaction detected

			MOUSE_DOWN, //when the mouse is pressed inside an element
			MOUSE_UP, //when the mouse is released inside an element (however, the mouse wasn't pressed inside it)
			MOUSE_CLICK, //when an element is clicked (down+up inside the element)

			MOUSE_HOLD, //when the mouse is held on an element
			MOUSE_DRAG, //when a draggable element is being dragged

			MOUSE_HOVER, //when the mouse hovers an element
			MOUSE_LEAVE, //when the mouse leaves an element

			TEXT_WRITE, //when somthing is written in an element
			TEXT_DELETE, //deleted a character
			TEXT_BLINK, //when the cursor in a textbox blinks

			size //enum size for easier extending
		};
	};
	template<typename T>
	struct DLL_EXPORT GVector2D
	{
		T x, y;
		GVector2D () : x (0), y (0) {}
		GVector2D (T _x, T _y) : x (_x), y (_y) {}
		GVector2D (const GVector2D& other) : x (other.x), y (other.y) {}

		GVector2D& operator = (const GVector2D& other)
		{
			x = other.x;
			y = other.y;
			return *this;
		}
	};

	template<typename T>
	struct DLL_EXPORT GVector4D
	{
		T x, y, w, h;
		GVector4D () : x (0), y (0), w (0), h (0) {}
		GVector4D (T _x, T _y, T _w, T _h) : x (_x), y (_y), w (_w), h (_h) {}
		GVector4D (const GVector4D& other) : x (other.x), y (other.y), w (other.w), h (other.h) {}

		GVector4D& operator= (const GVector4D& other)
		{
			x = other.x;
			y = other.y;
			w = other.w;
			h = other.h;
			return *this;
		}
		GVector4D operator>> (const GVector4D<T>& other)
		{
			return GVector4D (x + other.x, y + other.y, w, h);
		}
		GVector4D operator>> (const GVector2D<T>& other)
		{
			return GVector4D (x + other.x, y + other.y, w, h);
		}
		bool collides (const GVector2D<T>& other)
		{
			return (other.x >= x and other.x <= x + w) and (other.y >= y and other.y <= y + h);
		}
		bool collides (const GVector4D<T>& other)
		{
			if ( (other.x <= x + w and other.x >= x) or (other.x + other.w <= x + w and other.x + other.w >= x))
			{
				if ( (other.y <= y + h and other.y >= y) or (other.y + other.h <= y + h and other.y + other.h >= y))
				{
					return true;
				}
			}
			return false;
		}
	};

	typedef GVector2D<int> GPoint;
	typedef GVector4D<int> GBox;

#include "GUIInput.h"
#include "GUIResource.h"

#include "GUIWidget.h"
#include "GUIMenu.h"
#include "GUIButton.h"
#include "GUICheckBox.h"
#include "GUIScroll.h"
#include "GUIDropList.h"

#include "GUIManager.h"

}

#endif
