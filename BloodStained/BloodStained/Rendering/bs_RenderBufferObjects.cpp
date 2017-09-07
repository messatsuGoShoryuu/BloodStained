#include "bs_RenderBufferObjects.h"
#include "bs_OpenGL.h"
#include <Utilities/bs_Error.h>

namespace bs
{
	VertexBufferObject::VertexBufferObject()
		:m_id(0)
	{
	}
	VertexBufferObject::VertexBufferObject(const VertexBufferObject & v)
		:m_id(v.m_id)
	{
	}
	VertexBufferObject::~VertexBufferObject()
	{
		if (m_id != 0) shutDown();
	}
	ERROR_ID VertexBufferObject::initialize()
	{
		if (m_id != 0) shutDown();
		OpenGL::genBuffers(1, &m_id);
		if (m_id == 0) return ERROR_ID::VBO_INIT_FAIL;
		return ERROR_ID::NONE;
	}
	ERROR_ID VertexBufferObject::shutDown()
	{
		OpenGL::deleteBuffers(1, &m_id);
		m_id = 0;
		return ERROR_ID::NONE;
	}
	void VertexBufferObject::bind()
	{
		OpenGL::bindBuffer(OPENGL_BUFFER_TYPE::ARRAY, m_id);
	}
	void VertexBufferObject::unbind()
	{
		OpenGL::bindBuffer(OPENGL_BUFFER_TYPE::ARRAY, 0);
	}

	void VertexBufferObject::upload(byte* pointer, ui32 size)
	{
		OpenGL::bufferData(OPENGL_BUFFER_TYPE::ARRAY, size, pointer, OPENGL_BUFFER_STORAGE::STATIC_DRAW);
	}

	VertexArrayObject::VertexArrayObject()
		:m_id(0),
		m_enabledAttribArrays(0)
	{
	}

	VertexArrayObject::VertexArrayObject(const VertexArrayObject & o)
		:m_id(o.m_id),
		m_enabledAttribArrays(o.m_enabledAttribArrays)
	{
	}

	VertexArrayObject::~VertexArrayObject()
	{
	}

	ERROR_ID VertexArrayObject::initializeMultiple(VertexArrayObject * v, ui32 count)
	{
		if (count > 8) return ERROR_ID::VAO_INIT_FAIL;
		//Set max list VAO creation to 8, (arbitrary)
		ui32 idList[8];
		
		OpenGL::genVertexArrays(count, idList);
		for (ui32 i = 0; i < count; i++)
		{
			v[i].m_id = idList[i];
		}

		return ERROR_ID::NONE;
	}

	ERROR_ID VertexArrayObject::shutDownMultiple(VertexArrayObject * v, ui32 count)
	{
		if (count > 8) return ERROR_ID::VAO_INIT_FAIL;

		ui32 idList[8];
		for (ui32 i = 0; i < count; i++)
		{
			idList[i] = v[i].m_id;
			for (ui32 i = 0; i < v[i].m_enabledAttribArrays; i++)
				OpenGL::disableVertexAttribArray(i);
			v[i].m_enabledAttribArrays = 0;
		}

		OpenGL::deleteVertexArrays(count, idList);
		return ERROR_ID::NONE;
	}

	ERROR_ID VertexArrayObject::initialize()
	{
		if (m_id != 0) shutDown();
		OpenGL::genVertexArrays(1, &m_id);
		if (m_id != 0) return ERROR_ID::VAO_INIT_FAIL;
		return ERROR_ID::NONE;
	}

	ERROR_ID VertexArrayObject::shutDown()
	{
		for (ui32 i = 0; i < m_enabledAttribArrays; i++)
			OpenGL::disableVertexAttribArray(i);
		OpenGL::deleteVertexArrays(1, &m_id);
		m_id = 0;
		m_enabledAttribArrays = 0;
		return ERROR_ID::NONE;
	}

	void VertexArrayObject::bind()
	{
		OpenGL::bindVertexArray(m_id);
	}

	void VertexArrayObject::unbind()
	{
		OpenGL::bindVertexArray(0);
	}
	void VertexArrayObject::setAttribPointer(ptrsize sizeOf, ui32 count, 
		const void* offset, OPENGL_TYPE type, bool isNormalized)
	{
		OpenGL::enableVertexAttribArray(m_enabledAttribArrays);
		OpenGL::vertexAttribPointer(m_enabledAttribArrays, count, type, isNormalized, sizeOf, offset);		
		m_enabledAttribArrays++;
	}
}