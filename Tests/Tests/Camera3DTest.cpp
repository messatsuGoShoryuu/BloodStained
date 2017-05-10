#include "Camera3DTest.h"
#include <Globals/bs_globals.h>
#include <Rendering/bs_Camera3D.h>
#include <Game/Entity/bs_Entity.h>
#include <Game/Entity/Component/Basic/bs_Transform2D.h>
#include <Game/Entity/Component/Basic/bs_Transform3D.h>
#include <Rendering/bs_Shader.h>
#include <Rendering/bs_VertexBufferObject.h>
#include <Rendering/bs_Texture2D.h>
#include <Rendering/bs_Vertex.h>
#include <Physics\3D\Collisions\bs_Ray3D.h>

Camera3DTest::Camera3DTest()
	:m_initialized(false),
	m_relpos(true)
{

}

Camera3DTest::Camera3DTest(const Camera3DTest& t)
	: m_initialized(t.m_initialized)
{

}

Camera3DTest::~Camera3DTest()
{
	
}

void Camera3DTest::shutDown()
{
	delete m_camera;
}

void Camera3DTest::execute(bs::Level* l, real dt)
{

	if (!m_initialized) return;

	bs::Vector2 mousePosition(bs::g_inputManager.mouse.getX(), bs::g_inputManager.mouse.getY());
	bs::Ray3D ray = m_camera->screenToWorld(mousePosition);

	bs::Vector3 intersection = bs::hitTest(ray, m_plane);

	bs::Vector3 newPos = ray.origin;

	if (bs::g_inputManager.keyboard.isKeyHeld(KB_UPARROW))
	{
		m_camera->rotate(bs::Quaternion((m_camera->right()), BS_DEG_TO_RAD * -50.0 * dt));
	}
	if (bs::g_inputManager.keyboard.isKeyHeld(KB_DOWNARROW))
	{
		m_camera->rotate(bs::Quaternion((m_camera->right()), BS_DEG_TO_RAD * 50.0 * dt));
	}

	if (bs::g_inputManager.keyboard.isKeyHeld(KB_LEFTARROW))
	{
		m_camera->rotate(bs::Quaternion(bs::Vector3::up, BS_DEG_TO_RAD * -50.0 * dt));
	}
	if (bs::g_inputManager.keyboard.isKeyHeld(KB_RIGHTARROW))
	{
		m_camera->rotate(bs::Quaternion(bs::Vector3::up, BS_DEG_TO_RAD * 50.0 * dt));
	}

	if (bs::g_inputManager.keyboard.isKeyHeld(KB_A))
	{
		m_camera->translate(m_camera->right() * -2 * dt);
	}
	if (bs::g_inputManager.keyboard.isKeyHeld(KB_D))
	{
		m_camera->translate(m_camera->right() * 2 * dt);
	}

	if (bs::g_inputManager.keyboard.isKeyHeld(KB_W))
	{
		m_camera->translate(m_camera->forward() * 2 * dt);
	}
	if (bs::g_inputManager.keyboard.isKeyHeld(KB_S))
	{
		m_camera->translate(m_camera->forward() * -2 * dt);
	}

	m_transform.setPosition(intersection);
}

void Camera3DTest::render(bs::Level* l)
{
	if (!m_initialized) return;

	f32 matrix[16];

	if (m_camera)
	{
		f32 aspectRatio = m_camera->aspectRatio();
		f32 height = m_camera->viewPort().h;
		bs::Matrix4x4 identity;

		m_pitch.bind();

		m_vao2.bind();
		m_vbo2.bind();

		m_texShader->beginScope();
		

		m_texShader->uploadUniform((void*)&m_camera->view());
		m_texShader->uploadUniform((void*)&m_camera->projection());
		m_texShader->uploadUniform((void*)&identity);
		m_texShader->uploadUniform(&aspectRatio);
		m_texShader->uploadUniform(&height);
		m_texShader->uploadUniform(0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		
		m_texShader->unbind();
		m_vao2.unbind();
		m_vbo2.unbind();

		m_pitch.unbind();

		m_sign.bind();
		m_texShader->bind();
		m_texShader->beginScope();
		m_vao.bind();
		m_vbo.bind();
		m_texShader->uploadUniform((void*)&m_camera->view());
		m_texShader->uploadUniform((void*)&m_camera->projection());
		m_texShader->uploadUniform((void*)&m_transform.modelMatrix());
		
		m_texShader->uploadUniform(&aspectRatio);
		
		m_texShader->uploadUniform(&height);
		m_texShader->uploadUniform(0);

		glDrawArrays(GL_TRIANGLES, 0, 6);



		
		identity.loadIdentity();
		m_vao.unbind();
		m_vbo.unbind();

		m_sign.unbind();
		
	}
}

void	drawCube(f32* q, f32 l, f32 o)
{
	q[0] = -l;	q[3] = l;
	q[1] = l;	q[4] = l;
	q[2] = o;	q[5] = o;

	q[6] = -l;	q[15] = l;
	q[7] = -l;	q[16] = l;
	q[8] = o;	q[17] = o;

	q[9] = -l;	q[12] = l;
	q[10] = -l;	q[13] = -l;
	q[11] = o;	q[14] = o;

	
	
	q[18] = -l;		q[21] = l;
	q[19] = -l;		q[22] = -l;
	q[20] = o;		q[23] = o;

	q[24] = -l;		q[33] = l;
	q[25] = -l;		q[34] = -l;
	q[26] = o-2*l;	q[35] = o;

	q[27] = -l;		q[30] = l;
	q[28] = -l;		q[31] = -l;
	q[29] = o-2*l;	q[32] = o-2*l;

	
	
	q[36] = -l;		q[39] = l;
	q[37] = -l;		q[40] = -l;
	q[38] = o-2*l;	q[41] = o-2*l;

	q[42] = -l;		q[51] = l;
	q[43] = l;		q[52] = -l;
	q[44] = o-2*l;	q[53] = o-2*l;

	q[45] = -l;		q[48] = l;
	q[46] = l;		q[49] = l;
	q[47] = o-2*l;	q[50] = o-2*l;



	q[54] = -l;		q[57] = l;
	q[55] = l;		q[58] = l;
	q[56] = o-l;	q[59] = o-2*l;

	q[60] = -l;		q[69] = l;
	q[61] = l;		q[70] = l;
	q[62] = o;		q[71] = o - 2*l;

	q[63] = -l;		q[66] = l;
	q[64] = l;		q[67] = l;
	q[65] = o;		q[68] = o;



	q[72] = -l;		q[75] = -l;
	q[73] = -l;		q[76] = l;
	q[74] = o;		q[77] = o;

	q[78] = -l;		q[87] = -l;
	q[79] = -l;		q[88] = l;
	q[80] = o - 2*l;	q[89] = o;

	q[81] = -l;		q[84] = -l;
	q[82] = -l;		q[85] = l;
	q[83] = o - 2*l;	q[86] = o - 2*l;



	q[90] = l;		q[93] = l;
	q[91] = -l;		q[94] = l;
	q[92] = o;		q[95] = o;

	q[96] = l;		q[105] = l;
	q[97] = -l;		q[106] = l;
	q[98] = o - 2*l;	q[107] = o;

	q[99] = l;		q[102] = l;
	q[100] = -l;	q[103] = l;
	q[101] = o - 2*l;	q[104] = o - 2*l;
	
}

void drawQuadArray(f32* q, f32 w, f32 h)
{
	w = w / 2.0f;

	q[0] = -w;	q[3] = w;
	q[1] = 0;	q[4] = 0;
	q[2] = 0;	q[5] = 0;

	q[6]= -w;	q[15] = w;
	q[7] = 0;   q[16] = 0;
	q[8] = h;	q[17] = 0;

	q[9] = -w;	q[12] = w;
	q[10] = 0;	q[13] = 0;
	q[11] = h;	q[14] = h;
}

void drawQuad(bs::Vertex3D_PU* q, f32 w, f32 h, f32 d)
{
	w = w / 2.0f;
	d = d / 2.0f;

	q[0].position[0] = -w;	q[1].position[0] = w;
	q[0].position[1] = h;	q[1].position[1] = h;
	q[0].position[2] = -d;	q[1].position[2] = -d;

	q[2].position[0] = -w;	q[5].position[0] = w;
	q[2].position[1] = h;   q[5].position[1] = h;
	q[2].position[2] = d;	q[5].position[2] = -d;

	q[3].position[0] = -w;	q[4].position[0] = w;
	q[3].position[1] = h;	q[4].position[1] = h;
	q[3].position[2] = d;	q[4].position[2] = d;

	q[0].uv.u = 0.0f;
	q[0].uv.v = 0.0f;

	q[1].uv.u = 1.0f;
	q[1].uv.v = 0.0f;

	q[2].uv.u = 0.0f;
	q[2].uv.v = 1.0f;

	q[3].uv.u = 0.0f;
	q[3].uv.v = 1.0f;

	q[4].uv.u = 1.0f;
	q[4].uv.v = 1.0f;

	q[5].uv.u = 1.0f;
	q[5].uv.v = 0.0f;
}

void Camera3DTest::initialize(bs::Level* l)
{
	m_time = 0.0f;

	m_vao.initialize();
	m_vao.bind();

	m_vbo.initialize();
	m_vbo.bind();

	bs::Vertex3D_PU qvertices[6];
	f32 width = 0.1;
	f32 height = 0.1;

	//Quad
	drawQuad(qvertices, width, 0.00001,height);

	for (ui32 i = 0; i < 6; i++)m_vbo.addData(qvertices[i]);
	m_vbo.upload(BS_DRAWTYPE_STATIC);

	glDepthMask(GL_FALSE);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	

	m_shader = &bs::g_shaderManager.getShaderMap()["TestShader"];
	m_texShader = &bs::g_shaderManager.getShaderMap()["TexShader3D"];
	m_shader->bind();

	m_vao.setAttribPointer<bs::Vertex3D_PU>(GL_FLOAT, 3, offsetof(bs::Vertex3D_PU, position), false);
	m_vao.setAttribPointer<bs::Vertex3D_PU>(GL_FLOAT, 2, offsetof(bs::Vertex3D_PU, uv), true);

	std::cout << "Initializing " << l->name().utf8() << std::endl;

	std::cout << "Screen aspect ratio = " << bs::g_screen.aspectRatio() << std::endl;
	m_vao.unbind();
	m_vbo.unbind();
	m_shader->unbind();

	m_vao2.initialize();
	m_vao2.bind();
	m_vbo2.initialize();
	m_vbo2.bind();

	width = 8;
	height = 5.7;

	drawQuad(qvertices, width, 0,height);

	f32 qvf[18];
	drawQuadArray(qvf,width,height);
	for (ui32 i = 0; i < 6; i++)
	{
		std::cout << "qVertices[" << i << "].position = " << qvertices[i].position.toString().utf8() << std::endl;
		std::cout << "qVertices[" << i << "].uv		  = " << "U = " << qvertices[i].uv.u << " V = " << qvertices[i].uv.v << std::endl;
		m_vbo2.addData(qvertices[i]);
	}
	m_vbo2.upload(BS_DRAWTYPE_STATIC);

	m_texShader->bind();
	m_vao2.setAttribPointer<bs::Vertex3D_PU>(GL_FLOAT, 3, offsetof(bs::Vertex3D_PU,position), false);
	m_vao2.setAttribPointer<bs::Vertex3D_PU>(GL_FLOAT, 2, offsetof(bs::Vertex3D_PU,uv), true);

	m_vao2.unbind();
	m_vbo2.unbind();

	m_texShader->unbind();

	m_camera = new bs::Camera3D();
	m_camera->setFov(60);

	bs::Quaternion q(bs::Vector3(1.0f, 0.0f, 0.0f), -30*BS_DEG_TO_RAD);
//	m_camera->setOrientation(q);

	m_camera->setPosition(bs::Vector3(0,1,-1));

	m_pitch = bs::g_resourceManager.loadImage("FootballPitch-800px.png");
	m_sign = bs::g_resourceManager.loadImage("x23.png");

	std::cout << "pitch id = " << m_pitch.id() << std::endl;
	std::cout << "Pitch width = " << m_pitch.width() << std::endl;
	std::cout << "Bound texture count" << bs::Texture2D::boundTextureCount() << std::endl;

	m_initialized = true;

	m_plane.point = bs::Vector3::zero;
	m_plane.normal = bs::Vector3::up;
}