#include	"bs_Event.h"
#include <Events/bs_EventManager.h>

namespace bs
{
	EventDispatcher::EventDispatcher()
	{

	}

	EventDispatcher::EventDispatcher(EVENT_ID id):
		m_id(id)
	{
	}

	EventDispatcher::EventDispatcher(const EventDispatcher & e):
		m_id(e.m_id),
		m_members(e.m_members)
	{
	}

	EventDispatcher::~EventDispatcher()
	{
	}

	void EventDispatcher::addListener(BaseMemberFunction<void, Event>* function)
	{
		m_members.add(function);
	}

	void EventDispatcher::dispatch(Event event)
	{
		ptrsize count = m_members.count();

		for (ptrsize i = 0; i < count; i++)
		{
			if(m_members[i]->canExecute())
				(*m_members[i])(event);
		}
	}

	BaseMemberFunction<void, Event>* EventDispatcher::removeListener(BaseMemberFunction<void, Event>* function)
	{
		ptrsize count = m_members.count();
		BaseMemberFunction<void, Event>* result = nullptr;

		for (ptrsize i = 0; i < count; i++)
		{
			if (*m_members[i] == *function)
			{
				result = m_members[i];
				m_members.swapAndRemove(i);
				break;
			}
		}

		return result;
	}
}