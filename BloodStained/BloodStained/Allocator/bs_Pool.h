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
		Pool(ui16 poolSize, ui16 itemSize, ui8 alignment);

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
		ui16 itemSize(){ return m_itemSize; }
		ui16 poolSize(){ return m_poolSize; }
		ui16 alignment(){ return m_alignment; }
		ui16 itemCount(){ return m_itemCount; }
		Pool*	next(){ return m_next; }

		bool isEmpty(){ return m_itemCount == 0; }
		bool isFull(){ return m_itemCount >= m_poolSize; }

		//setters
		void setNext(Pool* p){ m_next = p; }

	private:
		//helpers

		//Calculates the item size with the alignment.
		void _calculateItemSize();

		//Read ui16 from byte array.
		//@index: index to read from the buffer
		ui16 _readUi16FromBuffer(ui32 index);

		/*Put ui16 to byte array.
		**@value: value to store
		**@index: index in buffer
		*/
		void _putUi16ToBuffer(ui16 value, ui32 index);

	private:
		ui16 m_nextAvailableBlock;
		ui16 m_itemCount;
		ui16 m_itemSize;
		ui16 m_poolSize;
		ui16 m_poolByteCount;
		byte*	m_buffer;
		ui8		m_alignment;

		//linked list
		Pool* m_next;
	};
}

#endif // !BS_POOL_H
