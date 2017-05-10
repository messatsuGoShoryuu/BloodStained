#include "bs_FontRenderer.h"
#include "../../../Globals/bs_globals.h"

namespace bs
{
	FontRenderer::FontRenderer()
	{

	}

	FontRenderer::~FontRenderer()
	{

	}

	bool	FontRenderer::initialize()
	{
		if (!m_vao.initialize()) return false;
		if (!m_ibo.initialize()) return false;
		if (!m_vbo.initialize()) return false;

		m_vao.bind();
		m_ibo.bind();
		m_vbo.bind();

		m_vao.setAttribPointer<Vertex2D_PUC>(GL_FLOAT, 2, offsetof(Vertex2D_PUC, position), GL_FALSE);
		m_vao.setAttribPointer<Vertex2D_PUC>(GL_FLOAT, 2, offsetof(Vertex2D_PUC, uv), GL_FALSE);
		m_vao.setAttribPointer<Vertex2D_PUC>(GL_FLOAT, 4, offsetof(Vertex2D_PUC, color), GL_FALSE);

		m_vao.unbind();
		m_ibo.unbind();
		m_vbo.unbind();

		return true;
	}

	bool	FontRenderer::shutDown()
	{
		return true;
	}

	void	FontRenderer::render(Camera2D* camera)
	{

	}

	void	FontRenderer::_updateCameraUniforms(Camera2D* camera)
	{

	}

	void	FontRenderer::_draw(Camera2D* camera)
	{

	}

	void	FontRenderer::_uploadData()
	{
		ui32 count = m_strings.count();
		if (count == 0) return;

		Font* font = m_strings[0].font;

		for (ui32 i = 0; i < count; i++)
		{
			if (m_strings[i].font != font)m_batches.add(i);
			_generateVertices(m_strings[i]);
		}

		m_vbo.upload(GL_DYNAMIC_DRAW);
		m_ibo.upload(GL_DYNAMIC_DRAW);
	}

	void	FontRenderer::_generateVertices(const FontRegistry& registry)
	{

	}

	void	FontRenderer::drawString(const char* string, const Vector2& position, const char* font, FONT_ALIGNMENT alignment, ui32 size, ColorRGBA32 color)
	{
		drawString(String(string), position, g_fontManager[font], alignment, size, color);
	}

	void	FontRenderer::drawString(const String& string, const Vector2& position, Font* font, FONT_ALIGNMENT alignment, ui32 size, ColorRGBA32 color)
	{
		ui32 index = m_strings.construct();

		FontRegistry* registry = &m_strings[index];
		registry->string = string;
		registry->position = position;
		registry->font = font;
		registry->alignment = alignment;
		registry->size = size;
		registry->color = color;
	}
}