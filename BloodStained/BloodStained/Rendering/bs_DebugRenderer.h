#ifndef _BS_DEBUGRENDERER_H_
#define _BS_DEBUGRENDERER_H_

#include <Containers/bs_Array.h>
#include <Allocator/bs_StackAllocator.h>
#include "bs_RenderBufferObjects.h"
#include "bs_Color.h"
#include "bs_OpenGLEnums.h"
namespace bs
{
	enum class ERROR_ID;
	class Camera;
	struct Vertex2D_PC;
	class Vector2;
	class Shader;

	struct DebugRenderBatch
	{
		ColorRGBA32 color;
		OPENGL_PRIMITIVE primitive;
	};

	class DebugRenderer
	{
	public:
		DebugRenderer();
		DebugRenderer(const DebugRenderer& r);
		~DebugRenderer();

		ERROR_ID initialize();
		ERROR_ID shutDown();

		void drawShape(Vector2* vertices, ui16 count, const ColorRGBAf& color);

		void drawCircle(const Vector2& center, f32 radius, ui16 resolution, const ColorRGBAf& color);

		void drawLine(const Vector2& from, const Vector2& to, const ColorRGBAf& color);

		void	render(const Array<Camera*>& cameras);

	public:
		void _updateCameraUniforms(Camera * camera);
	

	private:
		StackAllocator m_stackAllocator;
		VertexBufferObject m_vbo;
		VertexArrayObject m_vao;
		ElementBufferObject m_ebo;
		const Shader* m_shader;
		ui32 m_vertexCount;
	};

}


#endif // !_BS_DEBUGRENDERER_H_