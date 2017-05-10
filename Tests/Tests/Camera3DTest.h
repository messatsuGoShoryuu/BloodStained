#ifndef CAMERA3DTEST_H
#define CAMERA3DTEST_H

#include <Game/bs_Level.h>
#include <Game/bs_LevelScript.h>
#include <GL\glew.h>

#include <Rendering/bs_VertexBufferObject.h>
#include <Physics\3D\Collisions\bs_Primitives.h>
#include <Rendering/bs_Texture2D.h>
#include <Game/Entity/Component/Basic/bs_Transform3D.h>

namespace bs
{
	class Camera3D;
	class Shader;
}
class Camera3DTest : public bs::LevelScript
{
public:
	Camera3DTest();
	Camera3DTest(const Camera3DTest& t);
	~Camera3DTest();

	void execute(bs::Level* l, real dt);
	void initialize(bs::Level* l);
	void render(bs::Level* l);
	void shutDown();

private:
	bs::VertexBufferObject m_vbo;
	bs::VertexArrayObject m_vao;

	bs::VertexBufferObject	m_vbo2;
	bs::VertexArrayObject m_vao2;
	GLuint m_vertexShader;
	GLuint m_fragmentShader;
	GLuint m_shaderProgram;

	bs::Camera3D*	m_camera;
	f32	m_time;

	bs::Shader*	m_shader;
	bs::Shader* m_texShader;

	bool m_initialized;
	bool m_relpos;
	bs::Plane m_plane;

	bs::Texture2D m_pitch;
	bs::Texture2D m_sign;
	bs::Transform3D m_transform;
};



#endif // !TEST_LEVEL_H
