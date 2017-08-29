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

	class RenderManager
	{
		friend class Texture2D;
	public:
		static ERROR_ID	initialize();
		static ERROR_ID shutDown();

		static void	render();
	private:
		static QuadRenderer s_quadRenderer;
		static HashMap<String, Texture2D> s_textureDB;
	};
}

#endif // !_BS_RENDERMANAGER_H_
