#ifndef _BS_LINKEDARRAY_H_
#define _BS_LINKEDARRAY_H_

#include "../Allocator/bs_Memory.h"
#include "../Allocator/bs_PoolAllocator.h"

#ifdef BS_ASSERT
#include <assert.h>
#endif

#define DEFINE_CONSTRUCT_FUNCTION(TYPES,ARGS,PARAMS)	template<TYPES> \
														T* construct(ARGS) \
														{ \
															if (isFull()) return nullptr; \
															LinkedArrayRegistry<T>* r = _findAvailableRegistry(); \
															Place((&r->item), T, PARAMS); \
															r->isEmpty = false; \
															m_itemCount++; \
															return &r->item; \
														}


namespace bs
{
	//This struct will store linked array items.
	template<class T>
	struct LinkedArrayRegistry
	{
		T		item;
		bool	isEmpty; //For O(1) removal 
	};


	//A pool of LinkedArrayRegistries.
	template<class T>
	class LinkedArrayPool
	{
	public:
		//Default constructor and destructor.
		LinkedArrayPool();
		~LinkedArrayPool();

		//Copy constructor.
		LinkedArrayPool(const LinkedArrayPool& l);

		//@count: specify item count in pool.
		LinkedArrayPool(ui32 count, ui32 id);

	public:
		//This is where the initialization is done.
		//Allocation and size calculation is done once until destruction.
		bool initialize();

		//Manual destruction method.
		void destroy();

	public:
		//Add and remove
		T*	add(const T& item);

		T*	construct();
		//Define multiple argument versions, up to 6 arguments.
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_1, MULTIPLE_ARGS_1, MULTIPLE_PARAMS_1)
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_2, MULTIPLE_ARGS_2, MULTIPLE_PARAMS_2)
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_3, MULTIPLE_ARGS_3, MULTIPLE_PARAMS_3)
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_4, MULTIPLE_ARGS_4, MULTIPLE_PARAMS_4)
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_5, MULTIPLE_ARGS_5, MULTIPLE_PARAMS_5)
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_6, MULTIPLE_ARGS_6, MULTIPLE_PARAMS_6)

		void remove(T* item);

	public:
		//Operators

		LinkedArrayRegistry<T>* operator[](ui32 index);
		const LinkedArrayRegistry<T>* operator[](ui32 index) const;

		void operator=(const LinkedArrayPool<T>& l);

	public:
		//Linked list setters and getters
		void setNext(LinkedArrayPool<T>* next){ m_next = next; }
		void setPrevious(LinkedArrayPool<T>* previous){ m_previous = previous; }

		LinkedArrayPool<T>*			next()				{ return m_next; }
		const LinkedArrayPool<T>*	next() const		{ return m_next; }
		LinkedArrayPool<T>*			previous()			{ return m_previous; }
		const LinkedArrayPool<T>*	previous() const	{ return m_previous; }

	public:
		//Retrieve info
		inline	const ui32	itemCount()			{ return m_itemCount; }
		inline	const ui32	itemCount() const	{ return m_itemCount; }

		inline	const ui32	id()				{ return m_id; }
		inline	const ui32	id()		const	{ return m_id; }

		inline	const bool	isFull()			{ return m_itemCount >= m_poolSize; }
		inline	const bool	isFull()	const	{ return m_itemCount >= m_poolSize; }
		inline	const bool	isEmpty()			{ return m_itemCount == 0; }
		inline	const bool	isEmpty()	const	{ return m_itemCount == 0; }

		inline	const ui32	maxIndex()			{ return m_maxIndex; }
		inline	const ui32	maxIndex()	const	{ return m_maxIndex; }
		inline	const ui32	minIndex()			{ return m_minIndex; }
		inline	const ui32	minIndex()	const	{ return m_minIndex; }

		inline	const bool	contains(T* item)		{ return (ui32)item >= (ui32)m_buffer && (ui32)item < (ui32)m_buffer + m_itemCount * m_itemSize; }
		inline	const bool	contains(T* item) const	{ return (ui32)item >= (ui32)m_buffer && (ui32)item < (ui32)m_buffer + m_itemCount * m_itemSize; }

	private:
		//Call destructors of all active items.
		void _destroyItems();

		//Cast byte to registry
		LinkedArrayRegistry<T>*	_readAsRegistry(ui32 index);
		const LinkedArrayRegistry<T>*	_readAsRegistry(ui32 index) const;


		//Find available registry
		LinkedArrayRegistry<T>* _findAvailableRegistry();
		LinkedArrayRegistry<T>* _findAvailableRegistry(ui32 min, ui32 max);
		LinkedArrayRegistry<T>* _getAvailableRegistry(ui32 index);


		//Copy data from other
		void _copy(const LinkedArrayPool& other);

		//Find maximum and minimum indexes.

		void _findMaxIndex(ui32 offset);
		void _findMinIndex(ui32 offset);


	private:
		//Buffer, presented in bytes since the size of T can be anything.
		byte* m_buffer;

		//Sizeof(T)
		ui32 m_itemSize;

		//Size of pool (max item count).
		ui32 m_poolSize;

		//Current item count.
		ui32 m_itemCount;

		//Handle of first available item.
		ui32 m_firstAvailableSlot;

		//Lower index bounds.
		ui32 m_minIndex;
		//Higher index bounds.
		ui32 m_maxIndex;

		//Id of the pool (for indexing in linked list).
		ui32 m_id;

		//Doubly linked list
		LinkedArrayPool<T>* m_previous;
		LinkedArrayPool<T>* m_next;
	};


	//Default constructor.
	template <class T>
	LinkedArrayPool<T>::LinkedArrayPool()
		: m_poolSize(256),
		m_itemCount(0),
		m_firstAvailableSlot(0),
		m_minIndex(0),
		m_maxIndex(0),
		m_id(0),
		m_buffer(nullptr),
		m_previous(nullptr),
		m_next(nullptr)
	{
		
	}

	//Default destructor.
	template <class T>
	LinkedArrayPool<T>::~LinkedArrayPool()
	{
		if (m_itemCount > 0 && m_buffer) destroy();
		else if (m_buffer) BS_Free(m_buffer);
	}

	//Copy constructor.
	template <class T>
	LinkedArrayPool<T>::LinkedArrayPool(const LinkedArrayPool<T>& l)
		: m_poolSize(l.m_poolSize),
		m_itemSize(l.m_itemSize),
		m_itemCount(l.m_itemCount),
		m_minIndex(l.m_minIndex),
		m_maxIndex(l.m_maxIndex),
		m_firstAvailableSlot(l.m_firstAvailableSlot),
		m_id(l.m_id),
		m_buffer(nullptr),
		m_previous(nullptr),
		m_next(nullptr)
	{
		_copy(l);
	}

	//Parametered constructor:
	//@poolSize : size in item count of pool
	template <class T>
	LinkedArrayPool<T>::LinkedArrayPool(ui32 poolSize, ui32 id)
		: m_buffer(nullptr),
		m_poolSize(poolSize),
		m_itemCount(0),
		m_minIndex(0),
		m_maxIndex(0),
		m_firstAvailableSlot(0),
		m_id(id),
		m_previous(nullptr),
		m_next(nullptr)
	{
		
	}


	//Initialization function:

	template<class T>
	bool LinkedArrayPool<T>::initialize()
	{
		//calculate total pool size in bytes
		m_itemSize = sizeof(LinkedArrayRegistry<T>);
		ui32 poolBytes = m_itemSize * m_poolSize;

		//request bytes from heap
		m_buffer = (byte*)BS_Malloc(poolBytes);

#ifdef BS_ASSERT
		assert(m_buffer);
#endif
		memset(m_buffer, -1, poolBytes);

		//return
		if (!m_buffer) return false;
		return true;
	}

	//Manual destructor
	template <class T>
	void LinkedArrayPool<T>::destroy()
	{
		//Call destructors
		_destroyItems();

		//Return bytes to heap
		BS_Free(m_buffer);

		//Reset to default
		m_buffer = nullptr;
		m_firstAvailableSlot = 0;
		m_poolSize = 256;
		m_minIndex = 0;
		m_maxIndex = 0;
	}

	//Add and remove
	
	template<class T>
	T*	LinkedArrayPool<T>::construct()
	{
		if (isFull()) return nullptr; 
		LinkedArrayRegistry<T>* r = _findAvailableRegistry(); 
		Place((&r->item), T,); 
		r->isEmpty = false; 
		m_itemCount++; 
		return &r->item; 
	}

	template <class T>
	T* LinkedArrayPool<T>::add(const T& item)
	{
		//Can't add if full.
		if (isFull()) return nullptr;

		//Find an empty slot and construct object
		LinkedArrayRegistry<T>* r = _findAvailableRegistry();

#ifdef BS_ASSERT
		assert(r);
#endif
		Place((&r->item), T, item);
		r->isEmpty = false;

		m_itemCount++;
		return &r->item;
	}

	template <class T>
	void LinkedArrayPool<T>::remove(T* item)
	{
		//Offset to registry point.
		byte* rawPtr = reinterpret_cast<byte*>(item);

#ifdef BS_ASSERT
		assert(rawPtr >= m_buffer);
		assert(rawPtr < m_buffer + m_poolSize * m_itemSize);
#endif

		//Destroy item.
		LinkedArrayRegistry<T>* r = reinterpret_cast<LinkedArrayRegistry<T>*>(rawPtr);
		
		Destroy((&r->item), T);
		r->isEmpty = true;

		//If this is the last item reset min and max indexes
		if (m_itemCount == 1)
		{
			m_minIndex = 0;
			m_maxIndex = 0;
		}
		else
		{
			//If this is the max index find update max index.
			LinkedArrayRegistry<T>* rX = SELF[m_maxIndex];
			if (rX == r)_findMaxIndex(m_maxIndex);

			//If this is the min index find update min index.
			rX = SELF[m_minIndex];
			if (rX == r)_findMinIndex(m_minIndex);
		}

#ifdef BS_ASSERT
		assert(m_maxIndex >= m_minIndex);
#endif

		memset(r, -1, m_itemSize);

		

		m_itemCount--;
	}

	template <class T>
	LinkedArrayRegistry<T>* LinkedArrayPool<T>::operator[](ui32 index)
	{
		ui32 byteIndex = index * m_itemSize;
		return _readAsRegistry(byteIndex);
	}

	template <class T>
	const LinkedArrayRegistry<T>* LinkedArrayPool<T>::operator[](ui32 index) const
	{
		ui32 byteIndex = index * m_itemSize;
		return _readAsRegistry(byteIndex);
	}

	template<class T>
	void LinkedArrayPool<T>::operator=(const LinkedArrayPool<T>& l)
	{
		m_poolSize = l.m_poolSize;
		m_itemSize = l.m_itemSize;
		m_itemCount = l.m_itemCount;
		m_firstAvailableSlot = l.m_firstAvailableSlot;
		m_maxIndex = l.m_maxIndex;
		m_minIndex = l.m_minIndex;
		_copy(l);
	}


	template <class T>
	LinkedArrayRegistry<T>* LinkedArrayPool<T>::_readAsRegistry(ui32 index)
	{
		byte* ptr = m_buffer + index;

#ifdef BS_ASSERT
		assert(ptr >= m_buffer && ptr < m_buffer + (m_poolSize * m_itemSize));
#endif

		LinkedArrayRegistry<T>* registry = reinterpret_cast<LinkedArrayRegistry<T>*>(ptr);

		return registry;
	}

	template <class T>
	const LinkedArrayRegistry<T>* LinkedArrayPool<T>::_readAsRegistry(ui32 index) const
	{
		byte* ptr = m_buffer + index;

#ifdef BS_ASSERT
		assert(ptr >= m_buffer && ptr < m_buffer + (m_poolSize * m_itemSize));
#endif

		LinkedArrayRegistry<T>* registry = reinterpret_cast<LinkedArrayRegistry<T>*>(ptr);
		return registry;
	}

	template <class T>
	LinkedArrayRegistry<T>* LinkedArrayPool<T>::_findAvailableRegistry()
	{
		//We try squeeze data together as much as possible:

		LinkedArrayRegistry<T>* result = _findAvailableRegistry(m_minIndex, m_maxIndex);
		if (result) return result;

		result = _findAvailableRegistry(m_minIndex, 0);
		if (result) return result;

		result = _findAvailableRegistry(m_maxIndex, m_poolSize - 1);
		return result;
	}

	template <class T>
	LinkedArrayRegistry<T>* LinkedArrayPool<T>::_getAvailableRegistry(ui32 index)
	{
		LinkedArrayRegistry<T>* r = SELF[index];
#ifdef BS_ASSERT
		assert(r);
#endif
		if (r->isEmpty)
		{
			m_firstAvailableSlot = index;

			//Update max and min indexes for faster iteration.
			if (index > m_maxIndex) m_maxIndex = index;
			else if (index < m_maxIndex) _findMaxIndex(m_maxIndex);
			if (index < m_minIndex) m_minIndex = index;
			else if (index > m_minIndex) _findMinIndex(m_minIndex);
			return r;
		}
		return nullptr;
	}

	template <class T>
	LinkedArrayRegistry<T>* LinkedArrayPool<T>::_findAvailableRegistry(ui32 min, ui32 max)
	{
		//Check if current slot is available.
		LinkedArrayRegistry<T>* r = SELF[m_firstAvailableSlot];
		if (r->isEmpty) return r;

		//If not iterate until empty one is found.

		//In which order do we iterate?
		bool reverse = false;
		if (min > max) reverse = true;

		if (reverse) //Iterate backwards
		{
			for (i32 i = max; i >= 0; i--)
			{
				r = _getAvailableRegistry(i);
				if (r) return r;
			}
		}
		else //Iterate forwards
		{
			
			for (ui32 i = min; i <= max; i++)
			{
				r = _getAvailableRegistry(i);
				if (r) return r;
			}
		}
		return nullptr;
	}

	template <class T>
	void LinkedArrayPool<T>::_destroyItems()
	{
		//Iterate and destroy all non-empty objects.
		for (ui32 i = 0; i < m_poolSize; i++)
		{
			LinkedArrayRegistry<T>* r = SELF[i];
			if (!r->isEmpty)
			{
				r->isEmpty = true;
				Destroy((&r->item), T);
			}
		}

		memset(m_buffer, -1, m_poolSize * m_itemSize);

		m_itemCount = 0;
	}

	template <class T>
	void LinkedArrayPool<T>::_copy(const LinkedArrayPool<T>& other)
	{
		if(m_buffer) destroy();
		initialize();

		ui32 count = other.m_poolSize;
		for (ui32 i = 0; i < count; i++)
		{
			LinkedArrayRegistry<T>* r0 = SELF[i];
			LinkedArrayRegistry<T>* r1 = (LinkedArrayRegistry<T>*)other[i];
			if (r1->isEmpty) continue;
			Place(r0, T, r1->item);
			r0->isEmpty = false;
		}
	}

	template <class T>
	void LinkedArrayPool<T>::_findMaxIndex(ui32 offset)
	{
#ifdef BS_ASSERT
		assert(offset < m_poolSize);
#endif
		ui32 count = offset == 0 ? m_poolSize - 1 : offset;
		
		for (i32 i = count; i <= 0; i--)
		{
			LinkedArrayRegistry<T>* r = SELF[i];
			if (!r->isEmpty)
			{
				m_maxIndex = i;
				return;
			}
		}
	}

	template <class T>
	void LinkedArrayPool<T>::_findMinIndex(ui32 offset)
	{
#ifdef BS_ASSERT
		assert(offset < m_poolSize);
#endif
		for (i32 i = offset; i < m_poolSize ; i++)
		{
			LinkedArrayRegistry<T>* r = SELF[i];
			if (!r->isEmpty)
			{
				m_minIndex = i;
				return;
			}
		}
	}

	
}

#undef DEFINE_CONSTRUCT_FUNCTION(TYPES,ARGS,PARAMS)

#define DEFINE_CONSTRUCT_FUNCTION(TYPES,ARGS,PARAMS)	template< TYPES > \
														T*	construct(ARGS) \
														{\
															T* result = nullptr; \
															LinkedArrayPool<T>* p = _findAvailablePool(); \
															if (p) result = p->construct(PARAMS); \
															m_lastInsertedPool = p; \
															if (m_lastInsertedPool->id() < m_minPool->id()) m_minPool = m_lastInsertedPool; \
															if (m_lastInsertedPool->id() > m_maxPool->id()) m_maxPool = m_lastInsertedPool; \
															return result; \
														}

namespace bs
{
	//A LinkedArray is a doubly linked list of LinkedArrayPools.
	//It allows instant removal, relatively fast iteration and stable addresses.


	template <class T>
	class LinkedArray
	{
	public:

		//Default constructor.
		LinkedArray();

		//Default destructor.
		~LinkedArray();

		//Copy constructor.
		LinkedArray(const LinkedArray& l);

		//Paremeterized constructor.
		//@poolSize: item count by pool
		LinkedArray(ui32 poolSize);

	public:

		//Add new item:
		T*	add(const T& item);

		T*	construct();

		//Define multiple argument versions, up to 6 arguments.
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_1, MULTIPLE_ARGS_1, MULTIPLE_PARAMS_1)
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_2, MULTIPLE_ARGS_2, MULTIPLE_PARAMS_2)
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_3, MULTIPLE_ARGS_3, MULTIPLE_PARAMS_3)
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_4, MULTIPLE_ARGS_4, MULTIPLE_PARAMS_4)
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_5, MULTIPLE_ARGS_5, MULTIPLE_PARAMS_5)
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_6, MULTIPLE_ARGS_6, MULTIPLE_PARAMS_6)

		//Remove item:
		void	remove(T* item);

		//Manually destroy.
		void	destroy();

	public:
		//Accessors:

		//Item with minimum index.
		const T*		first()		const;

		//Item with maximum index.
		const T*		last()		const;

		ui32			firstIndex() const { return m_minPool->id() * m_poolSize + m_minPool->minIndex(); }
		ui32			lastIndex() const { return m_maxPool->id() * m_poolSize + m_maxPool->maxIndex(); }

		//How many items do we have?
		ui32			count()				{ return m_count; }
		const ui32		count()		const	{ return m_count; }

	public:
		//Operators

		//Random access.
		T*			operator[](ui32 index);
		const T*	operator[](ui32 index) const;

		//Assignment.
		void		operator=(const LinkedArray<T>& other);

	private:
		//Add a new pool.
		bool _addPool();

		//Remove existing pool.
		bool _removePool(LinkedArrayPool<T>* pool);

		//Copy other LinkedArray to this one.
		void _copy(const LinkedArray<T>& other);

		//Find an available pool for insertion.
		LinkedArrayPool<T>*	_findAvailablePool();

		//Find the pool containing item in question.
		LinkedArrayPool<T>*	_findContainingPool(T* item);

		//Find next empty pool.
		LinkedArrayPool<T>* _findMinPool(LinkedArrayPool<T>* startingNode);

		//Find previous empty pool.
		LinkedArrayPool<T>* _findMaxPool(LinkedArrayPool<T>* startingNode);

	private:
		//Linked list of pools:

		//Linked list root:
		LinkedArrayPool<T>*	m_pools;

		//End of list
		LinkedArrayPool<T>*	m_lastPool;

		//Pool which contains minimum index.
		LinkedArrayPool<T>* m_minPool;

		//Pool which contains maximum index.
		LinkedArrayPool<T>* m_maxPool;

		//Last inserted pool node.
		LinkedArrayPool<T>* m_lastInsertedPool;

		//How many items do we have?
		ui32 m_count;

		//Max items per pool
		ui32 m_poolSize;

	private:
		//Pool allocator.
		PoolAllocator<LinkedArrayPool<T>> m_allocator;
	};


	//Default constructor.
	template<class T>
	LinkedArray<T>::LinkedArray()
		:m_pools(nullptr),
		m_lastInsertedPool(nullptr),
		m_lastPool(nullptr),
		m_maxPool(nullptr),
		m_minPool(nullptr),
		m_count(0),
		m_poolSize(256),
		m_allocator(16)
	{

	}

	//Default destructor.
	template<class T>
	LinkedArray<T>::~LinkedArray()
	{
		if (m_pools) destroy();
	}

	//Copy constructor.
	template<class T>
	LinkedArray<T>::LinkedArray(const LinkedArray& l)
		:m_pools(nullptr),
		m_lastInsertedPool(nullptr),
		m_lastPool(nullptr),
		m_maxPool(nullptr),
		m_minPool(nullptr),
		m_count(l.m_count),
		m_poolSize(l.m_poolSize),
		m_allocator(16)
	{
		_copy(l);
	}

	//Paremeterized constructor.
	//@poolSize: item count by pool
	template<class T>
	LinkedArray<T>::LinkedArray(ui32 poolSize)
		:m_pools(nullptr),
		m_lastInsertedPool(nullptr),
		m_lastPool(nullptr),
		m_maxPool(nullptr),
		m_minPool(nullptr),
		m_count(0),
		m_poolSize(poolSize),
		m_allocator(16)
	{

	}

	//Add new item:
	template<class T>
	T*	LinkedArray<T>::add(const T& item)
	{
		T* result = nullptr;

		//Find the most available pool.
		LinkedArrayPool<T>* p = _findAvailablePool();

		//Insert item.
		if (p) result = p->add(item);
		m_lastInsertedPool = p;

		if (m_lastInsertedPool->id() < m_minPool->id()) m_minPool = m_lastInsertedPool;
		if (m_lastInsertedPool->id() > m_maxPool->id()) m_maxPool = m_lastInsertedPool;

		return result;
	}

	template<class T>
	T*	LinkedArray<T>::construct()
	{

		T* result = nullptr; 
		LinkedArrayPool<T>* p = _findAvailablePool(); 
		if (p) result = p->construct(); 
		m_lastInsertedPool = p; 
		if (m_lastInsertedPool->id() < m_minPool->id()) m_minPool = m_lastInsertedPool; 
		if (m_lastInsertedPool->id() > m_maxPool->id()) m_maxPool = m_lastInsertedPool; 
		return result; 

	}

	//Remove item:

	template<class T>
	void	LinkedArray<T>::remove (T* item)
	{
		//Find the containing pool.
		LinkedArrayPool<T>* p = _findContainingPool(item);

		//Return if no pool is found (shouldn't happen unless m_count == 0).
		if (!p) return;

		//Remove the item
		p->remove(item);

		//If we emptied p, update min and max pool values.
		if (p->isEmpty())
		{
			ui32 id = p->id();
			ui32 maxId = m_maxPool->id();
			ui32 minId = m_minPool->id();

			if (id == minId) m_minPool = _findMinPool(p);
			if (id == maxId) m_maxPool = _findMaxPool(p);
		}
	}

	//Manually destroy.
	template<class T>
	void	LinkedArray<T>::destroy()
	{
		//Check if linked list exist.
		if (!m_pools) return;

		LinkedArrayPool<T>* p = m_pools;
		LinkedArrayPool<T>* next = p->next();

		//Traverse linked list.
		while (p)
		{
			//Buffer the next node
			next = p->next();

			//Destroy current node
			p->destroy();
			m_allocator.deallocate(p);

			//If there is a node left, we update pointers.
			if (next)
			{
				next->setPrevious(nullptr);
			}
			p = next;
		}

		m_pools = nullptr; 

		//Clean up allocator
		m_allocator.shutDown();
	}

	template <class T>
	bool LinkedArray<T>::_addPool()
	{
		//ID of th new pool
		ui32 id = 0;
		if (m_pools) id = m_lastPool->id() + 1;

		//Allocate and construct object.
		LinkedArrayPool<T>* p = m_allocator.allocate(m_poolSize, id);
		p->initialize();

		//Any errors in memory allocation?
		if (!p) return false;

		//If the linked list is empty, the node is p.
		if (!m_pools)
		{
			m_pools = p;
			m_lastInsertedPool = p;
			m_minPool = p;
			m_maxPool = p;
		}
		else
		{
			//Else the last one is p.
			m_lastPool->setNext(p);
			p->setPrevious(m_lastPool);
		}
		
		m_lastPool = p;

		return true;
	}

	//Remove existing pool.
	template <class T>
	bool LinkedArray<T>::_removePool(LinkedArrayPool<T>* pool)
	{
		//Nothing to remove
		if (!m_pools) return false;

		LinkedArrayPool<T>* p = m_pools;

		//Traverse until object is found.
		while (p)
		{
			if (p == pool)
			{
				//If item is found remove it and link its neighbours

				LinkedArrayPool<T>* previous = p->previous();
				LinkedArrayPool<T>* next = p->next();

				if (previous)
				{
					if (next)
						previous->setNext(next);
					else previous->setNext(nullptr);
				}
				if (next)
				{
					if (previous)
						next->setPrevious(previous);
					else next->setPrevious(nullptr);
				}

				m_allocator.deallocate(p);

				return true;
			}
		}

		return false;
	}

	//Copy other LinkedArray to this one.
	template <class T>
	void LinkedArray<T>::_copy(const LinkedArray<T>& other)
	{
		//Destroy previous content.
		if (m_pools) destroy();
		m_pools = nullptr;

		LinkedArrayPool<T>* o = other.m_pools;
		LinkedArrayPool<T>* p = nullptr;

		ui32 lastInsertedId = other.m_lastInsertedPool->id();
		ui32 minPool = other.m_minPool->id();
		ui32 maxPool = other.m_maxPool->id();
		ui32 lastPool = other.m_lastPool->id();


		//Traverse the pool and copy the content of each pool.
		while (o)
		{
			p = m_allocator.allocate(other.m_poolSize, o->id());

			//If this is the first pool, assign.
			if (!m_pools) m_pools = p;

			//Copy content
			*p = *o;

			ui32 id = o->id();
			if (id == lastInsertedId) m_lastInsertedPool = p;
			if (id == minPool) m_minPool = p;
			if (id == maxPool) m_maxPool = p;
			if (id == lastPool) m_lastPool = p;

			//Update pointers. 
			p = p->next();
			o = o->next();
		}
	}


	//Find an available pool for insertion.
	template <class T>
	LinkedArrayPool<T>*	LinkedArray<T>::_findAvailablePool()
	{
		if (m_pools)
		{
			if (!m_lastInsertedPool->isFull()) return m_lastInsertedPool;

			LinkedArrayPool<T>* c = m_lastInsertedPool ? m_lastInsertedPool : m_minPool;
			LinkedArrayPool<T>* p = m_lastInsertedPool->previous();
			LinkedArrayPool<T>* n = m_lastInsertedPool->next();

			while (p)
			{
				if (!p->isFull()) return p;
				p = p->previous();
			}

			while (n)
			{
				if (!n->isFull()) return n;
				n = n->next();
			}
		}

		_addPool();
		return m_lastPool;
	}

	//Find the pool containing item in question.
	template <class T>
	LinkedArrayPool<T>*	LinkedArray<T>::_findContainingPool(T* item)
	{
		LinkedArrayPool<T>* min = m_minPool;
		LinkedArrayPool<T>* max = m_maxPool;
		ui32 maxId = max->id();

		for (; min->id() <= maxId ; min = min->next())
		{
			if (!min) return nullptr;
			if (min->contains(item)) return min;
		}

		return nullptr;
	}

	//Find next empty pool.
	template <class T>
	LinkedArrayPool<T>* LinkedArray<T>::_findMinPool(LinkedArrayPool<T>* startingNode)
	{
		LinkedArrayPool<T>* p = startingNode;
		while (p)
		{
			if (!p->isFull()) return p;
			p = p->next();
		}

		return nullptr;
	}

	//Find previous empty pool.
	template <class T>
	LinkedArrayPool<T>* LinkedArray<T>::_findMaxPool(LinkedArrayPool<T>* startingNode)
	{
		LinkedArrayPool<T>* p = startingNode;
		while (p)
		{
			if (!p->isFull()) return p;
			p = p->previous();
		}

		return nullptr;
	}

	//Operators

	//Random access.
	template <class T>
	T*			LinkedArray<T>::operator[](ui32 index)
	{
		if (!m_pools) return nullptr;

		//Calculate pool ids
		ui32 poolId = index / m_poolSize;
		ui32 localId = index % m_poolSize;
		
		ui32 minId = m_minPool->id();
		ui32 maxId = m_maxPool->id();

		LinkedArrayPool<T>* p = nullptr;

		//Setup starting points
		if (poolId < minId) p = m_pools;
		else if (poolId < maxId) p = m_minPool;
		else p = m_maxPool;

		//Traverse until correct pool is found.
		while (p && p->id() != poolId)
			p = p->next();

		//Return null if no pool is found.
		if (!p) return nullptr;

		//Return the address of the correct item.

		LinkedArrayRegistry<T>* r = (*p)[localId];
		if (r->isEmpty) return nullptr;
		return &(r->item);
	}

	template <class T>
	const T*	LinkedArray<T>::operator[](ui32 index) const
	{
		if (!m_pools) return nullptr;

		//Calculate pool ids
		ui32 poolId = index / m_poolSize;
		ui32 localId = index % m_poolSize;

		ui32 minId = m_minPool->id();
		ui32 maxId = m_maxPool->id();

		LinkedArrayPool<T>* p = nullptr;

		//Setup starting points
		if (poolId < minId) p = m_pools;
		else if (poolId < m_maxPool) p = m_minPool;
		else poolId = m_maxPool;

		//Traverse until correct pool is found.
		while (p && p->id() != poolId)
			p = p->next();

		//Return null if no pool is found.
		if (!p) return nullptr;

		//Return the address of the correct item.
		return &((*p)[localId]);
	}

	//Assignment.
	template <class T>
	void		LinkedArray<T>::operator=(const LinkedArray<T>& other)
	{
		m_count = l.m_count;
		m_poolSize = l.m_poolSize;

		_copy();
	}

}


#undef DEFINE_CONSTRUCT_FUNCTION(TYPES,ARGS,PARAMS)


#endif // !BS_LINKEDARRAY_H
