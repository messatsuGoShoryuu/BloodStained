#ifndef BS_FONTMANAGER_H
#define	BS_FONTMANAGER_H

#include "bs_Font.h"

namespace bs
{
	

	class FontManager
	{
		friend class FontResource;
	public:
		FontManager();
		~FontManager();

		inline Font* operator[](String id)
		{
			if (!m_fonts.isEmptyAt(id)) return &m_fonts[id];
			return nullptr;
		}

	private:
		FontManager(const FontManager& f);

	private:
		Font*		_createFont(byte* rawData, size_t dataSize, const String& charset, f32 charSize);
		Font*		_addFont(String name);
		bool			_getGlyphsFromRawData(Font** font, byte* rawData, size_t dataSize, const String& charset, f32 charSize);
		void			_createBitmap(ui32 w, ui32 h, Font* font, const String& charset);
		void			_drawGlyphToBitmap(byte* out, byte* glyphData, FontGlyph& glyph, ui32 glyphW, ui32 glyphH, ui32 bitmapW, ui32 bitmapH);
				
	public:

		bool	initialize();
		bool	shutDown();

	private:
		HashMap<String, Font>	m_fonts;
	};
}

#endif // !BS_FONTMANAGER_H
