#ifndef BS_COMPONENT_H
#define BS_COMPONENT_H

#include "../../../Utilities/bs_types.h"

namespace bs
{
	//Forward declarations:
	class Entity;

	typedef	ui32 ComponentType;

	//Base component interface.
	class BaseComponent
	{
		friend class Entity;
		friend class ComponentManager;
	public:
		//Default constructor.
		BaseComponent();
		//Copy constructor.
		BaseComponent(const BaseComponent& c);
		//Initialize type.
		explicit BaseComponent(ComponentType type);

		//Destructor.
		virtual ~BaseComponent();

		//Entity setter/getter.
		const	Entity*	owner();
		const	Entity*	owner() const;

		void	setOwner(Entity*	owner);

	protected:
		static	ComponentType	sm_typeCount;

		//Owning entity.
		Entity*	m_owner;

	private:
		const	ComponentType m_type;
	};

	//Templated component interface.
	template<class T>
	class Component : public BaseComponent
	{
	public:
		//Default constructor.
		Component();
		//Copy constructor.
		Component(const Component& c);
		//Destructor.
		virtual ~Component();

		static	ComponentType	type();
	};

	template<class T>
	Component<T>::Component()
		:BaseComponent(type())
	{

	}

	template<class T>
	Component<T>::Component(const Component<T>& c)
		:BaseComponent(c)
	{

	}

	template<class T>
	Component<T>::~Component()
	{

	}

	template<class T>
	ComponentType	Component<T>::type()
	{
		static ComponentType type = sm_typeCount++;
		return type;
	}
}

#endif // !BS_COMPONENT_H
