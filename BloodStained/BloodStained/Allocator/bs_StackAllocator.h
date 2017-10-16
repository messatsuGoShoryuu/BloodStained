#ifndef _BS_STACKALLOCATOR_H_
#define _BS_STACKALLOCATOR_H_

#include "../Utilities/bs_types.h"

namespace bs
{
	class StackAllocator
	{
	public:
		//Default constructor / destructor.
		StackAllocator();
		~StackAllocator();

		//Copy constcrutor.
		StackAllocator(const StackAllocator& s);

		//@param stackSize size in bytes of the stack
		//@param seamless -> seamless means we don't align and the data has no holes
		//in it, so basically an array.
		StackAllocator(ptrsize stackSize, bool seamless);

		//Manual init and shutDown.
		bool initialize();
		bool shutDown();

		//Allocates chunk.
		void*	allocate(ptrsize size, ptrsize align);

		void*	getFrame(){ return m_stackBase + m_pointer; }

		//Deallocates last frame.
		void*	deallocate();
		//Deallocates all
		void	deallocateWhole();

		inline	ptrsize	size() { return m_pointer; }
		inline	byte*	base() { return m_stackBase; }


	private:
		ptrsize	m_stackSize;
		ptrsize	m_pointer;
		byte*	m_stackBase;
		bool	m_seamless;
	};
}


#endif // !BS_STACKALLOCATOR_H
