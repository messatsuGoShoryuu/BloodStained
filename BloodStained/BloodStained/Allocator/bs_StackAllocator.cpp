#include "bs_StackAllocator.h"
#include "../Math/bs_math.h"

#include<memory>

namespace bs
{
	StackAllocator::StackAllocator()
		:m_pointer(0),
		m_stackBase(nullptr),
		m_stackSize(65536),
		m_seamless(false)
	{

	}

	StackAllocator::StackAllocator(ptrsize stackSize, bool seamless)
		:m_pointer(0),
		m_stackBase(nullptr),
		m_stackSize(stackSize),
		m_seamless(seamless)
	{

	}

	StackAllocator::StackAllocator(const StackAllocator& s)
		:m_pointer(s.m_pointer),
		m_stackBase(s.m_stackBase),
		m_stackSize(s.m_stackSize),
		m_seamless(s.m_seamless)
	{

	}

	StackAllocator::~StackAllocator()
	{
		if (m_stackBase) shutDown();
	}

	bool StackAllocator::initialize()
	{
		m_stackBase = static_cast<byte*>(malloc((size_t)m_stackSize));
		if (!m_stackBase) return false;

		m_pointer = 0;
		return true;
	}

	bool StackAllocator::shutDown()
	{
		m_pointer = 0;
		free(m_stackBase);
		m_stackBase = nullptr;

		return true;
	}

	//Allocates chunk.
	void*	StackAllocator::allocate(ptrsize size, ptrsize align)
	{
		ptrsize intSize = sizeof(ptrsize);
		if (m_pointer + size + intSize >= m_stackSize) return nullptr;

		//move pointer by aligned size
		ptrsize frame = m_pointer;
		if(!m_seamless)size = math::nearest2PowMultipleOf(size, align);
		m_pointer += size;

		if (!m_seamless)
		{
			//store last frame value and move pointer 
			if (sizeof(ptrsize) == 4)
				math::storeUi32ToByteArray(m_stackBase + m_pointer, frame);
			else if (sizeof(ptrsize) == 8)
				math::storeUi64ToByteArray(m_stackBase + m_pointer, frame);

			m_pointer += intSize;
		}

		//return last allocated space
		return m_stackBase + frame;
	}

	//Deallocates until last frame.
	void*	StackAllocator::deallocate()
	{
		if (m_seamless)
		{
			deallocateWhole();
			return m_stackBase;
		}
		ptrsize intSize = sizeof(ptrsize);

		//if the pointer is at head return pointer
		if (m_pointer == 0) return m_stackBase;
		
		//read header to get last pointer value
		m_pointer -= intSize;
		ptrsize* lastFramePtr = reinterpret_cast<ptrsize*>(m_stackBase + m_pointer);
		ptrsize lastFrame = *lastFramePtr;

		//reset bits of last allocated space
		ptrsize difference = m_pointer - lastFrame;
		memset(m_stackBase + lastFrame, 0x00, difference);

		//move pointer down to last frame and return last frame
		m_pointer = lastFrame;

		return m_stackBase + lastFrame;
	}
	void StackAllocator::deallocateWhole()
	{
		memset(m_stackBase, 0x00, m_pointer);
		m_pointer = 0;
	}
}