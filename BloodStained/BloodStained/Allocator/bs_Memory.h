#ifndef BS_MEMORY_H
#define BS_MEMORY_H

#include <memory>

#include "../Profiler/bs_Profiler.h"
#include "../Utilities/bs_types.h"
#include "../Utilities/bs_math.h"
#include "../Utilities/bs_define.h"

	#ifdef BS_PROFILE_MEMORY

		#define Malloc(SIZE) setHeader(SIZE);\
			bs::Profiler::addAllocatedBytes(SIZE)

		#define Free(ITEM) bs::Profiler::removeAllocatedBytes(readHeader(ITEM))

		#define Place(PTR, TYPE, ARGS) new(PTR) TYPE(ARGS);\
			bs::Profiler::addUsedBytes(sizeof(TYPE))

		#define Destroy(PTR, TYPE) PTR->~TYPE();\
			bs::Profiler::removeUsedBytes(sizeof(TYPE))
		#else

		#define Malloc(SIZE) malloc(SIZE)

		#define Free(ITEM) free(SIZE)

		#define Place(PTR, TYPE, ARGS) new(PTR) TYPE ARGS

		#define Destroy(PTR, TYPE) PTR->~TYPE()

	#endif

//allow memory tracking


	#ifdef BS_PROFILE_MEMORY

	void* setHeader(ui32 size);
	ui32 readHeader(void* ptr);

	void* operator new(std::size_t size)
	{
		bs::Profiler::addUsedBytes(size);
		bs::Profiler::addAllocatedBytes(size);
		return setHeader(size);
	}

	void operator delete(void* ptr)
	{
		ui32 size = readHeader(ptr);
		bs::Profiler::removeAllocatedBytes(size);
		bs::Profiler::removeUsedBytes(size);
	}

	void* operator new[](std::size_t size)
	{
		bs::Profiler::addUsedBytes(size);
		bs::Profiler::addAllocatedBytes(size);
		return setHeader(size);
	}

	void operator delete[](void* ptr)
	{
		ui32 size = readHeader(ptr);
		bs::Profiler::removeAllocatedBytes(size);
		bs::Profiler::removeUsedBytes(size);
	}


	
	void* setHeader(ui32 size)
	{
		ui32* ptr = (ui32*)malloc(sizeof(ui32) + size);
		*ptr = size;
		ptr++;
		return (void*)ptr;
	}

	ui32 readHeader(void* ptr)
	{
		ui32* item = (ui32*)ptr;
		item--;
		ptr = (void*)item;
		ui32 result = *item;
		free(ptr);
		return result;
	}
	#endif

#endif // !BS_MEMORY
