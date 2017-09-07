#include "bs_SpriteRenderer.h"
#include "bs_QuadRenderer.h"
#include <Utilities/bs_Error.h>
#include <Rendering/bs_Sprite.h>

namespace bs
{
	SpriteRenderer::SpriteRenderer()
		:m_sprites(1024)
	{
	}

	SpriteRenderer::SpriteRenderer(const SpriteRenderer & s)
		:m_spritePointers(s.m_spritePointers),
		m_sprites(s.m_sprites)
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	ERROR_ID SpriteRenderer::initialize()
	{
		if (!m_sprites.initialize()) return ERROR_ID::SPRITERENDERER_INIT_FAIL;
		return ERROR_ID::NONE;
	}

	ERROR_ID SpriteRenderer::shutDown()
	{
		if (!m_sprites.shutDown()) return ERROR_ID::SPRITERENDERER_SHUTDOWN_FAIL;
		return ERROR_ID::NONE;
	}

	void SpriteRenderer::render(QuadRenderer & r)
	{
		ui32 count = m_spritePointers.count();

		ui32 batchSize = 0;
		const	Shader* s = m_spritePointers[0]->shader();
		const	Texture2D* t = m_spritePointers[0]->texture();

		for (ui32 i = 0;i < count; i++)
		{
			Quad<Vertex2D_PUC>* qptr = r.add<Quad<Vertex2D_PUC>>(1, m_spritePointers[i]->shader(), m_spritePointers[i]->texture());
			Vertex2D_PUC* v = reinterpret_cast<Vertex2D_PUC*>(qptr);
			Quad<Vertex2D_PUC> q;

			q.topLeft.color = ColorRGBA32::white;
			q.topLeft.position = Vector2(-0.5f, 0.5f) + m_spritePointers[i]->position();
			q.topLeft.uv.u = 0;
			q.topLeft.uv.v = 0;

			q.bottomLeft.color = ColorRGBA32::white;
			q.bottomLeft.position = Vector2(-0.5f, -0.5f) + m_spritePointers[i]->position();
			q.bottomLeft.uv.u = 0;
			q.bottomLeft.uv.v = 1;

			q.bottomRight.color = ColorRGBA32::white;
			q.bottomRight.position = Vector2(0.5f, -0.5f) + m_spritePointers[i]->position();
			q.bottomRight.uv.u = 1;
			q.bottomRight.uv.v = 1;

			q.topRight.color = ColorRGBA32::white;
			q.topRight.position = Vector2(0.5f, 0.5f) + m_spritePointers[i]->position();
			q.topRight.uv.u = 1;
			q.topRight.uv.v = 0;

			v[0] = q[0];
			v[1] = q[1];
			v[2] = q[2];
			v[3] = q[2];
			v[4] = q[3];
			v[5] = q[0];
		}
	}

	Sprite* SpriteRenderer::addSprite(const Texture2D* texture, const Shader* shader)
	{
		Sprite* s = m_sprites.allocate(texture, shader);
		m_spritePointers.add(s);
		return s;
	}

	void SpriteRenderer::removeSprite(Sprite* s)
	{
		m_spritePointers.remove(s);
		m_sprites.deallocate(s);
	}
}
