#ifndef BS_DEBUGRENDERER_H
#define BS_DEBUGRENDERER_H

#include "../../bs_VertexBufferObject.h"

namespace bs
{
	class Shader;
	class Camera2D;
	class ColorRGBA32;
	class Vector3;

	class DebugRenderer
	{
		friend class Level;
	public:
		DebugRenderer();
		~DebugRenderer();

	private:
		DebugRenderer(const DebugRenderer& d);

	public:
		ERROR_ID	initialize();

		ERROR_ID	shutDown();

		void	render(Camera2D* camera);

		void drawShape(Vector3* vertices, ui32 vertexCount, const ColorRGBA32& color);
		void drawLine(const Vector3& begin, const Vector3& end, const ColorRGBA32& color);

	private:
		void	_updateCameraUniforms(Camera2D* camera);

		//Makes draw calls
		void	_draw(Camera2D* camera);

		//Upload sprite data to OpenGL
		void	_uploadData();

	public:
		VertexBufferObject	m_vbo;
		VertexArrayObject	m_vao;
		IndexBufferObject	m_ibo;
		Shader*				m_shader;
		ui32				m_vertexCount;
	};
}

#endif // !BS_DEBUGRENDERER_H
