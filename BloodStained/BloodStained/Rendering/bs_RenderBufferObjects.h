#ifndef _BS_RENDERBUFFEROBJECTS_H_
#define _BS_RENDERBUFFEROBJECTS_H_
#include <Utilities/bs_types.h>
#include <Containers/bs_Array.h>
namespace bs
{
	enum class ERROR_ID;

	enum class OPENGL_TYPE;
	enum class OPENGL_BUFFER_STORAGE;

	class VertexBufferObject
	{
	public:
		VertexBufferObject();
		VertexBufferObject(const VertexBufferObject& v);
		~VertexBufferObject();

	public:
		ERROR_ID initialize();
		ERROR_ID shutDown();

		void	bind();
		void	unbind();
		
		inline	ui32	id() { return m_id; }

		//Upload using glBufferData
		void	upload(byte* pointer, ui32 size, OPENGL_BUFFER_STORAGE storage);

	private:
		ui32 m_id;
		
	};

	class VertexArrayObject
	{
	public:
		VertexArrayObject();
		VertexArrayObject(const VertexArrayObject& o);
		~VertexArrayObject();

	public:
		static ERROR_ID initializeMultiple(VertexArrayObject* v, ui32 count);
		static ERROR_ID shutDownMultiple(VertexArrayObject* v, ui32 count);
		ERROR_ID initialize();
		ERROR_ID shutDown();

		inline	ui32	id() { return m_id; }

		void	bind();
		void	unbind();

		void	setAttribPointer(ptrsize sizeOf, ui32 count, 
			const void* offset, OPENGL_TYPE type, bool isNormalized);

	private:
		ui32 m_id;
		ui32 m_enabledAttribArrays;
	};

	class ElementBufferObject
	{
	public:
		ElementBufferObject();
		ElementBufferObject(const ElementBufferObject& e);
		~ElementBufferObject();

	public:
		ERROR_ID initialize();
		ERROR_ID shutDown();

		inline	ui32	id() { return m_id; }

		inline ui32 count() { return m_data.count(); }
		inline void add(ui16 index) { m_data.add(index); }

		void upload(OPENGL_BUFFER_STORAGE storage);
		inline	void reset() { m_data.clear(); }
		ui16*	data() { return &m_data[0]; }

		void	bind();
		void	unbind();
		
	private:
		ui32 m_id;
		Array<ui16>	m_data;
	};
}

#endif // !_BS_RENDERBUFFEROBJECTS_H_