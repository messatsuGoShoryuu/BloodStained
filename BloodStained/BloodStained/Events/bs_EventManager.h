#ifndef _BS_EVENTMANAGER_H_
#define _BS_EVENTMANAGER_H_

#include <Utilities/bs_Error.h>
#include <Allocator/bs_PoolAllocator.h>
#include "bs_Event.h"

namespace bs
{
	class EventManager
	{
	public:

		static	ERROR_ID initialize();
		static	ERROR_ID shutdown();

	private:
		EventManager(const EventManager& e);

	public:
		template <class T>	
		static	void addListener(T* item, EVENT_FUNCTION(function), EVENT_ID id);

		template <class T>
		static	void removeListener(T* item, EVENT_FUNCTION(function), EVENT_ID id);

		static	void dispatch(EVENT_ID id, void* data);

		template<class T>
		static	MemberFunction<T, void, Event>* allocateFunction(T* item, EVENT_FUNCTION(function), EVENT_ID id);

		inline static void deallocateFunction(BaseMemberFunction<void, Event>* function)
		{
			s_functions.deallocate(reinterpret_cast<MemberFunction<nothing,void,Event>*>(function));
		}

	private:
		static	PoolAllocator<MemberFunction<nothing, void, Event>>	s_functions;
		static	Array<EventDispatcher>								s_dispatchers;
	};

	template<class T>
	inline void EventManager::addListener(T * item, EVENT_FUNCTION(function) , EVENT_ID id)
	{
		
		
		MemberFunction<T, void, Event>* funcPtr = allocateFunction(item, function, id);
		funcPtr->setCaster(item);

		assert((ptrsize)id < s_dispatchers.count());

		s_dispatchers[(ptrsize)id].addListener(ptr);
	}

	template<class T>
	inline void EventManager::removeListener(T * item, EVENT_FUNCTION(function) , EVENT_ID id)
	{
		MemberFunction<T, void, Event> memberFunction(function);
		memberFunction.setCaster(item);
		BaseMemberFunction<void, Event>* funcPtr = s_dispatchers[(int)id].removeListener();
		s_functions.deallocate(funcPtr);
	}

	template<class T>
	inline MemberFunction<T, void, Event>* EventManager::allocateFunction(T * item, EVENT_FUNCTION(function), EVENT_ID id)
	{
		MemberFunction<nothing, void, Event>* ptr = s_functions.allocate();
		new(ptr) MemberFunction<T, void, Event>(function);
		return reinterpret_cast<MemberFunction<T, void, Event>*>(ptr);
	}
}

#endif // !_BS_EVENTMANAGER_H_
