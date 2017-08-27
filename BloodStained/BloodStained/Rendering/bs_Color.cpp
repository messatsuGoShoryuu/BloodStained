#include "bs_Color.h"
#include "../Math/bs_math.h"

#include "../Utilities/bs_String.h"

namespace bs
{
	ColorRGBA32 initializeColor(ui8 r, ui8 g, ui8 b, ui8 a)
	{
		ColorRGBA32 result;
		result.r = r;
		result.g = g;
		result.b = b;
		result.a = a;
		return result;
	}

	ColorRGBA32 ColorRGBA32::white =				initializeColor(255, 255, 255, 255);
	ColorRGBA32 ColorRGBA32::black =				initializeColor(0, 0, 0, 255);
	ColorRGBA32 ColorRGBA32::transparentWhite =		initializeColor(255, 255, 255, 0);
	ColorRGBA32 ColorRGBA32::transparentBlack =		initializeColor(0, 0, 0, 0);
	ColorRGBA32 ColorRGBA32::red =					initializeColor(255, 0, 0, 255);
	ColorRGBA32 ColorRGBA32::green =				initializeColor(0, 255, 0, 255);
	ColorRGBA32 ColorRGBA32::blue =					initializeColor(0, 0, 255, 255);
	ColorRGBA32 ColorRGBA32::cyan =					initializeColor(0, 255, 255, 255);
	ColorRGBA32 ColorRGBA32::magenta =				initializeColor(255, 0, 255, 255);
	ColorRGBA32 ColorRGBA32::yellow =				initializeColor(255, 255, 0, 255);


	ColorRGB24	initializeColor24(ui8 r, ui8 g, ui8 b)
	{
		ColorRGB24 result;
		result.r = r;
		result.g = g;
		result.b = b;
		return result;
	}

	ColorRGB24 ColorRGB24::white = initializeColor24(255, 255, 255);
	ColorRGB24 ColorRGB24::black = initializeColor24(0, 0, 0);
	ColorRGB24 ColorRGB24::red = initializeColor24(255, 0, 0);
	ColorRGB24 ColorRGB24::green = initializeColor24(0, 255, 0);
	ColorRGB24 ColorRGB24::blue = initializeColor24(0, 0, 255);
	ColorRGB24 ColorRGB24::cyan = initializeColor24(0, 255, 255);
	ColorRGB24 ColorRGB24::magenta = initializeColor24(255, 0, 255);
	ColorRGB24 ColorRGB24::yellow = initializeColor24(255, 255, 0);

	String	ColorRGBAf::toString() const
	{
		String result;
		result = result + "R = " + r + ", G = " + g + ", B = " + b + ", A = " + a;
		return result;
	}
	
}