#include "bs_EventManager.h"

namespace bs
{
	PoolAllocator<MemberFunction<nothing, void, Event>>	EventManager::s_functions;
	Array<EventDispatcher>								EventManager::s_dispatchers;

	ERROR_ID EventManager::initialize()
	{
		new(&s_functions) PoolAllocator<MemberFunction<void, void, Event>>(1024);

		s_functions.initialize();
		s_dispatchers.resize(4096);

		return ERROR_ID::NONE;
	}
	ERROR_ID EventManager::shutdown()
	{
		return ERROR_ID::NONE;
	}

	void EventManager::dispatch(EVENT_ID id, void* data)
	{
		Event e;
		e.id = id;
		e.data = data;
		s_dispatchers[(ptrsize)id].dispatch(e);
	}
}