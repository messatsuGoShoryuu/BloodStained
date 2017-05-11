#include "../../../Globals/bs_globals.h"
#include "../../bs_Camera2D.h" 
#include "../../bs_Vertex.h"
#include "../../../Math/bs_Vector.h"

namespace bs
{
	DebugRenderer::DebugRenderer()
		:m_vertexCount(0)
	{

	}

	DebugRenderer::~DebugRenderer()
	{

	}

	ERROR_ID	DebugRenderer::initialize()
	{
		m_shader = &g_shaderManager.getShaderMap()["DebugDrawShader"];
		
		ERROR_ID err = ERROR_ID::NONE;

		err = m_vao.initialize();
		if (err != ERROR_ID::NONE) return Error::fatalError(err, "DebugRenderer Vertex Array Object initialization failed");
		err = m_ibo.initialize();
		if (err != ERROR_ID::NONE) return Error::fatalError(err, "DebugRenderer Index Buffer Object initialization failed");
		err = m_vbo.initialize();
		if (err != ERROR_ID::NONE) return Error::fatalError(err, "DebugRenderer Vertex Buffer Object initialization failed");

		m_vao.bind();
		m_ibo.bind();
		m_vbo.bind();

		m_vao.setAttribPointer<Vertex3D_PC>(GL_FLOAT, 3, offsetof(Vertex3D_PC, position), false);
		m_vao.setAttribPointer<Vertex3D_PC>(GL_FLOAT, 4, offsetof(Vertex3D_PC, color), false);

		m_vao.unbind();
		m_ibo.unbind();
		m_vbo.unbind();

		return ERROR_ID::NONE;
	}

	ERROR_ID	DebugRenderer::shutDown()
	{
		m_vbo.shutDown();
		m_ibo.shutDown();
		return ERROR_ID::NONE;
	}

	void	DebugRenderer::render(Camera2D* camera)
	{
		//Early out if no data to process
		if (m_vertexCount == 0) return;

		//Bind the shader
		m_shader->bind();
		
		//Bind buffer objects
		m_vbo.bind();
		m_ibo.bind();

		//Upload to GL
		_uploadData();

		//Bind array attribs
		m_vao.bind();

		//Update uniforms
		_updateCameraUniforms(camera);

		//Draw call 
		glDrawElements(GL_LINES, m_ibo.size(), GL_UNSIGNED_SHORT, NULL);

		//Cleanup
		m_vao.unbind();

		m_vbo.clearData();
		m_ibo.clearData();

		m_shader->unbind();
		m_vertexCount = 0;
	}

	void DebugRenderer::drawShape(Vector3* vertices, ui32 vertexCount, const ColorRGBA32& color)
	{
		Vertex3D_PC	vertex;

		//Each vertex share the same color.
		vertex.color = color;

		//Add positions to vbo
		for (ui32 i = 0; i < vertexCount; i++)
		{
			vertex.position = vertices[i];
			m_vbo.addData(vertex);
		}

		//Add each pair to ibo
		for (ui32 i = 1; i < vertexCount; i++)
		{
			m_ibo.addData(m_vertexCount + i - 1);
			m_ibo.addData(m_vertexCount + i);
		}

		m_ibo.addData(m_vertexCount + vertexCount - 1);
		m_ibo.addData(m_vertexCount);

		m_vertexCount += vertexCount;
	}

	void DebugRenderer::drawLine(const Vector3& begin, const Vector3& end, const ColorRGBA32& color)
	{
		Vertex3D_PC vertex;
		//Create first vertex
		vertex.position = begin;
		vertex.color = color;

		//Add data to vbo
		m_vbo.addData(vertex);

		//Second vertex only changes by position
		vertex.position = end;
		m_vbo.addData(vertex);

		//Add indices
		m_ibo.addData(m_vertexCount);
		m_ibo.addData(m_vertexCount + 1);

		//Update vertex count
		m_vertexCount += 2;
	}

	void DebugRenderer::_uploadData()
	{
		m_vbo.upload(GL_DYNAMIC_DRAW);
		m_ibo.upload(GL_DYNAMIC_DRAW);
	}

	void	DebugRenderer::_updateCameraUniforms(Camera2D* camera)
	{
		m_shader->beginScope();
		m_shader->uploadUniform((void*)&(camera->view()));
		m_shader->uploadUniform((void*)&(camera->projection()));
	}
}