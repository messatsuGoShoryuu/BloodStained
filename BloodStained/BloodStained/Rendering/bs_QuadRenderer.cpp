#include "bs_QuadRenderer.h"
#include <Utilities/bs_Error.h>

namespace bs
{
	QuadRenderer::QuadRenderer()
		:m_stackAllocator(512 * BS_MEGABYTE)
	{
	}

	QuadRenderer::~QuadRenderer()
	{
	}

	ERROR_ID QuadRenderer::initialize()
	{
		m_stackAllocator.initialize();
		return ERROR_ID();
	}

	ERROR_ID QuadRenderer::shutDown()
	{
		return ERROR_ID();
	}

	void QuadRenderer::render(const Array<Camera*> cameras)
	{
		m_stackAllocator.deallocate();
	}

	bool QuadRenderer::_shouldBatchChange(const QuadBatch * current, VERTEX_TYPE type, ui32 shaderID, ui32 textureID)
	{
		return current->shader->id() != shaderID || current->type != type || current->texture->id() != textureID;
	}

	void QuadRenderer::_createBatch(void * startPointer, VERTEX_TYPE type, Shader * shader, Texture2D * texture)
	{
		ui32 index = m_batches.construct();
		m_batches[index].startPointer = startPointer;
		m_batches[index].shader = shader;
		m_batches[index].type = type;
		m_batches[index].texture = texture;
	}
}