#include "bs_ComponentManager.h"

namespace bs
{
	ComponentManager::ComponentManager()
	{

	}

	ComponentManager::~ComponentManager()
	{

	}

	bool ComponentManager::initialize()
	{
		return true;
	}

	bool ComponentManager::shutDown()
	{
		for (ui32 i = 0; i < m_usedTypes.count(); i++)
		{
			delete (m_components[m_usedTypes[i]]);
		}

		m_components.reset();
		m_usedTypes.reset();
		return true;
	}
}