#include "bs_Screen.h"

namespace bs
{
	ui32 Screen::s_width;
	ui32 Screen::s_height;
	f32  Screen::s_aspectRatio;

	void ScreenInitializer::initScreen(ui32 width, ui32 height)
	{
		Screen::s_width = width;
		Screen::s_height = height;
		Screen::s_aspectRatio = (f32)width / (f32)height;

	}
}