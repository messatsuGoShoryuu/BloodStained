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
		StackAllocator(ui32 stackSize);

		//Manual init and shutDown.
		bool initialize();
		bool shutDown();

		//Allocates chunk.
		void*	allocate(ui32 size, ui32 align);

		void*	getFrame(){ return m_stackBase + m_pointer; }

		//Deallocates until last frame.
		void*	deallocate();


	private:
		ui64	m_stackSize;
		ui32	m_pointer;
		byte*	m_stackBase;
	};
}


#endif // !BS_STACKALLOCATOR_H
