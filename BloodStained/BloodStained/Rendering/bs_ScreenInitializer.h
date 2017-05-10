#ifndef BS_SCREENINITIALIZER_H
#define BS_SCREENINITIALIZER_H

#include "../Utilities/bs_types.h"
namespace bs
{
	class Screen;
	class ScreenInitializer
	{
	public:
		static void	setWidth(Screen& s, ui16 value);
		static void	setHeight(Screen& s, ui16 value);
		static void setDimensions(Screen& s, ui16 w, ui16 h);
	};
}
#endif // !BS_SCREENINITIALIZER_H
