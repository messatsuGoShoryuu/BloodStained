#ifndef BS_COMPONENTMANAGER_H
#define BS_COMPONENTMANAGER_H

#include "bs_Component.h"
#include "../../../Containers/bs_HashMap.h"
#include "../../../Containers/bs_LinkedArray.h"
#include "../../../Containers/bs_Array.h"

namespace bs
{
	
	typedef ui32 ComponentType;

	class BaseComponentArray
	{
	public:
		BaseComponentArray()
		{

		}
		virtual ~BaseComponentArray()
		{

		}
	};

	template <class T>
	class ComponentArray : public BaseComponentArray
	{
	public:
		ComponentArray()
		{

		}

		ComponentArray(const ComponentArray& c)
			:array(c.array)
		{

		}

		virtual ~ComponentArray()
		{
			this->array.destroy();
		}

		LinkedArray<T>	array;
	};


	class ComponentManager
	{
	public:
		ComponentManager();
		~ComponentManager();

	private:
		ComponentManager(const ComponentManager& c);

	public:
		template<class T>
		void	createComponentArray();

		template<class T>
		T*	addComponent();

		template <class T>
		void	removeComponent(T* item);
		
	public:
		bool	initialize();
		bool	shutDown();

	private:
		//Component storage:
		HashMap<ComponentType, BaseComponentArray*>	m_components;
		//Used for iteration
		Array<ComponentType>	m_usedTypes;
	};

	template<class T>
	void	ComponentManager::createComponentArray()
	{
		ComponentType type = T::type();
		if (m_components.isEmptyAt(type))
		{
			m_components[type] = new ComponentArray<T>();
			m_usedTypes.add(type);
		}
	}

	template <class T>
	T*	ComponentManager::addComponent()
	{
		//This function will do nothing if there is already an array for this type of component.
		createComponentArray<T>();
		ComponentArray<T>* a = reinterpret_cast<ComponentArray<T>*>(m_components[T::type()]);
		return a->array.construct();
	}

	template<class T>
	void	ComponentManager::removeComponent(T* item)
	{
		ComponentType type = item->m_type;
		if (m_components.isEmptyAt(type)) return;

		ComponentArray<T>* a = reinterpret_cast<ComponentArray<T>*>(m_components[type]);
		a->array.remove(item);
	}

	extern	ComponentManager	g_componentManager;
}

#endif // !BS_COMPONENTMANAGER_H
