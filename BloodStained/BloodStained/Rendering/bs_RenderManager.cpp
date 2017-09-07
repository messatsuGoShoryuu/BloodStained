#include "bs_RenderManager.h"
#include <Utilities/bs_Error.h>

namespace bs
{
	QuadRenderer RenderManager::s_quadRenderer;
	SpriteRenderer RenderManager::s_spriteRenderer;
	HashMap<String, Texture2D> RenderManager::s_textureDB;

	ERROR_ID RenderManager::initialize()
	{
		//Set default texture creation method
		Texture2D::setCreationMethod(true, true, OPENGL_COLOR_FORMAT::RGBA);

		ERROR_ID err = s_quadRenderer.initialize();
		if (err != ERROR_ID::NONE) return err;

		return ERROR_ID::NONE;
	}

	ERROR_ID RenderManager::shutDown()
	{
		ERROR_ID err = s_quadRenderer.shutDown();
		if (err != ERROR_ID::NONE) return err;

		return ERROR_ID::NONE;
	}

	void RenderManager::render(const Array<Camera*> m_cameras)
	{
		s_spriteRenderer.render(s_quadRenderer);
		ui32 count = m_cameras.count();
		for(ui32 i = 0; i<count;i++)
			s_quadRenderer.render(m_cameras);
	}
	Sprite* RenderManager::addSprite(const Texture2D * texture, const Shader * shader)
	{
		return	s_spriteRenderer.addSprite(texture, shader);
	}
}
