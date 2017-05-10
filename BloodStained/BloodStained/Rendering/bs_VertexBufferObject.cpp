#include "bs_VertexBufferObject.h"

namespace bs
{
	VertexBufferObject::VertexBufferObject()
		:m_id(0)
	{

	}

	VertexBufferObject::VertexBufferObject(const VertexBufferObject& v)
		:m_id(v.m_id),
		m_data(v.m_data)
	{

	}

	VertexBufferObject::~VertexBufferObject()
	{
		if(m_id != 0) ::glDeleteBuffers(1, &m_id);
	}

	bool	VertexBufferObject::initialize()
	{
		::glGenBuffers(1, &m_id);
		if (m_id == 0) return false;
		return true;
	}

	void	VertexBufferObject::clearData()
	{
		m_data.clear();
	}

	void	VertexBufferObject::upload(VBO_DrawType drawType)
	{
		if (m_id != 0) ::glBufferData(GL_ARRAY_BUFFER, m_data.count(), &m_data[0], drawType);
	}

	VertexArrayObject::VertexArrayObject() 
		: m_id(0), 
		m_enabledAttribArrays(0)
	{

	}

	VertexArrayObject::VertexArrayObject(const VertexArrayObject& v) 
		: m_id(v.m_id), 
		m_enabledAttribArrays(v.m_enabledAttribArrays)
	{

	}

	VertexArrayObject::~VertexArrayObject()
	{
		if (m_id != 0) ::glDeleteVertexArrays(1, &m_id);
	}

	bool VertexArrayObject::initialize()
	{
		if (m_id == 0) ::glGenVertexArrays(1, &m_id);
		if (m_id == 0) return false;
		return true;
	}




	IndexBufferObject::IndexBufferObject()
		:m_id(0)
	{

	}

	IndexBufferObject::IndexBufferObject(const IndexBufferObject& i)
		: m_id(i.m_id),
		m_data(i.m_data)
	{

	}

	IndexBufferObject::~IndexBufferObject()
	{
		if (m_id != 0) ::glDeleteBuffers(1, &m_id);
	}

	bool	IndexBufferObject::initialize()
	{
		if (m_id == 0) ::glGenBuffers(1, &m_id);
		if (m_id == 0) return false;
		return true;
	}

	void IndexBufferObject::upload(GLenum drawType)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_data.count() * sizeof(GLushort), &m_data[0], drawType);
	}

}