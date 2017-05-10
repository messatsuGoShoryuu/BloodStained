#ifndef BS_HASHMAP_H
#define BS_HASHMAP_H

#include "../Utilities/bs_types.h"
#include "../External/HashFunctions/MurmurHash/bs_MurmurHash.h"
#include "../Allocator/bs_Memory.h"

#include <assert.h>

#define HASHMAP_EMPTY			0x00	//0000
#define HASHMAP_KEEPLOOKING		0x02	//0010
#define HASHMAP_FULL			0x01	//0001
#define HASHMAP_EMPTY_INV		0x0E	//1110
#define HASHMAP_KEEPLOOKING_INV	0x0D	//1101


template <class T>
static ui32 getHash(T& key)
{
	ui32 hash = 0;
	int size = sizeof(T);
	MurmurHash3_x86_32(&key, size, 0, &hash);
	return hash;
}

template <class T>
static ui32 getHash(T*& key)
{
	ui32 hash = 0;
	int size = sizeof(T);
	MurmurHash3_x86_32(key, size, 0, &hash);
	return hash;
}

template<>
static ui32 getHash<const char*>(const char*& key)
{
	ui32 hash = 0;
	int size = strlen(key);
	MurmurHash3_x86_32(key, size, 0, &hash);
	return hash;
}

template<>
static ui32 getHash<char*>(char*& key)
{
	ui32 hash = 0;
	int size = strlen(key);
	MurmurHash3_x86_32(key, size, 0, &hash);
	return hash;
}

namespace bs
{
	class String;
}

ui32	getStringHash(const bs::String& key);
template <>
static ui32 getHash<bs::String>(bs::String& key)
{
	return getStringHash(key);
}

template <>
static ui32 getHash<const bs::String>(const bs::String& key)
{
	return getStringHash(key);
}

namespace bs
{

	template <class Key, class Value>
	struct KeyValuePair
	{
		Key key;
		Value value;
	};
	
	template <class Key, class Value> class HashMapIterator;

	template <class Key, class Value>
	class HashMap
	{
		friend class HashMapIterator<Key, Value>;
	public:
		//Default constructor
		HashMap();
		//Copy constructor
		HashMap(const HashMap& h);
		//Destructor
		~HashMap();

		//Allocate
		HashMap(ui32 bufferSize);

	public:
		//Accessors
		inline	const ui32 count()				{ return m_count; }
		inline	const ui32 count()		const	{ return m_count; }
		inline  const ui32 bufferSize()			{ return m_bufferSize; }
		inline  const ui32 bufferSize()	const	{ return m_bufferSize; }

	public:
		//Operators
		Value&			operator[](const Key& key);
		const Value&	operator[](const Key& key) const;

		inline	void	operator=(const HashMap& other){ _copy(other); }

	public:
		//Clear everything, but don't deallocate buffer.
		void	clear();

		//Clear everything and deallocate buffer.
		void	reset();

		/*Check if this key is used
		**@param key	Key to be checked
		*/
		bool	isEmptyAt(const Key& key);
		
		/*Remove this key and its value.
		**@param key Key to be removed.	
		*/
		void	remove(const Key& key);

	private:
		//Struct to stor pairs
		struct HashMapNode
		{
			KeyValuePair<Key, Value> pair;
			ui8 bitMask;
		};

		HashMapNode m_emptyNode;


	private:
		//For copy constructor and assignment operator.
		void	_copy(const HashMap& other);

		/*Reallocate space and redistribute data
		**@param newSize New buffer size.
		*/
		void	_resize(ui32 newSize);
		
		//Array geographic functions:

		/*Apply quadratic probing to the hashed index if necessary.
		**Returns corrected index.
		**@param key	Key to be found.
		**@param index	Index returned by hash function.
		**@param changeFlag	Do we change the flag?
		*/
		ui32	_findByQuadraticProbing(const Key& key, ui32 index, bool changeFlag);

		/*Find the index of the required key, don't modify the flag.
		**Returns final index
		**@param key	Key to be found
		*/
		ui32	_find(const Key& key);

		/*Find the index of the required key, modify the flag (This location is now marked as non empty).
		**Returns final index
		**@param key	Key to be found
		*/
		ui32	_place(const Key& key);
	private:
		//Members
		HashMapNode*	m_buffer;
		ui32			m_bufferSize;
		ui32			m_count;
	};

	template<class Key, class Value>
	HashMap<Key, Value>::HashMap()
		:m_buffer(nullptr),
		m_bufferSize(0),
		m_count(0)
	{

	}
	
	template<class Key, class Value>
	HashMap<Key, Value>::HashMap(const HashMap<Key, Value>& h)
		:m_buffer(nullptr),
		m_bufferSize(0),
		m_count(0)
	{
		_copy(h);
	}
	
	template<class Key, class Value>
	HashMap<Key, Value>::~HashMap()
	{
		reset();
	}

	template<class Key, class Value>
	HashMap<Key, Value>::HashMap(ui32 bufferSize)
		:m_buffer(nullptr),
		m_bufferSize(0),
		m_count(0)
	{
		_resize(bufferSize);
	}

	//Operators
	template<class Key, class Value>
	Value&			HashMap<Key, Value>::operator[](const Key& key)
	{
		//Resize if not yet initialized
		if (m_buffer == nullptr || m_bufferSize < 8) _resize(8);

		//Place our key
		ui32	index = _place(key);

		//If placement has failed, return a default object.
		if (index == BS_INVALID_INDEX) return m_emptyNode.pair.value;

		//Check if this key exists in the registry.
		HashMapNode* n = &m_buffer[index];
		KeyValuePair<Key, Value>* k = &n->pair;
		bool isEmpty = (n->bitMask | HASHMAP_EMPTY_INV) == HASHMAP_EMPTY_INV;

		if (isEmpty)
		{
			//If the key doesn't exist in the registry, check if we have to resize.
			f32 loadFactor = (float)(m_count + 1) / (float)m_bufferSize;
			if (loadFactor > 0.75f)
			{
				//If the load factor is above the threshold, resize by buffersize * 2
				_resize(math::nearestPowerOfTwo(m_bufferSize * 2));
				index = _place(key);
				n = &m_buffer[index];
			}

			//Set the bitmask to full, and create the new Key object
			n->bitMask |= HASHMAP_FULL;
			k = &n->pair;
			Place(&(k->key), Key, key);
			m_count++;
#ifdef BS_PROFILE_MEMORY
			bs::Profiler::addUsedBytes(sizeof(Value));
#endif
		}

		return k->value;
	}

	template<class Key, class Value>
	const Value&	HashMap<Key, Value>::operator[](const Key& key) const
	{
		if (m_buffer == nullptr || m_bufferSize < 8) return Value();

		ui32 index = _find(Key);
		KeyValuePair<Key,Value>* k = m_buffer[index].pair;
		return k->value;
	}

	template<class Key, class Value>
	void	HashMap<Key, Value>::clear()
	{
		if (m_buffer && m_bufferSize > 0)
		{
			//Iterate throught the buffer
			for (ui32 i = 0; i < m_bufferSize; i++)
			{
				ui8 flags = m_buffer[i].bitMask;
				KeyValuePair<Key, Value>* k = &m_buffer[i].pair;

				//If the bytes are 0000 0001 destroy the key and the value
				if (flags & HASHMAP_FULL)
				{
					Destroy((&k->key), Key);
					Destroy((&k->value), Value);
				}

				//Set the bitmask to empty.
				m_buffer[i].bitMask = HASHMAP_EMPTY;
			}
		}
		m_count = 0;
	}

	template<class Key, class Value>
	void	HashMap<Key, Value>::reset()
	{
		clear();
		if (m_buffer)
			BS_Free(m_buffer);
		m_buffer = nullptr;
		m_bufferSize = 0;
	}

	template<class Key, class Value>
	bool	HashMap<Key, Value>::isEmptyAt(const Key& key)
	{
		//No buffer, no key
		if (!m_buffer) return true;
		
		//Find key without altering bitmasks
		ui32 index = _find(key);

		//No index no key
		if (index == BS_INVALID_INDEX) return true;

		//If flags are 0000 00x0 it is empty.
		ui8 flags = m_buffer[index].bitMask;
		return (flags | HASHMAP_EMPTY_INV) == HASHMAP_EMPTY_INV;
	}

	template<class Key, class Value>
	void	HashMap<Key, Value>::remove(const Key& key)
	{
		//No buffer, no remove.
		if (!m_buffer) return;

		//Find key without altering bitmasks.
		ui32 index = _find(key);

		//No index no remove.
		if (index == BS_INVALID_INDEX) return;

		//Nothing to remove if this is empty.
		ui8 flags = m_buffer[index].bitMask;
		if ((flags | HASHMAP_EMPTY_INV) == HASHMAP_EMPTY_INV) return;

		KeyValuePair<Key, Value>* k;
		k = &m_buffer[index].pair;

		//Destroy key and value.
		Destroy((&k->key), Key);
		Destroy((&k->value), Value);

		//Set bitmask to empty.
		flags &= HASHMAP_EMPTY_INV;
		m_buffer[index].bitMask = flags;

		m_count--;
	}


	template<class Key, class Value>
	void	HashMap<Key, Value>::_copy(const HashMap& other)
	{
		//If source has no buffer, nothing to copy.
		if (!other.m_buffer || other.m_bufferSize == 0) return;
		
		ui32 bufferSize = other.m_bufferSize;

		//If we have something in our buffer, clear it.
		if (m_buffer)
		{
			//If two buffers are of different size, reallocate.
			if (m_bufferSize != bufferSize)
			{
				reset();
				m_buffer = (HashMapNode*)BS_Malloc(sizeof(HashMapNode) * bufferSize);
			}
			//Else no need to reallocate.
			else clear();
		}

		//Iterate the buffer, copy anything that's full.
		for (ui32 i = 0; i < bufferSize; i++)
		{
			ui8 flags = other.m_buffer[i].bitMask;
			if (flags == HASHMAP_FULL)
			{
				KeyValuePair<Key, Value>* k = &m_buffer[i].pair;
				KeyValuePair<Key, Value>* o = &other.m_buffer[i].pair;
				Place(&(k->key), Key, o->key);
				Place(&(k->value), Value, o->value);
			}
			//Copy the bitmask.
			m_buffer[i].bitMask = flags;
		}

		m_bufferSize = other.m_bufferSize;
		m_count = other.m_count;
	}


	template<class Key, class Value>
	void	HashMap<Key, Value>::_resize(ui32 newSize)
	{
		//Nothing to resize
		if (m_buffer && newSize == m_bufferSize) return;

		HashMapNode* oldBuffer = m_buffer;

		//Store old buffer in local variable and allocate new buffer.
		ui32 oldBufferSize = m_bufferSize;
		m_bufferSize = newSize;
		ui32 sizeAsBytes = sizeof(HashMapNode) * newSize;
		m_buffer = (HashMapNode*)BS_Malloc(sizeAsBytes);
		memset(m_buffer, 0, sizeAsBytes);
		
	
		//Iterate old buffer array.
		for (ui32 i = 0; i < oldBufferSize; i++)
		{
			//Store in local variables
			ui8 flags = oldBuffer[i].bitMask;
			KeyValuePair<Key, Value>* k = &oldBuffer[i].pair;

			//If this keyvalue pair has valid data
			if ((flags & HASHMAP_FULL) == HASHMAP_FULL)
			{
				//Find appropriate index in new buffer.
				ui32 index = _place(k->key);

#ifdef BS_ASSERT
				assert(index != BS_INVALID_INDEX);
#endif

				//Construct old indexes in new buffer.
				Place(&(m_buffer[index].pair.key), Key, k->key);
				Place(&(m_buffer[index].pair.value), Value, k->value);

				//Destroy old values.
				Destroy((&k->key), Key);
				Destroy((&k->value), Value);

				//Set flags
				m_buffer[index].bitMask |= HASHMAP_FULL;
			}
		}

		//Free the old buffer.
		if (oldBuffer)
			BS_Free(oldBuffer);
	}

	template<class Key, class Value>
	ui32	HashMap<Key, Value>::_findByQuadraticProbing(const Key& key, ui32 index, bool changeFlag)
	{
		ui32 collisions = 0;

		//Bounds check.
		if (index >= m_bufferSize) return BS_INVALID_INDEX;
		ui32 firstIndex = index;

#ifdef BS_ASSERT
		assert(m_buffer);
#endif
		
		//While keys are not equal
		while (m_buffer[index].pair.key != key)
		{
			ui8 flags = m_buffer[index].bitMask;

			//There is nothing corresponding to this index.
			if ((flags & HASHMAP_KEEPLOOKING) != HASHMAP_KEEPLOOKING)
			{
				if (changeFlag)
				{
					//Update flags
					flags |= HASHMAP_KEEPLOOKING;
					m_buffer[index].bitMask = flags;
				}

				//Return newly found index.
				return index;
			}

			//If nothing has returned we have a collision.
			collisions++;
			index = (index + collisions * collisions) % m_bufferSize;
			if (index == firstIndex) break;
		}

		if (changeFlag) m_buffer[index].bitMask |= HASHMAP_KEEPLOOKING;
		return index;
	}

	template<class Key, class Value>
	ui32	HashMap<Key, Value>::_find(const Key& key)
	{
		ui32 hash = 0;
		hash = getHash(key);
		hash = hash % m_bufferSize;
		return _findByQuadraticProbing(key, hash, false);
	}

	template<class Key, class Value>
	ui32	HashMap<Key, Value>::_place(const Key& key)
	{
		ui32 hash = 0;
		hash = getHash(key);
		hash = hash % m_bufferSize;
		return _findByQuadraticProbing(key, hash, true);
	}


	template <class Key, class Value> 
	class HashMapIterator
	{
	public:
		HashMapIterator()
			:m_index(0),
			m_hashmap(nullptr)
		{

		}

		HashMapIterator(const HashMap<Key, Value>* hashmap)
			:m_hashmap(hashmap),
			m_index(0)
		{

		}

		HashMapIterator(const HashMapIterator& h)
		{

		}

		~HashMapIterator()
		{

		}

		Value*	begin()
		{ 
			m_index = 0;
			if ((m_hashmap->m_buffer[m_index].bitMask & HASHMAP_FULL) != HASHMAP_FULL)
				return &m_hashmap->m_buffer[0];
			return SELF++;
		}

		bool	end()
		{
			return m_index < m_hashmap->m_bufferSize;
		}

		Value*	operator++()
		{	
			while ((m_hashmap->m_buffer[m_index].bitMask & HASHMAP_FULL) != HASHMAP_FULL)
			{
				m_index++;
				if (m_index > m_hashmap->m_bufferSize) return nullptr;
			}
			return &m_hashmap->m_buffer[m_index];
		}

		Value*	operator--()
		{
			while ((m_hashmap->m_buffer[m_index].bitMask & HASHMAP_FULL) != HASHMAP_FULL)
			{
				m_index--;
				if (m_index == 0) return nullptr;
			}
			return &m_hashmap->m_buffer[m_index];
		}

	private:
		HashMap<Key, Value>*	m_hashmap;
		ui32	m_index;
	};

}

#undef HASHMAP_EMPTY
#undef HASHMAP_KEEPLOOKING
#undef HASHMAP_FULL

#endif // !BS_HASHMAP_H
