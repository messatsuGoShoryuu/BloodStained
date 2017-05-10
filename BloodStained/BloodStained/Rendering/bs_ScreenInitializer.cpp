#include "bs_ScreenInitializer.h"
#include "bs_Screen.h"


namespace bs
{
	void	ScreenInitializer::setWidth(Screen& s, ui16 value)
	{
		s._setWidth(value);
		s._calculateAspectRatio();
	}

	void	ScreenInitializer::setHeight(Screen& s, ui16 value)
	{
		s._setHeight(value);
		s._calculateAspectRatio();
	}

	void	ScreenInitializer::setDimensions(Screen& s, ui16 w, ui16 h)
	{
		s._setWidth(w);
		s._setHeight(h);
		s._calculateAspectRatio();
	}
}