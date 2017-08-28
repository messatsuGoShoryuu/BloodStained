#ifndef _BS_SCREEN_H_
#define _BS_SCREEN_H_

#include <Utilities/bs_types.h>

namespace bs
{
	class Screen
	{
	public:
		friend class ScreenInitializer;

		static ui32 width()			{ return s_width; }
		static ui32 height()		{ return s_height; }
		static f32 aspectRatio()	{ return s_aspectRatio; }

	private:
		//Width and height in pixels
		static	ui32	s_width;
		static	ui32	s_height;
		static	f32		s_aspectRatio;
	};

	
	class ScreenInitializer
	{
	public:
		static void initScreen(ui32 width, ui32 height);
	};
}

#endif