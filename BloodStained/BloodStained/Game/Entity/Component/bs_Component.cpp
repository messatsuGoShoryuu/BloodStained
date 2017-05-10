#include "bs_Component.h"
#include "../bs_Entity.h"

namespace bs
{
	ComponentType BaseComponent::sm_typeCount = 0;

	BaseComponent::BaseComponent()
		:m_owner(nullptr),
		m_type(0)
	{

	}

	BaseComponent::BaseComponent(const BaseComponent& c)
		: m_owner(c.m_owner),
		m_type(c.m_type)
	{

	}

	BaseComponent::BaseComponent(ComponentType type)
		:m_type(type)
	{

	}

	BaseComponent::~BaseComponent()
	{

	}

	const	Entity*	BaseComponent::owner()			{ return m_owner; }
	const	Entity*	BaseComponent::owner()	const	{ return m_owner; }
	


	void	BaseComponent::setOwner(Entity*	owner){ m_owner = owner; }
}