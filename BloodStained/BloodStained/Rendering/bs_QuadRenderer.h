#ifndef _BS_QUADRENDERER_H_
#define	_BS_QUADRENDERER_H_

#include <Allocator/bs_StackAllocator.h>
#include <Containers/bs_Array.h>
#include "bs_Primitive.h"
#include "bs_Vertex.h"
#include "bs_Shader.h"
#include "bs_Texture2D.h"

namespace bs
{
	class Camera;
	enum class ERROR_ID;

	struct QuadBatch
	{
		void*	startPointer;
		void*	endPointer;
		Shader*	shader;
		Texture2D* texture;
		VERTEX_TYPE type;
	};

	class QuadRenderer
	{
	public:
		QuadRenderer();
		~QuadRenderer();

		ERROR_ID initialize();
		ERROR_ID shutDown();

	public:
		void	render(const Array<Camera*> cameras);

	
		//TODO: add material support
		/*
		Adds quads to the stack allocator. This function is specialized depending on the vertex type.
		a VERTEX_TYPE enum will determine which type of vertex we are using. 
		*/
		template<class T> 
		T*	add(ui32 count, Shader* shader, Texture2D* texture){}

		template<>
		Quad<Vertex2D_PUC>*	add<Quad<Vertex2D_PUC>>(ui32 count, Shader* shader, Texture2D* texture);

		template<>
		Quad<Vertex3D_PC>*	add<Quad<Vertex3D_PC>>(ui32 count, Shader* shader, Texture2D* texture);

		template<>
		Quad<Vertex3D_PU>*	add<Quad<Vertex3D_PU>>(ui32 count, Shader* shade, Texture2D* texturer);

	private:
		template <class T> 
		T* _internalAdd(ui32 count, Shader* shader, Texture2D* texture, VERTEX_TYPE type);

		bool	_shouldBatchChange(const QuadBatch* current, VERTEX_TYPE type, ui32 shaderID, ui32 textureID);
		void	_createBatch(void* startPointer, VERTEX_TYPE type, Shader* shader, Texture2D* texture);

	private:
		StackAllocator		m_stackAllocator;
		Array<QuadBatch>	m_batches;
	};

	template<class T>
	T* QuadRenderer::_internalAdd(ui32 count, Shader* shader, Texture2D* texture, VERTEX_TYPE type)
	{
		T* pointer = (T*)m_stackAllocator.getFrame();
		m_stackAllocator.allocate(sizeof(Vertex2D_PUC) * count, __alignof(Vertex2D_PUC));

		QuadBatch* currentBatch = nullptr;
		if (m_batches.count() > 0)
			currentBatch = &m_batches.last();

		if (_shouldBatchChange(currentBatch, type, shader->id(),texture->id()))
		{
			currentBatch->endPointer = pointer;
			_createBatch(pointer, type, shader, texture);
		}
	}

	template<>
	Quad<Vertex2D_PUC>*	QuadRenderer::add<Quad<Vertex2D_PUC>>(ui32 count, Shader* shader, Texture2D* texture)
	{
		return _internalAdd<Quad<Vertex2D_PUC>>(count, shader, texture, VERTEX_TYPE::PUC_2D);
	}

	template<>
	Quad<Vertex3D_PC>*	QuadRenderer::add<Quad<Vertex3D_PC>>(ui32 count, Shader* shader, Texture2D* texture)
	{
		return _internalAdd<Quad<Vertex3D_PC>>(count, shader, texture,VERTEX_TYPE::PC_3D);
	}

	template<>
	Quad<Vertex3D_PU>*	QuadRenderer::add<Quad<Vertex3D_PU>>(ui32 count, Shader* shader, Texture2D* texture)
	{
		return _internalAdd<Quad<Vertex3D_PU>>(count, shader, texture, VERTEX_TYPE::PU_3D);
	}
}

#endif