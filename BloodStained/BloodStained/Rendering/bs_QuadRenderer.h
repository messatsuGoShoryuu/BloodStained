#ifndef _BS_QUADRENDERER_H_
#define	_BS_QUADRENDERER_H_

#include <Allocator/bs_StackAllocator.h>
#include <Containers/bs_Array.h>
#include "bs_Primitive.h"
#include "bs_Vertex.h"
#include "bs_Shader.h"
#include "bs_Texture2D.h"
#include "bs_RenderBufferObjects.h"

namespace bs
{
	class Camera;
	enum class ERROR_ID;

	struct QuadBatch
	{
		void*	startPointer;
		void*	endPointer;
		ptrsize	count;
		const Shader*	shader;
		const Texture2D* texture;
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
		T*	add(ui32 count,const Shader* shader, const Texture2D* texture)
		{
		}

		template<>
		Quad<Vertex2D_PUC>*	add<Quad<Vertex2D_PUC>>(ui32 count, const  Shader* shader, const  Texture2D* texture);

		template<>
		Quad<Vertex3D_PC>*	add<Quad<Vertex3D_PC>>(ui32 count, const  Shader* shader, const  Texture2D* texture);

		template<>
		Quad<Vertex3D_PU>*	add<Quad<Vertex3D_PU>>(ui32 count, const  Shader* shader, const  Texture2D* texture);

	private:
		template <class T> 
		T* _internalAdd(ui32 count, const  Shader* shader, const  Texture2D* texture, VERTEX_TYPE type);

		void _updateCameraUniforms(Camera* camera,const Shader* shader);

		bool	_shouldBatchChange(const QuadBatch* current, VERTEX_TYPE type, 
			const Shader* shader, const  Texture2D* texture);
		void	_createBatch(void* startPointer, VERTEX_TYPE type, const Shader* shader, const Texture2D* texture);

		ERROR_ID	_initVaos();

	private:
		StackAllocator		m_stackAllocator;
		Array<QuadBatch>	m_batches;
		VertexBufferObject	m_vbo;
		ElementBufferObject m_ebo;
		Array<VertexArrayObject> m_vaos;
	};

	template<class T>
	T* QuadRenderer::_internalAdd(ui32 count, const  Shader* shader, const  Texture2D* texture, VERTEX_TYPE type)
	{
		T* pointer = (T*)m_stackAllocator.getFrame();
		m_stackAllocator.allocate(sizeof(Vertex2D_PUC) * count * 6, __alignof(Vertex2D_PUC));
		ui16 offset = m_ebo.count();
		for (ui32 i = 0; i < count; i++)
		{
			m_ebo.add(offset);
			m_ebo.add(offset + 1);
			m_ebo.add(offset + 2);
			m_ebo.add(offset + 2);
			m_ebo.add(offset + 3);
			m_ebo.add(offset);
		}

		QuadBatch* currentBatch = nullptr;
		if (m_batches.count() == 0)
		{
			_createBatch(pointer, type, shader, texture);
			currentBatch = &m_batches.last();
		}
		else 
		{
			currentBatch = &m_batches.last();
			if (_shouldBatchChange(currentBatch, type, shader, texture))
			{
				currentBatch->endPointer = pointer;
				_createBatch(pointer, type, shader, texture);
				currentBatch = &m_batches.last();
			}
		}

		currentBatch->count += count;

		return pointer;
	}

	template<>
	Quad<Vertex2D_PUC>*	QuadRenderer::add<Quad<Vertex2D_PUC>>(ui32 count, const  Shader* shader, const  Texture2D* texture)
	{
		return _internalAdd<Quad<Vertex2D_PUC>>(count, shader, texture, VERTEX_TYPE::PUC_2D);
	}

	template<>
	Quad<Vertex3D_PC>*	QuadRenderer::add<Quad<Vertex3D_PC>>(ui32 count, const Shader* shader, const Texture2D* texture)
	{
		return _internalAdd<Quad<Vertex3D_PC>>(count, shader, texture,VERTEX_TYPE::PC_3D);
	}

	template<>
	Quad<Vertex3D_PU>*	QuadRenderer::add<Quad<Vertex3D_PU>>(ui32 count, const Shader* shader, const  Texture2D* texture)
	{
		return _internalAdd<Quad<Vertex3D_PU>>(count, shader, texture, VERTEX_TYPE::PU_3D);
	}
}

#endif