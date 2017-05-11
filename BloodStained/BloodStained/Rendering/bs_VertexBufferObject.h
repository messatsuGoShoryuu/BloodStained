#ifndef BS_VERTEXBUFFEROBJECT_H
#define BS_VERTEXBUFFEROBJECT_H

#include <GL/glew.h>
#include "../Containers/bs_Array.h"
#include "../Utilities/bs_Error.h"

namespace bs
{
	typedef GLenum VBO_DrawType;
	typedef GLushort IBO_Index;

	class VertexBufferObject
	{
	public:
		//Default constructor.
		VertexBufferObject();
		//Copy constructor.
		VertexBufferObject(const VertexBufferObject& v);
		//Destructor.
		~VertexBufferObject();

		//Upload buffer to OpenGL.
		ERROR_ID	initialize();
		void	clearData();

		inline	ui32 id(){ return (ui32)m_id; }

		inline ui32	 size(){ return m_data.count(); }

		inline	void bind()		{ ::glBindBuffer(GL_ARRAY_BUFFER, m_id); }
		inline	void unbind()	{ ::glBindBuffer(GL_ARRAY_BUFFER, 0); }
		
		template	<class T>	void	addData(const T& data);

		template	<class T>	T*		getData(){ return reinterpret_cast<T*>(&m_data[0]); }

		void upload(VBO_DrawType drawType);

		inline void			shutDown()
		{
			unbind();
			m_data.reset();
		}

	private:
		GLuint	m_id;
		Array<byte>	m_data;
	};

	template<class T>
	void	VertexBufferObject::addData(const T& data)
	{
		const byte* convertedData = reinterpret_cast<const byte*>(&data);
		size_t size = sizeof(T);
		for (ui32 i = 0; i < size; i++)m_data.add(convertedData[i]);
	}


	class VertexArrayObject
	{
	public:
		VertexArrayObject();
		VertexArrayObject(const VertexArrayObject& v);
		~VertexArrayObject();

		inline ui32		id(){ return	(ui32)m_id; }

		inline	void	bind()	{ ::glBindVertexArray(m_id); }
		inline	void	unbind(){ ::glBindVertexArray(0); }

		ERROR_ID initialize();
		

		template <class T>
		void setAttribPointer(GLenum type, i32 count, size_t offset, bool isNormalized);

	private:
		GLuint	m_id;
		GLuint	m_enabledAttribArrays;
	};

	template <class T>
	void	VertexArrayObject::setAttribPointer(GLenum type, i32 count, size_t offset, bool isNormalized)
	{
		ui32 size = sizeof(T);
		::glVertexAttribPointer(m_enabledAttribArrays, count, type, isNormalized, size <= 4? size * count : size, (void*)offset);
		::glEnableVertexAttribArray(m_enabledAttribArrays);		
		m_enabledAttribArrays++;
	}

	
	class IndexBufferObject
	{
	public:
		IndexBufferObject();
		IndexBufferObject(const IndexBufferObject& i);
		~IndexBufferObject();

		inline ui32		id(){ return	(ui32)m_id; }

		inline	void	addData(GLushort data){ m_data.add(data);}

		inline	ui32	size(){ return m_data.count(); }
		inline	ui16*	data(){ return &m_data[0]; }

		ERROR_ID	initialize();

		inline	void	clearData(){ m_data.clear(); }
		void	upload(GLenum drawType);

		inline	void	bind()	{ ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }
		inline	void	unbind(){ ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

		inline void			shutDown()
		{
			unbind();
			m_data.reset();
		}

	private:
		GLuint		m_id;
		Array<GLushort>	m_data;
	};

}

#endif // !BS_VERTEXBUFFEROBJECT_H
