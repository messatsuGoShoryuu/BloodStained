#include "bs_QuadRenderer.h"
#include <Utilities/bs_Error.h>
#include <Rendering/bs_Camera2D.h>
#include <Rendering/bs_Camera3D.h>
#include <Rendering/bs_Shader.h>

namespace bs
{
	QuadRenderer::QuadRenderer()
		:m_stackAllocator(512 * BS_MEGABYTE,true)
	{
	}

	QuadRenderer::~QuadRenderer()
	{
	}

	ERROR_ID QuadRenderer::initialize()
	{
		m_stackAllocator.initialize();

		ERROR_ID err = m_vbo.initialize();
		if (err != ERROR_ID::NONE) return err;

		err = m_ebo.initialize();
		if (err != ERROR_ID::NONE) return err;

		err = _initVaos();
		if (err != ERROR_ID::NONE) return err;

		return ERROR_ID::NONE;
	}

	ERROR_ID QuadRenderer::shutDown()
	{
		ERROR_ID err = m_vbo.shutDown();
		if (err != ERROR_ID::NONE) return err;

		err = m_ebo.shutDown();
		if (err != ERROR_ID::NONE) return err;

		err = VertexArrayObject::shutDownMultiple(&m_vaos[0], m_vaos.count());

		return ERROR_ID();
	}

	void QuadRenderer::render(const Array<Camera*> cameras)
	{

		m_vbo.bind();
		m_ebo.bind();

		if (m_stackAllocator.size() > 0)
		{
			OpenGL::bufferData(OPENGL_BUFFER_TYPE::ARRAY, m_stackAllocator.size(),
				m_stackAllocator.base(), OPENGL_BUFFER_STORAGE::DYNAMIC_DRAW);
			m_ebo.upload(OPENGL_BUFFER_STORAGE::DYNAMIC_DRAW);
		}

		ui32 batchCount = m_batches.count();
		ui32 vaoID = 0;
		ui32 lastVaoID = 0xFFFFFFFF;
		const	Shader* lastShader = nullptr;
		const	Texture2D* lastTexture = nullptr;

		ptrsize lastIndex = 0;

		for (ui32 i = 0; i < batchCount; i++)
		{
			vaoID = (ui32)m_batches[i].type;
			if (m_batches[i].shader && (m_batches[i].shader != lastShader || i == 0)) m_batches[i].shader->bind();
			else if (!m_batches[i].shader && lastShader) lastShader->unbind();
			if (m_batches[i].texture && (m_batches[i].texture != lastTexture  || i == 0)) m_batches[i].texture->bind(0);
			else if (!m_batches[i].texture && lastTexture) lastTexture->unbind(0);
			if(vaoID != lastVaoID || i == 0) m_vaos[vaoID].bind();

			i32 textureNo = 0;

			
			if (m_batches[i].shader)
			{
				_updateCameraUniforms(cameras[0], m_batches[i].shader);
				OpenGL::uniform(m_batches[i].shader->id(), "textureContent", SHADER_ATTRIB_TYPE::INT, &textureNo, false);
			}
			
			OpenGL::drawElements(OPENGL_PRIMITIVE::TRIANGLES, m_batches[i].count * 6, OPENGL_TYPE::USHORT,
				m_ebo.data() + lastIndex);

			lastVaoID = vaoID;
			lastShader = m_batches[i].shader;
			lastIndex += m_batches[i].count * 6;
			lastTexture = m_batches[i].texture;
		}

		m_stackAllocator.deallocateWhole();
		m_batches.clear();

		m_vaos[vaoID].unbind();
		m_vbo.unbind();
		m_ebo.reset();
	}

	void QuadRenderer::_updateCameraUniforms(Camera * camera,const  Shader * shader)
	{
		if (camera->isDirty())
		{
			f32 m[16];
			if ((shader->matrixFlags() & SHADER_MATRIX_FLAGS::P) == SHADER_MATRIX_FLAGS::P)
			{
				camera->projection().toFloatArray(m);
				OpenGL::uniform(shader->id(), "projection", SHADER_ATTRIB_TYPE::MATRIX4, m, false);
			}
			if ((shader->matrixFlags() & SHADER_MATRIX_FLAGS::V) == SHADER_MATRIX_FLAGS::V)
			{
				camera->view().toFloatArray(m);
				OpenGL::uniform(shader->id(), "view", SHADER_ATTRIB_TYPE::MATRIX4, m, false);
			}
		}
	}

	bool QuadRenderer::_shouldBatchChange(const QuadBatch * current, VERTEX_TYPE type,
		const Shader* shader, const Texture2D* texture)
	{
		return current->shader != shader || current->type != type || current->texture != texture;
	}

	void QuadRenderer::_createBatch(void * startPointer, VERTEX_TYPE type, const Shader * shader, const  Texture2D * texture)
	{
		ui32 index = m_batches.construct();
		m_batches[index].startPointer = startPointer;
		m_batches[index].shader = shader;
		m_batches[index].type = type;
		m_batches[index].texture = texture;
		m_batches[index].count = 0;
		m_batches[index].endPointer = startPointer;
	}
	ERROR_ID QuadRenderer::_initVaos()
	{
		m_vaos.construct();
		m_vaos.construct();
		m_vaos.construct();

		ERROR_ID err = VertexArrayObject::initializeMultiple(&m_vaos[0], m_vaos.count());
		if (err != ERROR_ID::NONE) return err;

		m_vbo.bind();
		m_ebo.bind();

		//Init 2D position, uv, color
		ui32 index = (int)VERTEX_TYPE::PUC_2D;
		m_vaos[index].bind();
		m_vaos[index].setAttribPointer(sizeof(Vertex2D_PUC), 2, 
			(void*)offsetof(Vertex2D_PUC, position), OPENGL_TYPE::FLOAT, false);
		m_vaos[index].setAttribPointer(sizeof(Vertex2D_PUC), 2, 
			(void*)offsetof(Vertex2D_PUC, uv), OPENGL_TYPE::FLOAT, false);
		m_vaos[index].setAttribPointer(sizeof(Vertex2D_PUC), 4,
			(void*)offsetof(Vertex2D_PUC, color), OPENGL_TYPE::FLOAT, true);

		//Init 3D position, uv
		index = (int)VERTEX_TYPE::PU_3D;
		m_vaos[index].bind();
		m_vaos[index].setAttribPointer(sizeof(Vertex2D_PUC), 3,
			(void*)offsetof(Vertex2D_PUC, position), OPENGL_TYPE::FLOAT, false);
		m_vaos[index].setAttribPointer(sizeof(Vertex2D_PUC), 2,
			(void*)offsetof(Vertex2D_PUC, uv), OPENGL_TYPE::FLOAT, false);

		index = (int)VERTEX_TYPE::PC_3D;
		//Init 3D position, color
		m_vaos[index].bind();
		m_vaos[index].setAttribPointer(sizeof(Vertex2D_PUC), 3,
			(void*)offsetof(Vertex2D_PUC, position), OPENGL_TYPE::FLOAT, false);
		m_vaos[index].setAttribPointer(sizeof(Vertex2D_PUC), 4,
			(void*)offsetof(Vertex2D_PUC, uv), OPENGL_TYPE::FLOAT, false);

		m_vaos[index].unbind();

		m_vbo.unbind();
		
		return ERROR_ID::NONE;
	}
}