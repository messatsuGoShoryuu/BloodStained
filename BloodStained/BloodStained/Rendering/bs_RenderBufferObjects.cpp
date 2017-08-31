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
	ui32 VertexBufferObject::id()
	{
		return m_id;
	}
	void VertexBufferObject::upload(byte* pointer, ui32 size)
	{
		OpenGL::bufferData(OPENGL_BUFFER_TYPE::ARRAY, size, pointer, OPENGL_BUFFER_STORAGE::STATIC_DRAW);
	}
}