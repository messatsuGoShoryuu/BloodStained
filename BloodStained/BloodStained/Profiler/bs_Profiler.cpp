#include "bs_Profiler.h"


namespace bs
{
	ui64 Profiler::m_allocatedBytes = 0;
	ui64 Profiler::m_usedBytes = 0;

	void Profiler::initialize()
	{
		m_allocatedBytes = 0;
		m_usedBytes = 0;
	}

	void Profiler::addAllocatedBytes(ui64 bytes)
	{
		m_allocatedBytes += bytes;
	}

	void Profiler::addUsedBytes(ui64 bytes)
	{
		m_usedBytes += bytes;
	}

	void Profiler::removeAllocatedBytes(ui64 bytes)
	{
		m_allocatedBytes -= bytes;
	}

	void Profiler::removeUsedBytes(ui64 bytes)
	{
		m_usedBytes -= bytes;
	}
}