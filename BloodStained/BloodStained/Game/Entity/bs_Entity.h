#ifndef BS_ENTITY_H
#define BS_ENTITY_H

#include "Component/bs_ComponentManager.h"

namespace bs
{

	//Any object that can be utilized in a game.
	class Entity
	{
	public:
		Entity();
		Entity(const Entity& e);
		~Entity();

		template<class T>
		T*	addComponent();
		
		template <class T>
		T*	getComponent();

		template <class T>
		void	removeComponent();

	private:
		Array<BaseComponent*>	m_components;
	};

	template<class T>
	T*	Entity::getComponent()
	{
		ui32 componentCount = m_components.count();
		if (componentCount == 0) return nullptr;

		for (ui32 i = 0; i < componentCount; i++)
		{
			if (m_components[i]->m_type == T::type())
			{
				return reinterpret_cast<T*>(m_components[i]);
			}
		}
		return nullptr;
	}

	template<class T>
	T*	Entity::addComponent()
	{
		T* component = g_componentManager.addComponent<T>();
		m_components.add(component);
		component->setOwner(this);
		return component;
	}

	template<class T>
	void	Entity::removeComponent()
	{
		T* component = getComponent<T>();
		m_components.remove(component);
		g_componentManager.removeComponent(component);
	}
}

#endif // !BS_ENTITY_H
