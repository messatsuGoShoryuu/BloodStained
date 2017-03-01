#include "bs_StackAllocator.h"
#include "../Utilities/bs_math.h"
#include "../Profiler/bs_Profiler.h"

#include<memory>

namespace bs
{
	StackAllocator::StackAllocator()
		:m_pointer(0),
		m_stackBase(nullptr),
		m_stackSize(65536)
	{

	}

	StackAllocator::StackAllocator(ui32 stackSize)
		:m_pointer(0),
		m_stackBase(nullptr),
		m_stackSize(stackSize)
	{

	}

	StackAllocator::StackAllocator(const StackAllocator& s)
		:m_pointer(s.m_pointer),
		m_stackBase(s.m_stackBase),
		m_stackSize(s.m_stackSize)
	{

	}

	StackAllocator::~StackAllocator()
	{
		if (m_stackBase) shutDown();
	}

	bool StackAllocator::initialize()
	{
		m_stackBase = static_cast<byte*>(malloc(m_stackSize));
		if (!m_stackBase) return false;

#ifdef BS_PROFILE_MEMORY
		Profiler::addAllocatedBytes(m_stackSize);
#endif

		m_pointer = 0;
		return true;
	}

	bool StackAllocator::shutDown()
	{
		m_pointer = 0;
		free(m_stackBase);
		m_stackBase = nullptr;
#ifdef BS_PROFILE_MEMORY
		Profiler::removeAllocatedBytes(m_stackSize);
#endif
		return true;
	}

	//Allocates chunk.
	void*	StackAllocator::allocate(ui32 size, ui32 align)
	{
		ui32 intSize = sizeof(ui32);
		if (m_pointer + size + intSize >= m_stackSize) return NULL;

		//move pointer by aligned size
		ui32 frame = m_pointer;
		size = nearest2PowMultipleOf(size, align);
		m_pointer += size;

		//store last frame value and move pointer 
		storeUi32ToByteArray(m_stackBase + m_pointer,frame);
		m_pointer += intSize;

#ifdef BS_PROFILE_MEMORY
		Profiler::addUsedBytes(size + intSize);
#endif

		//return last allocated space
		return m_stackBase + frame;
	}

	//Deallocates until last frame.
	void*	StackAllocator::deallocate()
	{
		ui32 intSize = sizeof(ui32);

		//if the pointer is at head return pointer
		if (m_pointer == 0) return m_stackBase;
		
		//read header to get last pointer value
		m_pointer -= intSize;
		ui32* lastFramePtr = reinterpret_cast<ui32*>(m_stackBase + m_pointer);
		ui32 lastFrame = *lastFramePtr;

		//reset bits of last allocated space
		ui32 difference = m_pointer - lastFrame;
		memset(m_stackBase + lastFrame, 0x00, difference);

#ifdef BS_PROFILE_MEMORY
		Profiler::removeUsedBytes((difference + intSize));
#endif

		//move pointer down to last frame and return last frame
		m_pointer = lastFrame;
		return m_stackBase + lastFrame;
	}
}