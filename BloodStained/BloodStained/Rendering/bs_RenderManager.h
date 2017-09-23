#ifndef _BS_RENDERMANAGER_H_
#define _BS_RENDERMANAGER_H_

#include <Rendering/bs_Color.h>
#include <Rendering/bs_OpenGL.h>
#include "bs_QuadRenderer.h"
#include "bs_DebugRenderer.h"
#include "bs_Texture2D.h"
#include <Containers/bs_HashMap.h>
#include <Rendering/bs_RenderBufferObjects.h>
#include <Rendering/bs_SpriteManager.h>
#include <Rendering/bs_Sprite.h>
#include <Rendering/bs_Shader.h>

namespace bs
{
	enum class ERROR_ID;
	class Camera;
	class Vector2;
	class ColorRGBAf;

	class RenderManager
	{
		friend class Texture2D;
	public:
		static ERROR_ID	initialize();
		static ERROR_ID shutDown();

		static void	render(const Array<Camera*> m_cameras);

		static Sprite* addSprite(const Texture2D* texture, const Shader* shader);
		static void drawDebugShape(Vector2 * vertices, ui32 count, const ColorRGBAf& color);
		static void drawDebugCircle(const Vector2& center, f32 radius, ui16 resolution, const ColorRGBAf& color);
		static void RenderManager::drawDebugLine(const Vector2& from, const Vector2& to, const ColorRGBAf& color);
	private:
		static QuadRenderer s_quadRenderer;
		static DebugRenderer s_debugRenderer;
		static SpriteManager s_spriteManager;
		static HashMap<String, Texture2D> s_textureDB;

	};
	template<class T>
	inline Quad<T>* RenderManager::addQuad(ui32 count, Shader * shader, Texture2D * texture)
	{
		return s_quadRenderer.add<Quad<T>>(count, shader, texture);
	}
}

#endif // !_BS_RENDERMANAGER_H_
