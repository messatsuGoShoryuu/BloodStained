#ifndef BS_LINKEDARRAY_H
#define BS_LINKEDARRAY_H

#include "../Allocator/bs_Memory.h"

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
		LinkedArrayPool(ui32 count);

	public:
		//This is where the initialization is done.
		//Allocation and size calculation is done once until destruction.
		bool initialize();

		//Manual destruction method.
		void destroy();

	public:
		//Add and remove
		T*	add(const T& item);

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

		void operator=(const LinkedArrayRegistry<T>& l);

	public:
		//Linked list setters and getters
		void setNext(const LinkedArrayPool<T>* next){ m_next = next; }
		void setPrevious(const LinkedArrayPool<T>* previous){ m_previous = previous; }

		LinkedArrayPool<T>*			next()				{ return m_next; }
		const LinkedArrayPool<T>*	next() const		{ return m_next; }
		LinkedArrayPool<T>*			previous()			{ return m_previous; }
		const LinkedArrayPool<T>*	previous() const	{ return m_previous; }

	public:
		//Retrieve info
		ui32		itemCount()			{ return m_itemCount; }
		const ui32	itemCount() const	{ return m_itemCount; }

		bool		isFull()			{ return m_itemCount >= m_poolSize; }
		const bool	isFull()	const	{ return m_itemCount >= m_poolSize; }
		bool		isEmpty()			{ return m_itemCount == 0; }
		const bool	isEmpty()	const	{ return m_itemCount == 0; }

	private:
		//Call destructors of all active items.
		void _destroyItems();

		//Cast byte to registry
		LinkedArrayRegistry<T>*	_readAsRegistry(ui32 index);
		const LinkedArrayRegistry<T>*	_readAsRegistry(ui32 index) const;


		//Find available registry
		LinkedArrayRegistry<T>* _findAvailableRegistry();


		//Copy data from other
		void _copy(const LinkedArrayPool& other);


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
		m_buffer(nullptr),
		m_previous(nullptr),
		m_next(nullptr)
	{
		initialize();
	}

	//Default destructor.
	template <class T>
	LinkedArrayPool<T>::~LinkedArrayPool()
	{
		if (m_itemCount > 0 && m_buffer) destroy();
	}

	//Copy constructor.
	template <class T>
	LinkedArrayPool<T>::LinkedArrayPool(const LinkedArrayPool<T>& l)
		: m_poolSize(l.m_poolSize),
		m_itemSize(l.m_itemSize),
		m_itemCount(l.m_itemCount),
		m_firstAvailableSlot(l.m_firstAvailableSlot),
		m_buffer(nullptr),
		m_previous(nullptr),
		m_next(nullptr)
	{
		initialize();
	}

	//Parametered constructor:
	//@poolSize : size in item count of pool
	template <class T>
	LinkedArrayPool<T>::LinkedArrayPool(ui32 poolSize)
		: m_buffer(nullptr),
		m_poolSize(poolSize),
		m_itemCount(0),
		m_firstAvailableSlot(0),
		m_previous(nullptr),
		m_next(nullptr)
	{
		initialize();
	}


	//Initialization function:

	template<class T>
	bool LinkedArrayPool<T>::initialize()
	{
		//calculate total pool size in bytes
		m_itemSize = sizeof(LinkedArrayRegistry<T>);
		ui32 poolBytes = m_itemSize * m_poolSize;

		std::cout << "size = " << m_itemSize << std::endl;
		
		//request bytes from heap
		m_buffer = (byte*)Malloc(poolBytes);

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
		Free(m_buffer);

		//Reset to default
		m_buffer = nullptr;
		m_firstAvailableSlot = 0;
		m_poolSize = 256;
	}

	//Add and remove
	
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
	const LinkedArrayRegistry<T>* LinkedArrayPool<T>:: operator[](ui32 index) const
	{
		ui32 byteIndex = index * m_itemSize;
		return _readAsRegistry(byteIndex);
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
		//Check if current slot is available.
		LinkedArrayRegistry<T>* r = SELF[m_firstAvailableSlot];
		if (r->isEmpty) return r;

		//If not iterate until empty one is found.
		for (ui32 i = 0; i < m_poolSize; i++)
		{
			r = SELF[i];
#ifdef BS_ASSERT
			assert(r);
#endif
			if (r->isEmpty)
			{
				m_firstAvailableSlot = i;
				return r;
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


	//A LinkedArray is a doubly linked list of LinkedArrayPools.
	//It allows instant removal, relatively fast iteration and stable addresses.
}


#undef DEFINE_CONSTRUCT_FUNCTION(TYPES,ARGS,PARAMS)

#endif // !BS_LINKEDARRAY_H
