#include "../../../Globals/bs_globals.h"
#include <ft2build.h>
#include <freetype.h>


namespace bs
{
	FT_Library	g_ftLibrary;
	FT_Face		face;

	FontManager::FontManager()
	{

	}

	FontManager::~FontManager()
	{

	}

	bool	FontManager::initialize()
	{
		if (FT_Init_FreeType(&g_ftLibrary)) return false;
		return true;
	}


	bool	FontManager::shutDown()
	{
		m_fonts.~HashMap();
		return true;
	}

	Font*	FontManager::_addFont(String name)
	{
		Font* result = nullptr;
		if (m_fonts.isEmptyAt(name)) m_fonts[name] = Font();
		result = &m_fonts[name];
		result->m_name = name;
		return result;
	}

	Font*		FontManager::_createFont(byte* rawData, size_t dataSize, const String& charset, f32 charSize)
	{
		if (face) delete face;
		face = new FT_FaceRec();
		Font* f = nullptr;

		if (!_getGlyphsFromRawData(&f, rawData, dataSize, charset, 16))
		{
			return nullptr;
		}

		_createBitmap(512, 512, f, charset);
		
		return f;
	}

	bool	FontManager::_getGlyphsFromRawData(Font** font, 
											   byte* rawData, 
											   size_t dataSize, 
											   const String& charset, 
											   f32 charSize)
	{

		//Create Face object on memory from raw data
		i32 error = FT_New_Memory_Face(g_ftLibrary, rawData, dataSize, 0, &face);

		std::cout << "Error = " << error << std::endl;
		if (error) return false;

		//Create font object on our font manager.
		*font = _addFont(face->family_name);

		if (!(*font))
		{
			return false;
		}

		error = FT_Set_Pixel_Sizes(face, 64, 0);

		if (error) return false;

		ui32 length = charset.length();

		//Create glyphs for each character in the charset.
		for (ui32 i = 0; i < length; i++)
		{
			ui16 unicode = (ui16)charset[i];
			i32 glyphIndex = FT_Get_Char_Index(face, unicode);

			FontGlyph glyph;
			glyph.unicode = unicode;
			glyph.index = glyphIndex;

			error = FT_Load_Glyph(face, glyphIndex, NULL);

			glyph.bearingX = (face->glyph->metrics.horiBearingX >> 6);
			glyph.bearingY = (face->glyph->metrics.horiBearingY >> 6);

			glyph.width = (face->glyph->metrics.width >> 6);
			glyph.height = (face->glyph->metrics.height >> 6);


			glyph.horizontalAdvance = (face->glyph->advance.x >> 6);
			glyph.verticalAdvance = (face->glyph->advance.y >> 6);

			(*font)->m_glyphs[unicode] = glyph;
		}

		return true;
	}

	void			FontManager::_createBitmap(ui32 w, ui32 h, Font* font, const String& charset)
	{

		//8 bit channel
		ui32 arraySize = w * h;

		byte* rawData = (byte*)BS_Malloc(arraySize);

		for (int i = 0; i < arraySize; i++)
		{
			rawData[i] = 0x00;
		}

		int x = 0;
		int y = 0;

#ifdef BS_ASSERT
		assert(font);
#endif // BS_ASSERT

		

		ui32 length = charset.length();
		for (ui32 i = 0; i < length; i++)
		{
			ui16 unicode = (ui16)charset[i];
			FontGlyph* glyph = &font->m_glyphs[unicode];

#ifdef BS_ASSERT
			assert(glyph);
			assert(glyph->unicode == unicode);
			assert(face);
#endif // BS_ASSERT

			FT_Error error = FT_Load_Char(face, glyph->unicode, FT_LOAD_RENDER);

			FT_GlyphSlot glyphSlot = face->glyph;

#ifdef BS_ASSERT
			assert(glyphSlot);
#endif // BS_ASSERT

			glyph->textureX = x;
			glyph->textureY = y;
			glyph->textureWidth = glyphSlot->bitmap.width;
			glyph->textureHeight = glyphSlot->bitmap.rows;

			x += glyphSlot->bitmap.width + 5;


			if (x > w - glyphSlot->bitmap.width)
			{
				y += 64;
				x = 0;
			}

			_drawGlyphToBitmap(rawData, glyphSlot->bitmap.buffer, *glyph, glyphSlot->bitmap.width, glyphSlot->bitmap.rows, w, h);
		}

		font->m_texture = Texture2D::create(GL_RED, w, h, rawData, false);

		BS_Free(rawData);
	}

	void			FontManager::_drawGlyphToBitmap(byte* out, 
													byte* glyphData, 
													FontGlyph& glyph, 
													ui32 glyphW, 
													ui32 glyphH, 
													ui32 bitmapW, 
													ui32 bitmapH)
	{
		i32 x = glyph.textureX;
		i32 y = glyph.textureY;

		i32 i = 0;
		i32 j = 0;

		for (i = 0; i < glyphW; i++)
		{
			for (j = 0; j < glyphH; j++)
			{
				out[x + i + 512 * (j + y)] = glyphData[i + glyphW * j];
			}
		}
	}
}