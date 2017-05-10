#ifndef BS_FONT_H
#define BS_FONT_H

#include "../../../Containers/bs_HashMap.h"
#include "../../bs_Texture2D.h"


namespace bs
{
	struct FontGlyph
	{
	public:
		ui16	unicode;
		ui16	index;

		ui16	width;
		ui16	height;
		ui16	horizontalAdvance;
		ui16	verticalAdvance;
		i16		bearingX;
		i16		bearingY;

		ui16	textureX;
		ui16	textureY;
		ui16	textureWidth;
		ui16	textureHeight;
	};

	class Font
	{
		friend class FontManager;
	public:
		Font();
		Font(const Font& f);
		~Font();

		inline	const String& name(){ return m_name; }
		inline const Texture2D& texture(){ return m_texture; }

	private:
		HashMap<ui16, FontGlyph>	m_glyphs;
		String						m_name;
		Texture2D					m_texture;
	};
}

#endif // !BS_FONT_H
