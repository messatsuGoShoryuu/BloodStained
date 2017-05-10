#ifndef BS_PROFILER_H
#define BS_PROFILER_H

#include "../Utilities/bs_types.h"

namespace bs
{
	class Profiler
	{
	public:
		static void initialize();

		static void addUsedBytes(ui64 bytes);
		static void addAllocatedBytes(ui64 bytes);
		static void removeUsedBytes(ui64 bytes);
		static void removeAllocatedBytes(ui64 bytes);
		static void addNewCount(ui64 bytes);
		static void addDeleteCount(ui64 bytes);
		static void addPlaceCount(ui64 bytes);
		static void addDestroyCount(ui64 bytes);
		static void addMallocCount(ui64 bytes);
		static void addFreeCount(ui64 bytes);
		inline	static void addPoolCount(){ m_poolCount++; }
		inline	static void removePoolCount(){ m_poolCount--; }

		inline static ui64 getAllocatedBytes(){ return m_allocatedBytes; }
		inline static ui64 getUsedBytes(){ return m_usedBytes; }
		inline static ui64 getUnusedBytes(){ return m_allocatedBytes - m_usedBytes; }
		inline static ui64 getNewCount(){ return m_newCount; }
		inline static ui64 getDeleteCount(){ return m_deleteCount; }
		inline static ui64 getPlaceCount(){ return m_placeCount; }
		inline static ui64 getDestroyCount(){ return m_destroyCount; }
		inline static ui64 getMallocCount() { return m_mallocCount; }
		inline static ui64 getFreeCount() { return m_freeCount; }
		inline static ui64 getPoolCount(){ return m_poolCount; }

		static void printMemoryStats(const char* functionName);

	private:
		static ui64	m_allocatedBytes;
		static ui64	m_usedBytes;
		static ui64 m_newCount;
		static ui64 m_deleteCount;
		static ui64 m_placeCount;
		static ui64 m_mallocCount;
		static ui64 m_freeCount;
		static ui64 m_destroyCount;
		static ui64 m_poolCount;
	};
}


#endif // !BS_PROFILER_H
