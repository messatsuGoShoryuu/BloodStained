#ifndef TEST_LEVEL_H
#define TEST_LEVEL_H

#include <Game/bs_Level.h>
#include <Game/bs_LevelScript.h>
#include <GL\glew.h>

#include <Rendering/bs_VertexBufferObject.h>

namespace bs
{
	class Camera2D;
	class Shader;
}
class TestLevel : public bs::LevelScript
{
public:
	TestLevel();
	TestLevel(const TestLevel& t);
	~TestLevel();

	void execute(bs::Level* l);
	void initialize(bs::Level* l);
	void render(bs::Level* l);

private:
	bs::VertexBufferObject m_vbo;
	bs::VertexArrayObject m_vao;
	GLuint m_vertexShader;
	GLuint m_fragmentShader;
	GLuint m_shaderProgram;

	bs::Camera2D*	m_camera;
	f32	m_time;

	bs::Shader*	m_shader;
	bool m_initialized;
};



#endif // !TEST_LEVEL_H
