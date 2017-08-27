#ifndef _BS_COLOR_H_
#define _BS_COLOR_H_

#include "../Utilities/bs_types.h"

namespace bs
{
	struct ColorRGBA32
	{
		ColorRGBA32():r(255),g(255),b(255),a(255){}
		ColorRGBA32(ui8 r, ui8 g, ui8 b, ui8 a) :r(r), g(g), b(b), a(a){}
		ColorRGBA32(ui8 r, ui8 g, ui8 b) :r(r), g(g), b(b), a(255){}
		ColorRGBA32(const ColorRGBA32& c) :r(c.r), g(c.g), b(c.b), a(c.a){}

		ui8	r;
		ui8 g;
		ui8 b;
		ui8 a;

		static ColorRGBA32 white;
		static ColorRGBA32 black;
		static ColorRGBA32 transparentWhite;
		static ColorRGBA32 transparentBlack;
		static ColorRGBA32 red;
		static ColorRGBA32 green;
		static ColorRGBA32 blue;
		static ColorRGBA32 cyan;
		static ColorRGBA32 magenta;
		static ColorRGBA32 yellow;
	};

	struct ColorRGB24
	{
		ColorRGB24() :r(255), g(255), b(255){}
		ColorRGB24(ui8 r, ui8 g, ui8 b, ui8 a) :r(r), g(g), b(b){}
		ColorRGB24(ui8 r, ui8 g, ui8 b) :r(r), g(g), b(b){}
		ColorRGB24(const ColorRGB24& c) :r(c.r), g(c.g), b(c.b){}

		ui8	r;
		ui8 g;
		ui8 b;

		static ColorRGB24 white;
		static ColorRGB24 black;
		static ColorRGB24 red;
		static ColorRGB24 green;
		static ColorRGB24 blue;
		static ColorRGB24 cyan;
		static ColorRGB24 magenta;
		static ColorRGB24 yellow;
	};

	struct ColorRGBAf
	{
		ColorRGBAf() :r(1.0f), g(1.0f), b(1.0f), a(1.0f){}
		ColorRGBAf(const ColorRGBA32& c)
		{
			r = (f32)c.r / 255.0f;
			g = (f32)c.g / 255.0f;
			b = (f32)c.b / 255.0f;
			a = (f32)c.a / 255.0f;
		}
		ColorRGBAf(f32 r, f32 g, f32 b, f32 a) :r(r), g(g), b(b), a(a){}
		ColorRGBAf(ui8 r, ui8 g, ui8 b) :r(r), g(g), b(b), a(255){}
		ColorRGBAf(const ColorRGBAf& c) :r(c.r), g(c.g), b(c.b), a(c.a){}

		f32	r;
		f32 g;
		f32 b;
		f32 a;

		class String	toString() const;
	};

}

#endif // !BS_COLOR_H
