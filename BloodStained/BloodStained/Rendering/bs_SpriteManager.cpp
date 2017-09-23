#include "bs_SpriteManager.h"
#include "bs_QuadRenderer.h"
#include <Utilities/bs_Error.h>
#include <Rendering/bs_Sprite.h>
#include "bs_Screen.h"

namespace bs
{
	SpriteManager::SpriteManager()
		:m_sprites(1024)
	{
	}

	SpriteManager::SpriteManager(const SpriteManager & s)
		:m_spritePointers(s.m_spritePointers),
		m_sprites(s.m_sprites)
	{
	}

	SpriteManager::~SpriteManager()
	{
	}

	ERROR_ID SpriteManager::initialize()
	{
		if (!m_sprites.initialize()) return ERROR_ID::SPRITERENDERER_INIT_FAIL;
		return ERROR_ID::NONE;
	}

	ERROR_ID SpriteManager::shutDown()
	{
		if (!m_sprites.shutDown()) return ERROR_ID::SPRITERENDERER_SHUTDOWN_FAIL;
		return ERROR_ID::NONE;
	}

	void SpriteManager::uploadData(QuadRenderer & r)
	{
		ui32 count = m_spritePointers.count();
		if (count == 0) return;

		ui32 batchSize = 0;
		const	Shader* s = m_spritePointers[0]->shader();
		const	Texture2D* t = m_spritePointers[0]->texture();

		f32 pixelWidth = 1.0f / Screen::height();

		for (ui32 i = 0;i < count; i++)
		{
			Quad<Vertex2D_PUC>* q = r.add<Quad<Vertex2D_PUC>>(1, m_spritePointers[i]->shader(), m_spritePointers[i]->texture());

			f32 w = (f32)m_spritePointers[i]->texture()->width() * m_spritePointers[i]->uvRect().w * pixelWidth * m_spritePointers[i]->scale().x;
			f32 h = (f32)m_spritePointers[i]->texture()->height()* m_spritePointers[i]->uvRect().h * pixelWidth * m_spritePointers[i]->scale().y;

			f32 hw = w / 2.0f;
			f32 hh = h / 2.0f;

			f32 uMin = m_spritePointers[i]->uvRect().x;
			f32 uMax = m_spritePointers[i]->uvRect().x + m_spritePointers[i]->uvRect().w;
			f32 vMin = m_spritePointers[i]->uvRect().y;
			f32 vMax = m_spritePointers[i]->uvRect().y + m_spritePointers[i]->uvRect().h;

			q->topLeft.color = m_spritePointers[i]->color();
			q->topLeft.position = Vector2(-hw, hh) + m_spritePointers[i]->position();
			q->topLeft.uv.u = uMin;
			q->topLeft.uv.v = vMin;

			q->bottomLeft.color = m_spritePointers[i]->color();
			q->bottomLeft.position = Vector2(-hw, -hh) + m_spritePointers[i]->position();
			q->bottomLeft.uv.u = uMin;
			q->bottomLeft.uv.v = vMax;

			q->bottomRight.color = m_spritePointers[i]->color();
			q->bottomRight.position = Vector2(hw, -hh) + m_spritePointers[i]->position();
			q->bottomRight.uv.u = uMax;
			q->bottomRight.uv.v = vMax;

			q->topRight.color = m_spritePointers[i]->color();
			q->topRight.position = Vector2(hw, hh) + m_spritePointers[i]->position();
			q->topRight.uv.u = uMax;
			q->topRight.uv.v = vMin;

			for (ui32 j = 0; j < 4; j++) (*q)[j].position.rotateAround(m_spritePointers[i]->position(),m_spritePointers[i]->orientation());
		}
	}

	Sprite* SpriteManager::addSprite(const Texture2D* texture, const Shader* shader)
	{
		Sprite* s = m_sprites.allocate(texture, shader);
		m_spritePointers.add(s);
		return s;
	}

	void SpriteManager::removeSprite(Sprite* s)
	{
		m_spritePointers.remove(s);
		m_sprites.deallocate(s);
	}
}
