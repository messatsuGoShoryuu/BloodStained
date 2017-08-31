#include "bs_Level.h"

//Test purposes.
#include <FileIO/bs_ResourceManager.h>
#include <Rendering/bs_Texture2D.h>

#include <Rendering/bs_RenderBufferObjects.h>
#include <Rendering/bs_Primitive.h>
#include <Rendering/bs_ShaderManager.h>
#include <Rendering/bs_Shader.h>
namespace bs
{
	Level::Level()
		:m_id(0)
	{
	}

	Level::Level(const Level & l)
		:m_cameras(l.m_cameras),
		m_id(l.m_id)
	{
	}

	Level::~Level()
	{
	}

	void Level::initialize()
	{
		const Texture2D* tex = ResourceManager::loadTexture2D("x23.png");
		m_cameras.add(new Camera2D());

		VertexBufferObject vbo;
		OpenGL::clearColor(ColorRGBA32::red);
		OpenGL::clear();

//		const Shader* s = ShaderManager::getShader("DefaultSprite/DefaultSprite");
//		s->bind();

		vbo.initialize();
		

		Quad<Vertex2D_PUC> q;

		Vertex2D_PUC v[6];
		
		q.topLeft.color = ColorRGBA32::white;
		q.topLeft.position = Vector2(-0.5f, 0.5f);

		q.bottomLeft.color = ColorRGBA32::blue;
		q.bottomLeft.position = Vector2(-0.5f, -0.5f);

		q.bottomRight.color = ColorRGBA32::white;
		q.bottomRight.position = Vector2(0.5f, -0.5f);

		q.topRight.color = ColorRGBA32::white;
		q.topRight.position = Vector2(0.5f, 0.5f);


		v[0] = q[0];
		v[1] = q[1];
		v[2] = q[2];
		v[3] = q[2];
		v[4] = q[3];
		v[5] = q[0];


		vbo.bind();

		ui32 code = OpenGL::getError();

		vbo.upload((byte*)v, 6 * sizeof(Vertex2D_PUC));
		OpenGL::enableVertexAttribArray(0);
		OpenGL::vertexAttribPointer(0, 2, OPENGL_TYPE::FLOAT, false, sizeof(Vertex2D_PUC), 0);
		OpenGL::enableVertexAttribArray(1);
		OpenGL::vertexAttribPointer(1, 2, OPENGL_TYPE::FLOAT, false, sizeof(Vertex2D_PUC), (void*)offsetof(Vertex2D_PUC, uv));
		OpenGL::enableVertexAttribArray(2);
		OpenGL::vertexAttribPointer(2, 4, OPENGL_TYPE::FLOAT, true, sizeof(Vertex2D_PUC), (void*)offsetof(Vertex2D_PUC, color));
		code = OpenGL::getError();

		OpenGL::drawArrays(OPENGL_PRIMITIVE::TRIANGLES, 0, 6);
		code = OpenGL::getError();
		
	}

	void Level::shutDown()
	{
		for (int i = 0; i < m_cameras.count(); i++) delete m_cameras[i];
		m_cameras.~Array();
	}

	void Level::update()
	{
	}
}

