#ifndef _BS_RENDERBUFFEROBJECTS_H_
#define _BS_RENDERBUFFEROBJECTS_H_
#include <Utilities/bs_types.h>

namespace bs
{
	enum class ERROR_ID;

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
		
		ui32	id();

		void	upload(byte* pointer, ui32 size);

	private:
		ui32 m_id;
		
	};
}

#endif // !_BS_RENDERBUFFEROBJECTS_H_