#ifndef BS_ARRAY_H
#define BS_ARRAY_H

#include "../Utilities/bs_arrayOperations.h"
#include "../Utilities/bs_math.h"
#include "../Allocator/bs_Memory.h"




#define DEFINE_CONSTRUCT_FUNCTION(TYPES,ARGS,PARAMS)	template<TYPES> \
														ui32 construct(ARGS)\
														{\
															ui32 index = m_count;\
															if (m_count + 1 >= m_bufferSize) reserve(m_bufferSize * 2); \
															T* p = &m_buffer[index];\
															Place((p), T, PARAMS);\
															m_count++; \
															return index;\
														}

namespace bs
{

	//Dynamic array class (simple std::vector)
	template <class T>
	class Array
	{
	public:
		//Default constructor and destructor.
		Array();
		~Array();

		//Copy constructor.
		Array(const Array& a);

		//Parameter constructors:

		//@size: preallocation size
		Array(const ui32 size);

	public:

		//Add existing item.
		ui32 add(const T& item);
		
		//Construct directly in the array
		ui32 construct()
		{
			ui32 index = m_count;
			if (m_count + 1 >= m_bufferSize) reserve(m_bufferSize * 2);
			m_count++;
			T* p = &m_buffer[index];
			Place(p, T,); 
			return index;
		}

		//Define multiple argument versions, up to 6 arguments.
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_1, MULTIPLE_ARGS_1, MULTIPLE_PARAMS_1)
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_2, MULTIPLE_ARGS_2, MULTIPLE_PARAMS_2)
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_3, MULTIPLE_ARGS_3, MULTIPLE_PARAMS_3)
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_4, MULTIPLE_ARGS_4, MULTIPLE_PARAMS_4)
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_5, MULTIPLE_ARGS_5, MULTIPLE_PARAMS_5)
		DEFINE_CONSTRUCT_FUNCTION(MULTIPLE_TYPES_6, MULTIPLE_ARGS_6, MULTIPLE_PARAMS_6)

		/*Swap two items
		**@index1: first item
		**@index2: second item
		*/
		void swap(ui32 index1, ui32 index2);

		//Pre-allocate bytes
		//@size: preallocation size
		void reserve(ui32 size);

		//Remove 1 item from the end
		void pop();

		//Remove first item and return its index.
		//@item: item to remove
		ui32 remove(const T& item);

		//Remove all items, return false if no item is found.
		//@item: item to remove
		bool removeAll(const T& item);

		//Swap the item with the last item and pop (fast removal, but will change item order)
		//@item: item to remove
		bool swapAndRemove(const T& item);
		//@index: index of the item to remove
		bool swapAndRemove(ui32 index);

		//Set size to 0.
		void clear();

		//Reset to default.
		void reset();

	private:
		//Allocate and clone data.
		T* _allocate(ui32 size);

		//Call destructors of all members
		void _destroyMembers();

		//Clone Array 
		void _copy(const Array& a);

		//Find index of a certain item.
		//@item: item to be found
		ui32 _findIndex(const T& item);

		/*Find index of a certain item with offset.
		**@item: item to be found
		**@offset: start search from this index
		*/
		ui32 _findIndex(const T& item, ui32 offset);

	public:
		//Accessors
		const ui32	count()					{ return m_count; }
		const ui32	count()			const	{ return m_count; }
		const ui32	bufferSize()			{ return m_bufferSize; }
		const ui32	bufferSize()	const 	{ return m_bufferSize; }
		T&			first()					{ return m_buffer[0]; }
		const T&	first()			const	{ return m_buffer[0]; }
		T&			last()					{ return m_buffer[m_count - 1]; }
		const T&	last()			const	{ return m_buffer[m_count - 1]; }

	public:
		//operators

		//random access
		T&			operator[](ui32 index)			{ return m_buffer[index]; }
		const T&	operator[](ui32 index)	const	{ return m_buffer[index]; }

		//assignment
		void		operator=(const Array& a);


	private:
		T*		m_buffer;
		ui32	m_count;
		ui32	m_bufferSize;
	};


	template <class T>
	Array<T>::Array()
		:m_buffer(nullptr),
		m_count(0),
		m_bufferSize(0)
	{

	}

	template <class T>
	Array<T>::~Array()
	{
		if (m_bufferSize > 0) reset();
	}

	template<class T>
	Array<T>::Array(const Array& a)
		:m_buffer(nullptr),
		m_count(a.m_count),
		m_bufferSize(a.m_bufferSize)
	{
		_copy(a);
	}

	template<class T>
	Array<T>::Array(ui32 size)
		:m_buffer(nullptr),
		m_count(0),
		m_bufferSize(0)
	{
		reserve(size);
	}

	template<class T>
	ui32 Array<T>::add(const T& item)
	{
		ui32 index = m_count;
		if (m_count + 1 >= m_bufferSize) reserve(m_bufferSize * 2);
		Place((m_buffer + index), T, item);
		m_count++;
		return index;
	}

	template <class T>
	void Array<T>::swap(ui32 index1, ui32 index2)
	{
		T temp;
		new(&temp) T(m_buffer[index1]);

		m_buffer[index1].~T();
		new(m_buffer + index1) T(m_buffer[index2]);

		m_buffer[index2].~T();
		new(m_buffer + index2) T(temp);
	}

	template <class T>
	void Array<T>::reserve(ui32 size)
	{
		//if the requested size if smaller then we already have, return
		if (m_bufferSize != 0 && size <= m_bufferSize) return;

		//set size to the nearest power of 2
		ui32 size2k = nearestPowerOfTwo(size);
		if (size2k < BS_MINIMUM_ARRAY_ALLOC) size2k = BS_MINIMUM_ARRAY_ALLOC;

		//allocate and migrate
		T* tempBuffer = _allocate(size2k);
		for (ui32 i = 0; i < m_count; i++) m_buffer[i].~T();
		

		//update members
		m_bufferSize = size2k;
		if(m_buffer) Free(m_buffer);
		m_buffer = tempBuffer;
	}

	template <class T>
	void Array<T>::pop()
	{
		//if there is nothing to pop return
		if (m_count == 0) return;

		//else destroy the last item
		m_count--;
		T* p = &m_buffer[m_count];
		Destroy(p, T);
	}

	template <class T>
	ui32 Array<T>::remove(const T& item)
	{
		//if count == 0 there is no item to be found
		if (m_count == 0) return BS_INVALID_INDEX;

		ui32 index = _findIndex(item);

		//if no index is found return 
		if (index == BS_INVALID_INDEX) return index;

		
		//if item is found overwrite all items onwards with the next item
		for (ui32 i = index; i < m_count; i++)
		{
			T* p = &m_buffer[i];
			Destroy(p, T);
			Place(p, T, m_buffer[i]);
		}

		//destroy the last item
		pop();
		return item;
		
	}

	template <class T>
	bool Array<T>::removeAll(const T& item)
	{
		//if count == 0 there is no item to be found
		if (m_count == 0) return false;


		ui32 index = 0;

		while (true)
		{
			index = _findIndex(item, index);

			//if no index is found return 
			if (index == BS_INVALID_INDEX) return false;


			//if item is found overwrite all items onwards with the next item
			for (ui32 i = index; i < m_count; i++)
			{
				T* p = &m_buffer[i];
				Destroy(p, T);
				Place(m_buffer + i, T, m_buffer[i]);
			}

			//destroy the last item
			pop();
		}
		return true;
	}


	template<class T>
	bool Array<T>::swapAndRemove(const T& item)
	{
		ui32 index = _findIndex(item);
		if (index == BS_INVALID_INDEX) return false;

		return swapAndRemove(index);
	}

	template<class T>
	bool Array<T>::swapAndRemove(ui32 index)
	{
		//check if index is valid
		if (index >= m_count) return false;

		//destroy item to remove
		m_buffer[index].~T();

		//overwrite with last item
		T* p = &m_buffer[index];
		new(p) T(last());

		//destroy last item
		pop();
		return true;
	}


	template <class T>
	void Array<T>::clear()
	{
		//destroy all members, but leave the buffer allocation as it is.
		_destroyMembers();
		m_count = 0;
	}

	template <class T>
	void Array<T>::reset()
	{
		//hard reset everything.
		clear();
		Free(m_buffer);
		m_buffer = nullptr;
		m_bufferSize = 0;
	}

	template <class T>
	T* Array<T>::_allocate(ui32 size)
	{
		//allocate new buffer
		T* ptr = (T*)Malloc(size * sizeof(T));

		//copy content from old buffer to new
		copyArray(m_buffer, ptr, m_count);

		//return new buffer
		return ptr;
	}

	template <class T>
	void Array<T>::_destroyMembers()
	{
		if (m_count == 0) return;
		for (ui32 i = 0; i < m_count; i++)
		{
			T* p = &m_buffer[i];
			Destroy(p, T);
		}
	}

	template <class T>
	void Array<T>::_copy(const Array<T>& a)
	{
		//reallocate this buffer
		m_buffer = (T*)Malloc(a.m_bufferSize * sizeof(T));

		//copy content from a's buffer to this buffer
		copyArray(a.m_buffer, m_buffer, a.m_count);

#ifdef BS_PROFILE_MEMORY
		Profiler::addUsedBytes(sizeof(T) * a.m_count);
#endif

		//update member values
		m_count = a.m_count;
		m_bufferSize = a.m_bufferSize;
	}

	template <class T>
	ui32 Array<T>::_findIndex(const T& item)
	{
		for (ui32 i = 0; i < m_count; i++)
		{
			if (m_buffer[i] == item) return i;
		}
		return BS_INVALID_INDEX;
	}

	template <class T>
	ui32 Array<T>::_findIndex(const T& item, ui32 offset)
	{
		for (ui32 i = offset; i < m_count; i++)
		{
			if (m_buffer[i] == item) return i;
		}
		return BS_INVALID_INDEX;
	}

	template <class T>
	void Array<T>::operator=(const Array<T>& a)
	{
		//don't cause memory leaks
		if (m_bufferSize > 0) reset();

		_copy(a);
	}
}





#undef DEFINE_CONSTRUCT_FUNCTION(TYPES,ARGS,PARAMS)

#endif // !BS_ARRAY_H
