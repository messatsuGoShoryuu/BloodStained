#include "bs_Texture2D.h"
#include "bs_RenderManager.h"

namespace bs
{
	Texture2D::Texture2D()
		:m_key(""),
		m_id(0),
		m_width(0),
		m_height(0)
	{

	}


	Texture2D::Texture2D(const Texture2D& t)
		:
		m_id(t.m_id),
		m_key(t.m_key),
		m_width(t.m_width),
		m_height(t.m_height)
	{

	}

	Texture2D::~Texture2D()
	{

	}

	void Texture2D::bind(ui32 texIndex)	const
	{
		OpenGL::activeTexture(texIndex);
		OpenGL::bindTexture(OPENGL_TEXTURE::_2D, texIndex);
	}

	void Texture2D::unbind(ui32 texIndex)	const
	{
		OpenGL::activeTexture(texIndex);
		OpenGL::bindTexture(OPENGL_TEXTURE::_2D, texIndex);
	}

	Texture2D* Texture2D::create(byte * data, ui32 width, ui32 height, const String & name, 
		OPENGL_COLOR_FORMAT colorFormat)
	{
		Texture2D* t = &RenderManager::s_textureDB[name];

		if (!RenderManager::s_textureDB.isEmptyAt(name))
		{
			ui32 id = t->id();
			OpenGL::deleteTextures(1, &id);
			t->m_id = 0;
		}

		ui32 id = 0;
		OpenGL::genTextures(1, &id);
		if (id == 0) return nullptr;

		OpenGL::activeTexture(0);
		OpenGL::bindTexture(OPENGL_TEXTURE::_2D, id);

		switch (colorFormat)
		{
		case OPENGL_COLOR_FORMAT::BGR:
		case OPENGL_COLOR_FORMAT::BGRA:
		case OPENGL_COLOR_FORMAT::BGRA_INT:
		case OPENGL_COLOR_FORMAT::BGR_INT:
		case OPENGL_COLOR_FORMAT::RGB:
		case OPENGL_COLOR_FORMAT::RGBA:
		case OPENGL_COLOR_FORMAT::RGBA_INT:
		case OPENGL_COLOR_FORMAT::RGB_INT:
		case OPENGL_COLOR_FORMAT::R_INT:
			OpenGL::pixelStorei(OPENGL_ALIGNMENT::UNPACK, 4);
			break;
		case OPENGL_COLOR_FORMAT::R:
			OpenGL::pixelStorei(OPENGL_ALIGNMENT::UNPACK, 1);
			break;
		case OPENGL_COLOR_FORMAT::RG:
			OpenGL::pixelStorei(OPENGL_ALIGNMENT::UNPACK, 2);
		default:
			OpenGL::pixelStorei(OPENGL_ALIGNMENT::UNPACK, 4);
		}

		OpenGL::bindTexture(OPENGL_TEXTURE::_2D, 0);

		RenderManager::s_textureDB[name] = Texture2D();

		t->m_id = id;
		t->m_key = name;
		t->m_width = width;
		t->m_height = height;

		return t;
	}

	void Texture2D::setClamped(bool value)
	{
		OPENGL_TEXTURE_PARAMETER p = value ? OPENGL_TEXTURE_PARAMETER::CLAMP_TO_EDGE 
			: OPENGL_TEXTURE_PARAMETER::REPEAT;

		OpenGL::texParameteri(OPENGL_TEXTURE::_2D, OPENGL_TEXTURE_PARAMETER_NAME::WRAP_S, p);
	}

}