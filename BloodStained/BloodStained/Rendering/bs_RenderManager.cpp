#include "bs_RenderManager.h"
#include <Utilities/bs_Error.h>
#include "bs_Camera.h"


namespace bs
{
	QuadRenderer RenderManager::s_quadRenderer;
	DebugRenderer RenderManager::s_debugRenderer;
	SpriteManager RenderManager::s_spriteManager;
	HashMap<String, Texture2D> RenderManager::s_textureDB;

	ERROR_ID RenderManager::initialize()
	{
		//Set default texture creation method
		Texture2D::setCreationMethod(true, true, OPENGL_COLOR_FORMAT::RGBA);

		ERROR_ID err = s_quadRenderer.initialize();
		if (err != ERROR_ID::NONE) return err;

		err = s_debugRenderer.initialize();
		if (err != ERROR_ID::NONE) return err;

		return ERROR_ID::NONE;
	}

	ERROR_ID RenderManager::shutDown()
	{
		ERROR_ID err = s_debugRenderer.shutDown();
		if (err != ERROR_ID::NONE) return err;

		err = s_quadRenderer.shutDown();
		if (err != ERROR_ID::NONE) return err;

		return ERROR_ID::NONE;
	}

	void RenderManager::render(const Array<Camera*> m_cameras)
	{
		s_spriteManager.uploadData(s_quadRenderer);
		s_quadRenderer.render(m_cameras);
		s_debugRenderer.render(m_cameras);

		for (ui32 i = 0; i < m_cameras.count(); i++)
		{
			m_cameras[i]->setDirty(false);
		}
	}
	Sprite* RenderManager::addSprite(const Texture2D * texture, const Shader * shader)
	{
		return	s_spriteManager.addSprite(texture, shader);
	}
	void RenderManager::drawDebugShape(Vector2 * vertices, ui32 count, const ColorRGBAf& color)
	{
		s_debugRenderer.drawShape(vertices, count, color);
	}
	void RenderManager::drawDebugCircle(const Vector2 & center, f32 radius, ui16 resolution, const ColorRGBAf & color)
	{
		s_debugRenderer.drawCircle(center, radius, resolution, color);
	}

	void RenderManager::drawDebugLine(const Vector2& from, const Vector2& to, const ColorRGBAf& color)
	{
		s_debugRenderer.drawLine(from, to, color);
	}
}
