#ifndef _BS_SPRITERENDERER_H_
#define _BS_SPRITERENDERER_H_

#include <Allocator/bs_PoolAllocator.h>
#include <Containers/bs_Array.h>

namespace bs
{
	class QuadRenderer;
	class Sprite;
	class Texture2D;
	class Shader;
	enum class ERROR_ID;

	class SpriteRenderer
	{
	public:
		SpriteRenderer();
		SpriteRenderer(const SpriteRenderer& s);
		~SpriteRenderer();

		ERROR_ID initialize();
		ERROR_ID shutDown();

		void render(QuadRenderer& r);

		Sprite* addSprite(const Texture2D* texture, const Shader* shader);
		void removeSprite(Sprite* s);
	private:
		PoolAllocator<Sprite>	m_sprites;

		//TODO: implement a pooled linked list and replace the array with it?
		Array<Sprite*>			m_spritePointers;
	};
}
#endif // !_BS_SPRITERENDERER_H_
