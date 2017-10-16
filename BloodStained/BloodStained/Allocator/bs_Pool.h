#ifndef _BS_POOL_H_
#define _BS_POOL_H_

#include "../Utilities/bs_types.h"


namespace bs
{
	//a pool of data
	class Pool
	{

	public:
		//default constructor and destructor
		Pool();
		~Pool();

		/*	Constructor with parameters:
		*	@poolSize: how many items does this pool contain
		*	@itemSize: what is the size of an item in bytes
		*	@what is the alignment in bytes
		*/
		Pool(ptrsize poolSize, ptrsize itemSize, ui8 alignment);

		//copy constructor
		Pool(const Pool& p);


	public:
		//Manual init and shut down.
		bool initialize();
		bool shutDown();


		//Get an aligned pointer of itemSize bytes.
		void* allocate();
		//Return the pointer to the pool
		void deallocate(void* item);
		//Does this pool containt this item?
		bool contains(void* item){ return item >= m_buffer && item < m_buffer + m_poolByteCount; }


	public:
		//accessors
		ptrsize itemSize(){ return m_itemSize; }
		ptrsize poolSize(){ return m_poolSize; }
		ptrsize alignment(){ return m_alignment; }
		ptrsize itemCount(){ return m_itemCount; }
		Pool*	next(){ return m_next; }

		bool isEmpty(){ return m_itemCount == 0; }
		bool isFull(){ return m_itemCount >= m_poolSize; }

		//setters
		void setNext(Pool* p){ m_next = p; }

	private:
		//helpers

		//Calculates the item size with the alignment.
		void _calculateItemSize();

		void _putPtrSizeToBuffer(ptrsize value, ptrsize index);
		ptrsize _readPtrSizeFromBuffer(ptrsize index);

	private:
		
		ptrsize m_itemCount;
		ptrsize m_itemSize;
		ptrsize m_poolSize;
		ptrsize m_poolByteCount;
		ptrsize m_nextAvailableBlock;
		byte*	m_buffer;
		ui8		m_alignment;

		//linked list
		Pool* m_next;
	};
}

#endif // !BS_POOL_H
