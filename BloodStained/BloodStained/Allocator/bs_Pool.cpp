#include "bs_Pool.h"
#include "../Utilities/bs_arrayOperations.h"
#include "../Math/bs_math.h"

#include <assert.h>

namespace bs
{
	//default constructor
	Pool::Pool()
		:m_buffer(nullptr),
		m_alignment(4),
		m_itemCount(0),
		m_next(nullptr),
		m_nextAvailableBlock(0),
		m_itemSize(4),
		m_poolSize(256),
		m_poolByteCount(1024)
	{
		
	}

	/*	Constructor with parameters:
	*	@poolSize: how many items does this pool contain
	*	@itemSize: what is the size of an item in bytes
	*	@what is the alignment in bytes
	*/
	Pool::Pool(ui16 poolSize, ui16 itemSize, ui8 alignment)
		:m_buffer(nullptr),
		m_alignment(alignment),
		m_itemCount(0),
		m_next(nullptr),
		m_nextAvailableBlock(0),
		m_itemSize(itemSize),
		m_poolSize(poolSize)
	{
		//if size of item is 1 bytes, poolsize cant be bigger than 256
		if (m_itemSize == 1 && m_poolSize > 256) m_poolSize = 256;

		//calculate pool byte count
		m_poolByteCount = m_itemSize * m_poolSize;
	}

	Pool::Pool(const Pool& p)
		:m_buffer(nullptr),
		m_alignment(p.m_alignment),
		m_itemCount(p.m_itemCount),
		m_next(nullptr),
		m_nextAvailableBlock(p.m_nextAvailableBlock),
		m_itemSize(p.m_itemSize),
		m_poolSize(p.m_poolSize),
		m_poolByteCount(p.m_poolByteCount)
	{
		m_buffer = (byte*)malloc(m_poolByteCount);

		copyArray(p.m_buffer, m_buffer, m_poolByteCount);
	}

	//destructor (do nothing, everything should be controlled manually)
	Pool::~Pool()
	{
		
	}


	//manual initialization
	bool Pool::initialize()
	{

		//calculate aligned item size
		_calculateItemSize();

		//free buffer array if it is allocated
		if (m_buffer)
		{
			clearArray(m_buffer, m_poolByteCount);
			free(m_buffer);
		}

		m_buffer = (byte*)malloc(m_poolByteCount);

		if (!m_buffer) return false;

		//set next block values
		memset(m_buffer, 0, m_poolByteCount);
		for (ui32 i = 0; i < m_poolByteCount; i += m_itemSize)
		{
			_putUi16ToBuffer(i+m_itemSize,i);
		}

		return true;
	}

	//manual shut down
	bool Pool::shutDown()
	{
		//free buffer array if it is allocated
		if (m_buffer)
		{
			clearArray(m_buffer, m_poolByteCount);
			free(m_buffer);

			m_buffer = nullptr;
		}

		//set members to default values
		m_alignment = 4;
		m_itemSize = 4;
		m_itemCount = 0;
		m_poolSize = 256;
		m_poolByteCount = 1024;

		return true;
	}


	//Get an aligned pointer of itemSize bytes.
	void*	Pool::allocate()
	{

		//if this pool is full, return NULL
		if (m_itemCount >= m_poolSize) return nullptr;

		//store address of next available block
		ui16 next = _readUi16FromBuffer(m_nextAvailableBlock);

		//store empty pointer to return
		byte* result = m_buffer + m_nextAvailableBlock;
		memset(result, 0, m_itemSize);
		
#ifdef BS_ASSERT
		assert(result >= m_buffer);	
		assert(result < m_buffer + m_poolByteCount);		
#endif

		//keep track of data
		if (next < m_poolByteCount)
			m_nextAvailableBlock = next;
		m_itemCount++;

		return (void*)result;
	}

	//Return the pointer to the pool
	void Pool::deallocate(void* item)
	{

#ifdef BS_ASSERT
		assert(item >= m_buffer);
		assert(item < m_buffer + m_poolByteCount);
#endif
 
		//calculate item index
		ui16 itemIndex = (ui16)((byte*)item - m_buffer);

		memset(item, 0, m_itemSize);
		
		//if buffer is full make the only available block this item
		if (isFull())
		{
			m_nextAvailableBlock = itemIndex;
			_putUi16ToBuffer(m_nextAvailableBlock, itemIndex);
		}
		else
		{
			//else make current available block the next one, 
			//set the locator to the last freed one
			_putUi16ToBuffer(m_nextAvailableBlock,itemIndex);
			m_nextAvailableBlock = itemIndex;
		}
		
		m_itemCount--;
	}

	
	//helpers:

	//calculates the item size with the alignment
	void Pool::_calculateItemSize()
	{
		m_itemSize = math::nearest2PowMultipleOf(m_itemSize, m_alignment);
	}

	//Read ui16 from byte array.
	//@index: index to read from the buffer
	ui16 Pool::_readUi16FromBuffer(ui32 index)
	{
		if (m_itemSize == 1) return static_cast<ui16>(m_buffer[index]);
		return *(reinterpret_cast<ui16*>(m_buffer + index));
	}

	/*Put ui16 to byte array.
	**@value: value to store
	**@index: index in buffer
	*/
	void Pool::_putUi16ToBuffer(ui16 value, ui32 index)
	{
		if (m_itemSize == 1) m_buffer[index] = static_cast<byte>(value);
		else math::storeUi16ToByteArray(m_buffer + index, value);
	}
}