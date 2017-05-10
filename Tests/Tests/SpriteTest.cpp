#include "SpriteTest.h"
#include <Globals/bs_globals.h>
#include <Rendering/bs_Camera3D.h>
#include <Rendering/bs_Camera2D.h>
#include <Game/Entity/bs_Entity.h>
#include <Game/Entity/Component/Basic/bs_Transform2D.h>
#include <Game/Entity/Component/Basic/bs_Transform3D.h>
#include <Rendering/bs_Shader.h>
#include <Rendering/bs_VertexBufferObject.h>
#include <Rendering/bs_Texture2D.h>
#include <Rendering/bs_Vertex.h>
#include <Physics\3D\Collisions\bs_Ray3D.h>

SpriteTest::SpriteTest()
	:m_initialized(false)
{

}

SpriteTest::SpriteTest(const SpriteTest& t)
	: m_initialized(t.m_initialized)
{

}

SpriteTest::~SpriteTest()
{

}

void SpriteTest::shutDown()
{
	
}

void SpriteTest::execute(bs::Level* l, real dt)
{
	if (bs::g_inputManager.keyboard.isKeyHeld(KB_LEFTARROW)) m_camera->translate(bs::Vector2(-0.1 * dt, 0.0f));
	if (bs::g_inputManager.keyboard.isKeyHeld(KB_RIGHTARROW)) m_camera->translate(bs::Vector2(0.1 * dt, 0.0f));
	if (bs::g_inputManager.keyboard.isKeyHeld(KB_UPARROW)) m_camera->translate(bs::Vector2(0.0f , 0.1 * dt));
	if (bs::g_inputManager.keyboard.isKeyHeld(KB_DOWNARROW)) m_camera->translate(bs::Vector2(0.0f, -0.1 * dt));

	bs::Vector3 vertices[4];

	vertices[0].x = -1;
	vertices[0].y = 0;
	vertices[0].z = 0;

	vertices[1].x = 2;
	vertices[1].y = -0.5;
	vertices[0].z = 0;

	vertices[2].x = 2;
	vertices[2].y = 0;
	vertices[0].z = 0;

	vertices[3].x = 0.2;
	vertices[3].y = 0.2;
	vertices[0].z = 0;

	bs::g_debugRenderer.drawShape(vertices, 4, bs::ColorRGBA32::yellow);
}

void SpriteTest::render(bs::Level* l)
{
	
}

void SpriteTest::initialize(bs::Level* l)
{
	m_time = 0.0f;

	m_camera = l->addCamera2D();
	m_sprite = bs::g_spriteRenderer.addSprite("x23.png");

	bs::Font*	font = bs::g_resourceManager.loadFont("Fonts/calibri.ttf");

	if (font == nullptr) std::cout << "Font not found" << std::endl;
	else m_sprite->setTexture(font->texture());

	bs::Sprite* sprite2 = bs::g_spriteRenderer.addSprite("FootballPitch-800px.png");
	sprite2->setPosition(1.0, 1.0);
	
}