#ifndef _BS_RENDERMANAGER_H_
#define _BS_RENDERMANAGER_H_

#include <Rendering/bs_Color.h>
#include <Rendering/bs_OpenGL.h>
#include "bs_QuadRenderer.h"
#include "bs_Texture2D.h"
#include <Containers/bs_HashMap.h>


namespace bs
{
	enum class ERROR_ID;
	class Camera;

	class RenderManager
	{
		friend class Texture2D;
	public:
		static ERROR_ID	initialize();
		static ERROR_ID shutDown();

		static void	render(const Array<Camera*> m_cameras);

		template <class T>
		static Quad<T>* addQuad(ui32 count, Shader* shader, Texture2D* texture);
	private:
		static QuadRenderer s_quadRenderer;
		static HashMap<String, Texture2D> s_textureDB;

	};
	template<class T>
	inline Quad<T>* RenderManager::addQuad(ui32 count, Shader * shader, Texture2D * texture)
	{
		return s_quadRenderer.add<Quad<T>>(count, shader, texture);
	}
}

#endif // !_BS_RENDERMANAGER_H_
