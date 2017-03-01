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

		static ui64 getAllocatedBytes(){ return m_allocatedBytes; }
		static ui64 getUsedBytes(){ return m_usedBytes; }
		static ui64 getUnusedBytes(){ return m_allocatedBytes - m_usedBytes; }


	private:
		static ui64	m_allocatedBytes;
		static ui64	m_usedBytes;
	};
}


#endif // !BS_PROFILER_H
