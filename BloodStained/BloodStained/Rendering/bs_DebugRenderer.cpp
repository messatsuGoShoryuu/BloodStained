#include "bs_DebugRenderer.h"
#include "bs_Vertex.h"
#include <Math/bs_Vector.h>
#include <Math/bs_math.h>
#include "bs_Camera.h"
#include "bs_Shader.h"
#include "bs_ShaderManager.h"
#include "bs_OpenGL.h"
#include "bs_Color.h"
#include <Utilities/bs_String.h>

#include <Utilities/bs_Error.h>

namespace bs
{
	DebugRenderer::DebugRenderer():m_stackAllocator(64 * BS_MEGABYTE, true),
		m_vertexCount(0)
	{
	}

	DebugRenderer::DebugRenderer(const DebugRenderer & r)
	{
	}

	DebugRenderer::~DebugRenderer()
	{
	}

	ERROR_ID DebugRenderer::initialize()
	{
		m_stackAllocator.initialize();

		ERROR_ID err = m_vbo.initialize();
		if (err != ERROR_ID::NONE) return err;

		err = m_ebo.initialize();
		if (err != ERROR_ID::NONE) return err;

		err = m_vao.initialize();
		if (err != ERROR_ID::NONE) return err;

		m_vbo.bind();
		m_ebo.bind();

		m_vao.bind();
		m_vao.setAttribPointer(sizeof(Vertex2D_PC), 2,
			(void*)offsetof(Vertex2D_PC, position), OPENGL_TYPE::FLOAT, false);
		m_vao.setAttribPointer(sizeof(Vertex2D_PC), 4,
			(void*)offsetof(Vertex2D_PC, color), OPENGL_TYPE::FLOAT, true);
		m_vao.unbind();
		m_vbo.unbind();

		m_shader = ShaderManager::getShader("DefaultDebug/DefaultDebug");
		if (m_shader == nullptr) return ERROR_ID::SHADER_NOT_FOUND;

		return ERROR_ID::NONE;
	}

	ERROR_ID DebugRenderer::shutDown()
	{
		ERROR_ID err = m_vbo.shutDown();
		if (err != ERROR_ID::NONE) return err;

		err = m_ebo.shutDown();
		if (err != ERROR_ID::NONE) return err;

		err = m_vao.shutDown();
		if (err != ERROR_ID::NONE) return err;

		return ERROR_ID::NONE;
	}
	void DebugRenderer::drawShape(Vector2 * vertices, ui16 count, const ColorRGBAf& color)
	{
		Vertex2D_PC* v = (Vertex2D_PC*)m_stackAllocator.allocate(sizeof(Vertex2D_PC) * count, alignof(Vertex2D_PC));
		for (ui32 i = 0; i < count; i++)
		{
			v[i].position = vertices[i];
			v[i].color = color;
		}

		ui16 offset = m_vertexCount;
		for (ui32 i = 0; i < count; i++)
		{
			m_ebo.add(offset + i);
			m_ebo.add(offset + ((i + 1) % count));
		}

		m_vertexCount += count;
	}

	void DebugRenderer::drawCircle(const Vector2 & center, f32 radius, ui16 resolution, const ColorRGBAf & color)
	{
		f32 a = (BS_PI*2.0f) / (f32)resolution;

		Vertex2D_PC* v = (Vertex2D_PC*)m_stackAllocator.allocate(sizeof(Vertex2D_PC)
			* resolution, alignof(Vertex2D_PC));

		for (ui32 i = 0; i < resolution; i++)
		{
			f32 angle = a*(f32)i;
			v[i].position.x = center.x + math::cos(angle) * radius;
			v[i].position.y = center.y + math::sin(angle) * radius;
			v[i].color = color;
		}

		ui16 offset = m_vertexCount;
		for (ui32 i = 0; i < resolution; i++)
		{
			m_ebo.add(offset + i);
			m_ebo.add(offset + ((i + 1) % resolution));
		}

		m_vertexCount += resolution;
	}

	void DebugRenderer::drawLine(const Vector2 & from, const Vector2 & to, const ColorRGBAf & color)
	{
		Vertex2D_PC* v = (Vertex2D_PC*)m_stackAllocator.allocate(sizeof(Vertex2D_PC) * 2, alignof(Vertex2D_PC));
		v[0].position = from;
		v[1].position = to;

		v[0].color = color;
		v[1].color = color;

		ui16 offset = m_vertexCount;
		m_ebo.add(offset);
		m_ebo.add(offset + 1);
		

		m_vertexCount += 2;
	}

	void DebugRenderer::render(const Array<Camera*>& cameras)
	{
		m_vbo.bind();
		m_ebo.bind();
		m_shader->bind();

		if (m_stackAllocator.size() > 0)
		{
			OpenGL::bufferData(OPENGL_BUFFER_TYPE::ARRAY, m_stackAllocator.size(),
				m_stackAllocator.base(), OPENGL_BUFFER_STORAGE::DYNAMIC_DRAW);
			m_ebo.upload(OPENGL_BUFFER_STORAGE::DYNAMIC_DRAW);
		}

		if (m_shader)
			_updateCameraUniforms(cameras[0]);

		m_vao.bind();

		OpenGL::drawElements(OPENGL_PRIMITIVE::LINES, m_ebo.count(), OPENGL_TYPE::USHORT,
			m_ebo.data());

		m_stackAllocator.deallocateWhole();
		

		m_vao.unbind();
		m_vbo.unbind();
		m_ebo.reset();
		m_vertexCount = 0;
	}
	void DebugRenderer::_updateCameraUniforms(Camera * camera)
	{
		if (camera->isDirty())
		{
			f32 m[16];
			camera->projection().toFloatArray(m);
			OpenGL::uniform(m_shader->id(), "projection", SHADER_ATTRIB_TYPE::MATRIX4, m, false);
			camera->view().toFloatArray(m);
			OpenGL::uniform(m_shader->id(), "view", SHADER_ATTRIB_TYPE::MATRIX4, m, false);
		}
	}
}