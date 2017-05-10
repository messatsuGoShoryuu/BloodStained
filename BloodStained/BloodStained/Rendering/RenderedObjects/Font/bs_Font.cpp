#include "../../../Globals/bs_globals.h"


namespace bs
{
	Font::Font()
	{

	}

	Font::Font(const Font& f)
		:m_glyphs(f.m_glyphs)
	{

	}

	Font::~Font()
	{

	}
}