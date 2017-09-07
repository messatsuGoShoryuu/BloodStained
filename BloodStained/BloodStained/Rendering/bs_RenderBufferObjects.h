#ifndef _BS_RENDERBUFFEROBJECTS_H_
#define _BS_RENDERBUFFEROBJECTS_H_
#include <Utilities/bs_types.h>

namespace bs
{
	enum class ERROR_ID;

	enum class OPENGL_TYPE;

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
		void	upload(byte* pointer, ui32 size);

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
}

#endif // !_BS_RENDERBUFFEROBJECTS_H_