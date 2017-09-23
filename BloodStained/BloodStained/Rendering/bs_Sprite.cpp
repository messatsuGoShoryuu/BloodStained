#include "bs_Sprite.h"

#include <Rendering/bs_Texture2D.h>
#include <Rendering/bs_Shader.h>

namespace bs
{

	Sprite::Sprite()
		:m_orientation(0.0f),
		m_position(Vector2::zero),
		m_scale(Vector2::unit),
		m_texture(nullptr),
		m_shader(nullptr),
		m_color(ColorRGBAf::white),
		m_uvRect(Rectf32(0.0f, 0.0f, 1.0f, 1.0f))
	{
	}

	Sprite::Sprite(const Texture2D * texture, const  Shader * shader)
		:m_orientation(0.0f),
		m_position(Vector2::zero),
		m_scale(Vector2::unit),
		m_texture(texture),
		m_shader(shader),
		m_color(ColorRGBAf::white),
		m_uvRect(Rectf32(0.0f, 0.0f, 1.0f, 1.0f))
	{
	}

	Sprite::Sprite(const Sprite & s)
		:m_orientation(s.m_orientation),
		m_position(s.m_position),
		m_scale(s.m_scale),
		m_texture(s.m_texture),
		m_shader(s.m_shader),
		m_color(s.m_color),
		m_uvRect(s.m_uvRect)
	{
	}

	Sprite::~Sprite()
	{
	}
}
