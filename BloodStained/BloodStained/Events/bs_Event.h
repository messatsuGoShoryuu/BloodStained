#ifndef _BS_EVENT_H_
#define _BS_EVENT_H_


#include <Functions/bs_MemberFunction.h>
#include <Containers/bs_Array.h>

#define EVENT_FUNCTION(f) void(T::*f)(Event)

namespace bs
{

	enum class EVENT_ID
	{
		LEVEL_LOADED,
		LEVEL_UNLOADED,
		ENTITY_CREATED,
		ENTITY_DESTROYED,
		COLLISION_BEGIN,
		COLLISION_END,
	};

	struct Event
	{
		EVENT_ID id;
		void* data;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher();
		EventDispatcher(EVENT_ID id);
		EventDispatcher(const EventDispatcher& e);
		~EventDispatcher();

	public:
		void addListener(BaseMemberFunction<void, Event>* function);
		void dispatch(Event event);
		inline const bool canDispatch()const { return m_members.count() > 0; }
		BaseMemberFunction<void, Event>* removeListener(BaseMemberFunction<void, Event>* function);

	private:
		EVENT_ID m_id;
		Array<BaseMemberFunction<void, Event>*> m_members;
	};
}

#endif // !_BS_EVENT_H_
