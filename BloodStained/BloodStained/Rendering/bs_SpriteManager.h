#ifndef _BS_SPRITEMANAGER_H_
#define _BS_SPRITEMANAGER_H_

#include <Allocator/bs_PoolAllocator.h>
#include <Containers/bs_Array.h>

namespace bs
{
	class QuadRenderer;
	class Sprite;
	class Texture2D;
	class Shader;
	enum class ERROR_ID;

	class SpriteManager
	{
	public:
		SpriteManager();
		SpriteManager(const SpriteManager& s);
		~SpriteManager();

		ERROR_ID initialize();
		ERROR_ID shutDown();

		void uploadData(QuadRenderer& r);

		Sprite* addSprite(const Texture2D* texture, const Shader* shader);
		void removeSprite(Sprite* s);
	private:
		PoolAllocator<Sprite>	m_sprites;

		//TODO: implement a pooled linked list and replace the array with it?
		Array<Sprite*>			m_spritePointers;
	};
}
#endif // !_BS_SPRITERENDERER_H_
