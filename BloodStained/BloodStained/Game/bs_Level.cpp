#include "bs_Level.h"
#include "Entity/bs_Entity.h"
#include "../Globals/bs_globals.h"
#include "../Rendering/bs_Camera2D.h"
namespace bs
{
	Level::Level()
		:m_name("New Bloodstained Level"),
		m_levelScript(nullptr)
	{

	}

	Level::Level(const Level& l)
		:m_name(l.m_name),
		m_entities(l.m_entities),
		m_levelScript(l.m_levelScript)
	{

	}

	Level::Level(String name)
		: m_name(name),
		m_levelScript(nullptr)
	{

	}

	Level::~Level()
	{

	}

	void Level::render()
	{
		if (m_levelScript) m_levelScript->render (this);
		ui32 count = m_cameras2D.count();
		for (ui32 i = 0; i < count; i++)
		{
			g_spriteRenderer.render(m_cameras2D[i]);
		}
		for (ui32 i = 0; i < count; i++)
		{
			g_debugRenderer.render(m_cameras2D[i]);
		}

		for (ui32 i = 0; i < count; i++)
		{
			
		}
	}

	ERROR_ID Level::initialize()
	{
		m_cameraAllocator.initialize();
		if (m_levelScript) m_levelScript->initialize(this);

		return ERROR_ID::NONE;
	}

	ERROR_ID Level::shutDown()
	{
		if (m_levelScript)
		{
			m_levelScript->shutDown();
			delete m_levelScript;
		}
		m_entities.destroy();
		m_name.clearFromMemory();

		ui32 count = m_cameras2D.count();
		for (ui32 i = 0; i < count; i++)
		{
			m_cameraAllocator.deallocate(m_cameras2D[i]);
		}

		m_cameras2D.reset();
		m_cameraAllocator.shutDown();

		return ERROR_ID::NONE;
	}

	void Level::update(f32 dt)
	{
		g_inputManager.update();
		if (m_levelScript) m_levelScript->execute(this,dt);
		g_inputManager.resetDeltas();
	}

	void Level::setName(String name)
	{
		m_name = name;
	}

	Entity* Level::addEntity()
	{
		return m_entities.construct();
	}

	void	Level::removeEntity(Entity* e)
	{
		m_entities.remove(e);
	}

	Camera2D*	Level::addCamera2D()
	{
		ui32 index = m_cameras2D.add(m_cameraAllocator.allocate());
		return m_cameras2D[index];
	}

	Camera2D*	Level::getCamera2D(ui32 index)
	{
		return m_cameras2D[index];
	}
}