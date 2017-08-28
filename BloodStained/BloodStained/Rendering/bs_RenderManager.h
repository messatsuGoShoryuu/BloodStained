#ifndef _BS_RENDERMANAGER_H_
#define _BS_RENDERMANAGER_H_

#include <Rendering/bs_Color.h>
#include <Rendering/bs_OpenGL.h>
#include "bs_QuadRenderer.h"

namespace bs
{
	enum class ERROR_ID;

	class RenderManager
	{
	public:
		static ERROR_ID	initialize();
		static ERROR_ID shutDown();

		static void	render();
	private:
		static QuadRenderer s_quadRenderer;
	};
}

#endif // !_BS_RENDERMANAGER_H_
