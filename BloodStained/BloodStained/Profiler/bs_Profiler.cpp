#include "bs_Profiler.h"
#include <iostream>

namespace bs
{
	ui64 Profiler::m_allocatedBytes = 0;
	ui64 Profiler::m_usedBytes = 0;
	ui64 Profiler::m_newCount = 0;
	ui64 Profiler::m_deleteCount = 0;
	ui64 Profiler::m_placeCount = 0;
	ui64 Profiler::m_destroyCount = 0;
	ui64 Profiler::m_freeCount = 0;
	ui64 Profiler::m_mallocCount = 0;
	ui64 Profiler::m_poolCount = 0;

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

	void Profiler::addNewCount(ui64 bytes)
	{
		m_newCount += bytes;
	}

	void Profiler::addDeleteCount(ui64 bytes)
	{
		m_deleteCount += bytes;
	}

	void Profiler::addPlaceCount(ui64 bytes)
	{
		m_placeCount += bytes;
	}

	void Profiler::addDestroyCount(ui64 bytes)
	{
		m_destroyCount += bytes;
	}

	void Profiler::addMallocCount(ui64 bytes)
	{
		m_mallocCount += bytes;
	}
	void Profiler::addFreeCount(ui64 bytes)
	{
		m_freeCount += bytes;
	}

	void Profiler::printMemoryStats(const char* functionName)
	{
		std::cout << std::endl;
		std::cout << "Call made at " << functionName << std::endl;
		std::cout << "Memory Stats:" << std::endl;
		std::cout << "Allocated Memory : " << getAllocatedBytes() << " bytes." << std::endl;
		std::cout << "Used Memory : " << getUsedBytes() << " bytes." << std::endl;
		std::cout << "Unused Memory: " << getUnusedBytes() << " bytes." << std::endl;
		std::cout << "New count: " << getNewCount() << std::endl;
		std::cout << "Delete count: " << getDeleteCount() << std::endl;
		std::cout << "Malloc count: " << getMallocCount() << std::endl;
		std::cout << "Free count: " << getFreeCount() << std::endl;
	//	std::cout << "Place count: " << getPlaceCount() << std::endl;
	//	std::cout << "Destroy count: " << getDestroyCount() << std::endl;
		std::cout << "Pool count = " << getPoolCount() << std::endl;
		std::cout << std::endl;
	}
}