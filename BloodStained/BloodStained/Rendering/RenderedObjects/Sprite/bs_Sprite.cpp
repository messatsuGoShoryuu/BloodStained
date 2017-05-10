#include "bs_Sprite.h"


namespace bs
{
	Sprite::Sprite()
		:m_color(ColorRGBA32::white),
		m_width(1.0f),
		m_height(1.0f),
		m_useParallax(false),
		m_parallaxFactor(1.0),
		m_parallaxOffset(Vector2::zero),
		m_depth(0.0f),
		m_position(Vector2::zero),
		m_orientation(0.0f),
		m_shader(nullptr),
		m_isDirty(true)
	{
		m_uvRect.x = 0.0f;
		m_uvRect.y = 0.0f;
		m_uvRect.w = 1.0f;
		m_uvRect.h = 1.0f;

		_setupVertices();
	}

	Sprite::Sprite(const Sprite& s)
		:m_color(s.m_color),
		m_width(s.m_width),
		m_height(s.m_height),
		m_uvRect(s.m_uvRect),
		m_position(s.m_position),
		m_orientation(s.m_orientation),
		m_normalMap(s.m_normalMap),
		m_texture(s.m_texture),
		m_parallaxFactor(s.m_parallaxFactor),
		m_useParallax(s.m_useParallax),
		m_parallaxOffset(s.m_parallaxOffset),
		m_depth(s.m_depth),
		m_shader(s.m_shader),
		m_isDirty(s.m_isDirty)
	{
		for (ui32 i = 0; i < 4; i++)
		{
			m_vertices[i] = s.m_vertices[i];
		}
	}

	Sprite::~Sprite()
	{

	}

	void Sprite::_setupVertices()
	{
		f32 hw = m_width / 2.0;
		f32 hh = m_height / 2.0;
		m_vertices[0].position.x = -hw;
		m_vertices[0].position.y = hh;
		m_vertices[0].uv.u = m_uvRect.x;
		m_vertices[0].uv.v = m_uvRect.y;
		m_vertices[0].color = m_color;

		m_vertices[1].position.x = hw;
		m_vertices[1].position.y = hh;
		m_vertices[1].uv.u = m_uvRect.x + m_uvRect.w;
		m_vertices[1].uv.v = m_uvRect.y;
		m_vertices[1].color = m_color;

		m_vertices[2].position.x = hw;
		m_vertices[2].position.y = -hh;
		m_vertices[2].uv.u = m_uvRect.x + m_uvRect.w;
		m_vertices[2].uv.v = m_uvRect.y + m_uvRect.h;
		m_vertices[2].color = m_color;

		m_vertices[3].position.x = -hw;
		m_vertices[3].position.y = -hh;
		m_vertices[3].uv.u = m_uvRect.x;
		m_vertices[3].uv.v = m_uvRect.y + m_uvRect.h;
		m_vertices[3].color = m_color;

		for (ui32 i = 0; i < 4; i++)
		{
			Vector2 vertex = m_vertices[i].position;
			m_vertices[i].position.x = vertex.x * math::cos(m_orientation) + vertex.y * math::sin(m_orientation) + m_position.x;
			m_vertices[i].position.y = -vertex.x * math::sin(m_orientation) + vertex.y * math::cos(m_orientation) + m_position.y;
		}

		m_isDirty = false;
	}
}