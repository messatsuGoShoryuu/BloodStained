#ifndef BS_POOLALLOCATOR_H
#define BS_POOLALLOCATOR_H

#include <assert.h>

#include "bs_Pool.h"

#include "../Profiler/bs_Profiler.h"

namespace bs
{
	//a class for allocating equal chunks of bytes in a linked list of 
	//equal sized arrays.

	template<class T>
	class PoolAllocator
	{
	public:
		//Default constructor and destructor.
		PoolAllocator();
		~PoolAllocator();

		//Copy constructor.
		PoolAllocator(const PoolAllocator& p);

		//@poolSize : how many items in the pool?
		PoolAllocator(ui32 poolSize);

		//Manual init and shutdown for more control.
		bool initialize();
		bool shutDown();
		
	public:
		//allocate function up to 6 parameters
		template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
		T*	allocate(Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
		{
			Pool* p = _findFirstAvailablePool();
#ifdef BS_ASSERT
			assert(p);
#endif
#ifdef BS_PROFILE_MEMORY
			Profiler::addUsedBytes(sizeof(T));
#endif
			return new(p->allocate()) T(arg0, arg1, arg2, arg3, arg4, arg5);
		}

		template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
		T*	allocate(Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
		{
			Pool* p = _findFirstAvailablePool();
#ifdef BS_ASSERT
			assert(p);
#endif
#ifdef BS_PROFILE_MEMORY
			Profiler::addUsedBytes(sizeof(T));
#endif
			return new(p->allocate()) T(arg0, arg1, arg2, arg3, arg4);
		}

		template<typename Arg0, typename Arg1, typename Arg2, typename Arg3>
		T*	allocate(Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3)
		{
			Pool* p = _findFirstAvailablePool();
#ifdef BS_ASSERT
			assert(p);
#endif
#ifdef BS_PROFILE_MEMORY
			Profiler::addUsedBytes(sizeof(T));
#endif
			return new(p->allocate()) T(arg0, arg1, arg2, arg3);
		}

		template<typename Arg0, typename Arg1, typename Arg2>
		T*	allocate(Arg0 arg0, Arg1 arg1, Arg2 arg2)
		{
			Pool* p = _findFirstAvailablePool();
#ifdef BS_ASSERT
			assert(p);
#endif
#ifdef BS_PROFILE_MEMORY
			Profiler::addUsedBytes(sizeof(T));
#endif
			return new(p->allocate()) T(arg0, arg1, arg2);
		}

		template<typename Arg0, typename Arg1>
		T*	allocate(Arg0 arg0, Arg1 arg1)
		{
			Pool* p = _findFirstAvailablePool();
#ifdef BS_ASSERT
			assert(p);
#endif
#ifdef BS_PROFILE_MEMORY
			Profiler::addUsedBytes(sizeof(T));
#endif
			return new(p->allocate()) T(arg0, arg1);
		}

		template<typename Arg0>
		T*	allocate(Arg0 arg0)
		{
			Pool* p = _findFirstAvailablePool();
#ifdef BS_ASSERT
			assert(p);
#endif
#ifdef BS_PROFILE_MEMORY
			Profiler::addUsedBytes(sizeof(T));
#endif
			return new(p->allocate()) T(arg0);
		}

		T*	allocate()
		{
			Pool* p = _findFirstAvailablePool();
#ifdef BS_ASSERT
			assert(p);
#endif
#ifdef BS_PROFILE_MEMORY
			Profiler::addUsedBytes(sizeof(T));
#endif
			return new(p->allocate()) T();
		}

		T* allocate(const T& object)
		{
			Pool* p = _findFirstAvailablePool();
#ifdef BS_ASSERT
			assert(p);
#endif
#ifdef BS_PROFILE_MEMORY
			Profiler::addUsedBytes(sizeof(T));
#endif
			return new (p->allocate()) T(object);
		}

		void	deallocate(T* item);

	public:
		//accessors
		ui32 poolSize(){ return m_poolSize; }

	private:
		//linked list navigation:

		//Adds new pool to the linked list.
		Pool*	_addPool();

		//Removes pool marked by m_poolIterator from linked list.
		void	_removePool();

		//Returns the first non empty pool (used for allocation)
		Pool*	_findFirstAvailablePool();

		//Returns the pool containing the item.
		//@item : item to find
		Pool*	_findContainingPool(T* item);

	private:
		//class members
		
		//Linked list of pools
		Pool*	m_poolList;
		//Iterator to navigate in the linked list
		Pool*	m_poolIterator;
		Pool*	m_lastPool;
		//Item count per pool.
		ui32 m_poolSize;
	};


	//Default constructor and destructor.
	template <class T>
	PoolAllocator<T>::PoolAllocator()
		:m_poolList(nullptr),
		m_poolIterator(nullptr),
		m_lastPool(nullptr),
		m_poolSize(256)
	{

	}

	template <class T>
	PoolAllocator<T>::~PoolAllocator()
	{

	}

	//Copy constructor.
	template <class T>
	PoolAllocator<T>::PoolAllocator(const PoolAllocator& p)
		:m_poolList(p.m_poolList),
		m_poolIterator(p.m_poolIterator),
		m_lastPool(p.m_lastPool),
		m_poolSize(p.m_poolSize)
	{

	}

	//@poolSize : how many items in the pool?
	template <class T>
	PoolAllocator<T>::PoolAllocator(ui32 poolSize)
		:m_poolList(nullptr),
		m_poolIterator(nullptr),
		m_lastPool(nullptr),
		m_poolSize(poolSize)
	{

	}

	//Manual init and shutdown for more control.
	template <class T>
	bool PoolAllocator<T>::initialize()
	{
		if(!_findFirstAvailablePool()) return false;
		return true;
	}
		
	template <class T>
	bool PoolAllocator<T>::shutDown()
	{
		m_poolIterator = m_poolList;
		while (m_poolIterator)
		{
			Pool* temp = m_poolIterator;
			m_poolIterator = temp->next();
			temp->shutDown();
			delete temp;
		}
		return true;
	}
	
	//Deallocate given T object.
	template <class T>
	void PoolAllocator<T>::deallocate(T* item)
	{
		Pool* p = _findContainingPool(item);
		if (p)
		{
			m_poolIterator = p;
			p->deallocate(item);
		}

#ifdef BS_PROFILE_MEMORY
		Profiler::removeUsedBytes(sizeof(T));
#endif
	}

	//Returns the first non empty pool (used for allocation)
	template<class T>
	Pool* PoolAllocator<T>::_findFirstAvailablePool()
	{
		//if the list is empty add and return new pool.
		if (!m_poolList)
		{
			m_poolIterator = _addPool();
			return m_poolIterator;
		}

		//if pool iterator is null set it to the begininng
		if (!m_poolIterator) m_poolIterator = m_poolList;

#ifdef BS_ASSERT
		assert(m_poolIterator);
#endif
		
		//if the iterator is available return it
		if (!m_poolIterator->isFull()) return m_poolIterator;

		//else iterate through linked list
		while (m_poolIterator->isFull())
		{
			m_poolIterator = m_poolIterator->next();
			//break if we hit the end of the list
			if (!m_poolIterator) break;
		}
		
		//if we found an available pool return it.
		if (m_poolIterator) return m_poolIterator;

		//else return new pool.
		m_poolIterator = _addPool();

#ifdef BS_ASSERT
		assert(m_poolIterator);
#endif
		return m_poolIterator;
	}

	//Adds new pool to the linked list.
	template<class T>
	Pool*	PoolAllocator<T>::_addPool()
	{
		
		if (!m_poolList)
		{
			//if pool list is empty create new pool
			m_poolList = new Pool(m_poolSize, sizeof(T), __alignof(T));

			//if initialization failed return null
			if (!m_poolList->initialize())
			{
				std::cout << "Pool List initialization failed!" << std::endl;
				return nullptr;
			}

			//set the last pool
			m_lastPool = m_poolList;
		}
		else
		{
#ifdef BS_ASSERT
			assert(m_lastPool);
#endif

			//create new pool at the end
			Pool* ptr = new Pool(m_poolSize, sizeof(T), __alignof(T));
			m_lastPool->setNext(ptr);

			//if initialization failed return null
			if (!ptr->initialize())
			{
				std::cout << "Pool List initialization failed!" << std::endl;
				return nullptr;
			}

			//set the last pool
			m_lastPool = ptr;
		}

		return m_lastPool;
	}

	//Returns the pool containing the item.
	template<class T>
	Pool*	PoolAllocator<T>::_findContainingPool(T* item)
	{
		//if current iterator contains this item early out
		if (m_poolIterator->contains(item)) return m_poolIterator;

		//if linked list is empty return null
		if (!m_poolList) return nullptr;

		//iterate while pool is not null and does not containt item
		Pool* p = m_poolList;
		while (p && !p->contains(item))
		{
			p = p->next();
		}

		//if found return pool else return null
		if (p) return p;
		return nullptr;
	}

}

#endif