#include "TestLevel.h"
#include <Globals/bs_globals.h>
#include <Rendering/bs_Camera2D.h>
#include <Game/Entity/bs_Entity.h>
#include <Game/Entity/Component/Basic/bs_Transform2D.h>
#include <Rendering/bs_Shader.h>
#include <Rendering/bs_VertexBufferObject.h>

TestLevel::TestLevel()
	:m_initialized(false)
{
	
}

TestLevel::TestLevel(const TestLevel& t)
	: m_initialized(t.m_initialized)
{

}

TestLevel::~TestLevel()
{
	delete m_camera;
}

void TestLevel::execute(bs::Level* l)
{
	if (!m_initialized) return;
	m_time += 0.0001f;

	m_camera->setPosition(bs::Vector2(bs::math::sin(m_time), bs::math::sin(-m_time)));
	m_camera->rotate(0.000001f);
}

void TestLevel::render(bs::Level* l)
{
	if (!m_initialized) return;

	f32 matrix[16];
	
	if (m_camera)
	{
		m_shader->beginScope();
		m_shader->uploadUniform((void*)&m_camera->view());
		m_shader->uploadUniform((void*)&m_camera->projection());
		m_shader->uploadUniform((void*)&m_camera->projection());
	//	m_shader->uploadUniform((void*)&l->entities()[0]->getComponent<bs::Transform2D>()->modelMatrix());
		f32 aspectRatio = m_camera->aspectRatio();
		m_shader->uploadUniform(&aspectRatio);
		f32 height = m_camera->viewPort().h;
		m_shader->uploadUniform(&height);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

void TestLevel::initialize(bs::Level* l)
{
	m_time = 0.0f;
	 
	m_vao.initialize();
	m_vao.bind();

	m_vbo.initialize();
	m_vbo.bind();
	f32 vertices[8];

	f32 vertexLength = 800.0f;

	vertices[0] = 0.0f;
	vertices[1] = 0.0f;

	vertices[2] = vertexLength;
	vertices[3] = 0.0f;

	vertices[4] = vertexLength;
	vertices[5] = vertexLength;

	for (ui32 i = 0; i < 6; i++)m_vbo.addData(vertices[i]);
	m_vbo.upload(BS_DRAWTYPE_STATIC);

	m_shader = &bs::g_shaderManager.getShaderMap()["TestShader"];
	m_shader->bind();

	m_vao.setAttribPointer<f32>(GL_FLOAT, 2, 0, false);

	std::cout << "Initializing "<< l->name().utf8() << std::endl;

	std::cout << "Screen aspect ratio = " << bs::g_screen.aspectRatio() << std::endl;
	
	m_camera = new bs::Camera2D();

	bs::Entity* e = l->addEntity();

	bs::Transform2D* transform = e->addComponent<bs::Transform2D>();

	std::cout << "Size of transform = " << sizeof(bs::Transform2D) << std::endl;

	m_initialized = true;
}