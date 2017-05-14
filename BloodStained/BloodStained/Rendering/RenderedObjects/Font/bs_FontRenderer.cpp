#include "bs_FontRenderer.h"
#include "../../../Globals/bs_globals.h"
#include "../../bs_Camera2D.h"
#include "../../../Math/bs_Vector.h"
#include "../../bs_Vertex.h"

namespace bs
{
	FontRenderer::FontRenderer()
	{

	}

	FontRenderer::~FontRenderer()
	{

	}

	ERROR_ID	FontRenderer::initialize()
	{
		ERROR_ID err = ERROR_ID::NONE;

		err = m_vao.initialize();
		if(err != ERROR_ID::NONE) return Error::fatalError(err,"FontRenderer Vertex Array Object initialization failed");
		err = m_ibo.initialize();
		if (err != ERROR_ID::NONE) return Error::fatalError(err, "FontRenderer Index Buffer Object initialization failed");
		err = m_vbo.initialize();
		if (err != ERROR_ID::NONE) return Error::fatalError(err, "FontRenderer Vertex Buffer Object initialization failed");

		m_vao.bind();
		m_ibo.bind();
		m_vbo.bind();

		m_vao.setAttribPointer<Vertex2D_PUC>(GL_FLOAT, 2, offsetof(Vertex2D_PUC, position), GL_FALSE);
		m_vao.setAttribPointer<Vertex2D_PUC>(GL_FLOAT, 2, offsetof(Vertex2D_PUC, uv), GL_FALSE);
		m_vao.setAttribPointer<Vertex2D_PUC>(GL_FLOAT, 4, offsetof(Vertex2D_PUC, color), GL_FALSE);

		m_vao.unbind();
		m_ibo.unbind();
		m_vbo.unbind();

		return ERROR_ID::NONE;
	}

	void	FontRenderer::setShader(Shader* shader)
	{
		m_shader = shader;
	}

	ERROR_ID	FontRenderer::shutDown()
	{
		return ERROR_ID::NONE;
	}

	void	FontRenderer::render(Camera2D* camera)
	{
		//Bind the big vertex buffer object
		m_vbo.bind();
		//Bind the big index buffer object
		m_ibo.bind();

		//GL buffer data
		_uploadData();

		//Nothing more to do with the vbo
		m_vbo.unbind();

		m_shader->bind();
		//We need vertex array pointers to specify how vertices are drawn
		m_vao.bind();

		//Draw with current camera.
		_draw(camera);

		//Cleanup
		m_shader->unbind();
		m_vao.unbind();
		m_ibo.clearData();
		m_vbo.clearData();
	}

	void	FontRenderer::_updateCameraUniforms(Camera2D* camera)
	{
		if (!camera) return; 
		m_shader->beginScope();
		m_shader->uploadUniform((void*)&camera->projection());
		m_shader->uploadUniform(0);
	}

	void	FontRenderer::_draw(Camera2D* camera)
	{
		if (!m_shader) return;

		ui32 elementCount = 0;
		ui32 totalElementCount = 0;

		ui32 count = m_strings.count();
		for (ui32 i = 0; i < count; i++)
		{
			if (i > 0)
			{
				if (m_strings[i].font != m_strings[i - 1].font)
				{
					//Upload uniform data to the shader
					_updateCameraUniforms(camera);

					//Make draw call (index buffer object)
					glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_SHORT, (void*)(totalElementCount * sizeof(GLushort)));

					totalElementCount += elementCount;
					elementCount = 0;

					m_strings[i - 1].font->texture().unbind();
					m_strings[i].font->texture().bind();
				}
			}
			else m_strings[i].font->texture().bind();
			elementCount += 6;
		}

		m_shader->bind();
		m_shader->unbind();
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
		//Pen position (starts at registry position)
		Vector2 pen;
		pen = registry.position;

		ui32 count = registry.string.length();

		//Empty glyph struct
		FontGlyph glyph;

		//Quad vertices
		Vertex2D_PUC tl;	//top left
		Vertex2D_PUC tr;	//top right
		Vertex2D_PUC br;	//bottom right
		Vertex2D_PUC bl;	//bottom left

		//Iterate over characters of the string.
		for (ui32 i = 0; i < count; i++)
		{
			//Fetch glyph
			glyph = registry.font->getGlyph((ui16)registry.string[i]);

			//Glyph clip bounds
			ui16 t = glyph.textureY;						//top 
			ui16 b = glyph.textureY + glyph.textureHeight;	//bottom
			ui16 l = glyph.textureX;						//left 
			ui16 r = glyph.textureX + glyph.textureWidth;	//right

			//Glyph UV coordinates
			f32 t_uv = (f32)t / (f32)glyph.textureHeight;
			f32 b_uv = (f32)b / (f32)glyph.textureHeight;
			f32 l_uv = (f32)l / (f32)glyph.textureWidth;
			f32 r_uv = (f32)r / (f32)glyph.textureWidth;

			f32 hh = (glyph.textureHeight * g_screen.height()) / 2.0f;	//Half width
			f32 hw = (glyph.textureWidth * g_screen.height()) / 2.0f;	//Half height


			//Store data into vertex struct
			tl.uv.u = l_uv;
			tl.uv.v = t_uv;

			tr.uv.u = r_uv;
			tr.uv.v = t_uv;

			br.uv.u = r_uv;
			br.uv.v = b_uv;
			
			bl.uv.u = l_uv;
			bl.uv.v = b_uv;

			tl.color = registry.color;
			tr.color = registry.color;
			bl.color = registry.color;
			br.color = registry.color;

			//The position of the quad is relative to the pen.
			Vector2 position;
			position.x = registry.position.x + pen.x + glyph.bearingX + glyph.width / 2.0f;
			position.y = registry.position.y + pen.y + glyph.bearingY - glyph.height / 2.0f;

			//Upload vertex positions
			tl.position.x = position.x - hw;
			tl.position.y = position.y + hw;

			tr.position.x = position.x + hw;
			tr.position.y = position.y + hw;

			br.position.x = position.x + hw;
			br.position.y = position.y - hw;

			bl.position.x = position.x - hw;
			bl.position.y = position.y - hw;

			//Upload actual vertex data.
			m_vbo.addData(tl);
			m_vbo.addData(tr);
			m_vbo.addData(br);
			m_vbo.addData(bl);

			//Keep track of indices
			ui16 addedCount = i * 6;

			//Add indices

			//First triangle.
			m_ibo.addData(addedCount);
			m_ibo.addData(addedCount + 1);
			m_ibo.addData(addedCount + 2);

			//Second triangle.
			m_ibo.addData(addedCount + 2);
			m_ibo.addData(addedCount + 3);
			m_ibo.addData(addedCount);

			pen.x += glyph.horizontalAdvance;

		}
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