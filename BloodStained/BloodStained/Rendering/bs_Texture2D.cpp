#include "bs_Texture2D.h"


namespace bs
{
	ui32 Texture2D::sm_boundTextureCount = 0;

	Texture2D::Texture2D()
		:m_width(0),
		m_height(0),
		m_id(0),
		m_isTiled(false)
	{
		
	}

	Texture2D::Texture2D(ui16 width, ui16 height, ui32 id, bool isTiled)
		:m_width(width),
		m_height(height),
		m_id(id),
		m_isTiled(isTiled)
	{

	}

	Texture2D::Texture2D(const Texture2D& t)
		:m_width(t.m_width),
		m_height(t.m_height),
		m_id(t.m_id),
		m_isTiled(t.m_isTiled)
	{

	}

	GLenum	Texture2D::_textureBindIndex() const
	{
		return GL_TEXTURE0;
	}

	Texture2D::~Texture2D()
	{
		unbind();
	}

	Texture2D Texture2D::create(i32 channels, ui32 width, ui32 height, byte* buffer, bool tiled)
	{
		ui32 id = 0;
		::glGenTextures(1, &id);
		if (id == 0)
		{
			return Texture2D();
		}

		//Bind texture
		::glBindTexture(GL_TEXTURE_2D, id);

		//Set correct alignment.
		if (channels != GL_RGBA) ::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		else ::glPixelStorei(GL_PACK_ALIGNMENT, 4);

		::glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, channels, GL_UNSIGNED_BYTE, buffer);

		GLenum	textureType = tiled ? GL_REPEAT : GL_CLAMP_TO_EDGE;

		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureType);
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureType);
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		::glGenerateMipmap(GL_TEXTURE_2D);

		//Unbind texture
		::glBindTexture(GL_TEXTURE_2D, 0);

		Texture2D tex = Texture2D(width, height, id, tiled);
		return tex;
	}

	void	Texture2D::destroy(Texture2D& tex)
	{
		GLuint id = tex.id();
		::glDeleteTextures(1, &id);
		tex.m_width = 0;
		tex.m_height = 0;
		tex.m_id = 0;
		tex.m_isTiled = false;
	}
}