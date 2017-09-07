#include "bs_Level.h"

//Test purposes.
#include <FileIO/bs_ResourceManager.h>
#include <Rendering/bs_Texture2D.h>

#include <Rendering/bs_RenderManager.h>
#include <Rendering/bs_RenderBufferObjects.h>
#include <Rendering/bs_Primitive.h>
#include <Rendering/bs_ShaderManager.h>
#include <Rendering/bs_Shader.h>
#include <Time/bs_Clock.h>
#include <Math/bs_math.h>
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

	Sprite* sprite[2];

	void Level::initialize()
	{
		m_cameras.add(new Camera2D());
		Texture2D::setCreationMethod(true, true, OPENGL_COLOR_FORMAT::RGBA);

		Shader* s = (Shader*)ShaderManager::getShader("DefaultSprite/DefaultSprite");

		Texture2D* t = (Texture2D*)ResourceManager::loadTexture2D("x23.png");
		Texture2D* t2 = (Texture2D*)ResourceManager::loadTexture2D("ken.png");

		sprite[0] = RenderManager::addSprite(t, s);
		sprite[1] = RenderManager::addSprite(t2, s);
	}

	void Level::shutDown()
	{
		for (int i = 0; i < m_cameras.count(); i++) delete m_cameras[i];
		m_cameras.~Array();
	}

	void Level::update(f32 dt)
	{
		
		
		Vector2 pos = sprite[1]->position();
		f32 now = Clock::now();

		pos.y = math::sin(now);

		sprite[1]->setPosition(pos);

		RenderManager::render(m_cameras);
		
	}
}

