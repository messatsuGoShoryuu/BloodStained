#include "bs_Texture2D.h"
#include "bs_RenderManager.h"
#include <Utilities/bs_Error.h>

namespace bs
{
	TEXTURE2D_CREATION_METHOD	Texture2D::s_creationMethod;

	Texture2D::Texture2D()
		:m_id(0),
		m_width(0),
		m_height(0)
	{

	}


	Texture2D::Texture2D(const Texture2D& t)
		:m_id(t.m_id),
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
		OpenGL::bindTexture(OPENGL_TEXTURE::_2D, m_id);
	}

	void Texture2D::unbind(ui32 texIndex)	const
	{
		OpenGL::activeTexture(texIndex);
		OpenGL::bindTexture(OPENGL_TEXTURE::_2D, 0);
	}

	ERROR_ID Texture2D::create(Texture2D* tex, byte * data, ui32 width, ui32 height)
	{
		//Create empty texture object
		ui32 id = 0;
		OpenGL::genTextures(1, &id);
		
		if (id == 0) return ERROR_ID::GL_TEXTURE_CREATION_FAIL;

		//Update the passed texture object
		tex->m_id = id;
		tex->bind(0);

		//Retrieve method creation options
		OPENGL_COLOR_FORMAT colorFormat = s_creationMethod.colorFormat;
		OPENGL_COLOR_FORMAT internalColorFormat = s_creationMethod.colorFormat;
		
		//Setup pixel storage and internal color format according to input color format
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
			internalColorFormat = OPENGL_COLOR_FORMAT::RGBA8;
			break;
		case OPENGL_COLOR_FORMAT::R:
			internalColorFormat = colorFormat;
			OpenGL::pixelStorei(OPENGL_ALIGNMENT::UNPACK, 1);
			break;
		case OPENGL_COLOR_FORMAT::RG:
			internalColorFormat = colorFormat;
			OpenGL::pixelStorei(OPENGL_ALIGNMENT::UNPACK, 2);
		default:
			OpenGL::pixelStorei(OPENGL_ALIGNMENT::UNPACK, 4);
		}
				
		//Apply creation method changes
		OpenGL::texParameteri(OPENGL_TEXTURE::_2D, OPENGL_TEXTURE_PARAMETER_NAME::MAG_FILTER, 
			OPENGL_TEXTURE_PARAMETER::LINEAR);
		OPENGL_TEXTURE_PARAMETER mipmapParameter = OPENGL_TEXTURE_PARAMETER::LINEAR;
		
		if (s_creationMethod.generateMipmap)
			mipmapParameter = OPENGL_TEXTURE_PARAMETER::LINEAR_MIPMAP_NEAREST;

		OpenGL::texParameteri(OPENGL_TEXTURE::_2D, OPENGL_TEXTURE_PARAMETER_NAME::MIN_FILTER, 
			mipmapParameter);

		setClamped(s_creationMethod.clampToEdge);

		//Upload texture data
		OpenGL::texImage2D(OPENGL_TEXTURE::_2D, 0, internalColorFormat, width, height, 0, colorFormat, 
			OPENGL_PIXEL_STORAGE::UBYTE, data);

		//Generate mipmaps if necessary
		if (s_creationMethod.generateMipmap) OpenGL::generateMipmap(OPENGL_TEXTURE::_2D);
		
		//update last bit of supplied Texture2D object
		tex->m_width = width;
		tex->m_height = height;

		//clean up
		tex->unbind(0);

		return ERROR_ID::NONE;
	}

	void Texture2D::setCreationMethod(bool generateMipmap, bool clampToEdge, 
		OPENGL_COLOR_FORMAT colorFormat)
	{
		s_creationMethod.generateMipmap = generateMipmap;
		s_creationMethod.clampToEdge = clampToEdge;
		s_creationMethod.colorFormat = colorFormat;
	}

	void Texture2D::destroy(Texture2D * tex)
	{
		ui32 id = tex->m_id;
		OpenGL::deleteTextures(1, &id);
		tex->m_id = 0;
		tex->m_width = 0;
		tex->m_height = 0;
	}

	void Texture2D::setClamped(bool value)
	{
		OPENGL_TEXTURE_PARAMETER p = value ? OPENGL_TEXTURE_PARAMETER::CLAMP_TO_EDGE 
			: OPENGL_TEXTURE_PARAMETER::REPEAT;

		OpenGL::texParameteri(OPENGL_TEXTURE::_2D, OPENGL_TEXTURE_PARAMETER_NAME::WRAP_S, p);
		OpenGL::texParameteri(OPENGL_TEXTURE::_2D, OPENGL_TEXTURE_PARAMETER_NAME::WRAP_T, p);
	}

}