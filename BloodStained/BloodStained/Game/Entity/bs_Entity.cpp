#include "bs_Entity.h"


namespace bs
{
	Entity::Entity()
	{

	}

	Entity::Entity(const Entity& e)
	{

	}

	Entity::~Entity()
	{
		ui32 count = m_components.count();
		for (ui32 i = 0; i < count; i++) g_componentManager.removeComponent(m_components[i]);
	}
}