#ifndef BS_MEMORY_H
#define BS_MEMORY_H

#include <Windows.h>
#include <memory>

#include "../Profiler/bs_Profiler.h"
#include "../Utilities/bs_types.h"
#include "../Math/bs_math.h"
#include "../Utilities/bs_define.h"
#include <assert.h>

	#ifdef BS_PROFILE_MEMORY


		#define BS_Malloc(SIZE) setHeader(SIZE);\
			bs::Profiler::addAllocatedBytes(SIZE);\
			bs::Profiler::addMallocCount(1)

		#define BS_Free(ITEM) bs::Profiler::removeAllocatedBytes(readHeader(ITEM));\
			bs::Profiler::addFreeCount(1)

		#define Place(PTR, TYPE, ARGS) new(PTR) TYPE(ARGS);\
			bs::Profiler::addUsedBytes(sizeof(TYPE));\
			bs::Profiler::addPlaceCount(sizeof(TYPE))

		#define Destroy(PTR, TYPE) PTR->~TYPE();\
			bs::Profiler::removeUsedBytes(sizeof(TYPE));\
			bs::Profiler::addDestroyCount(sizeof(TYPE))
		#else

		#define BS_Malloc(SIZE) malloc(SIZE)

		#define BS_Free(ITEM) free(SIZE)

		#define Place(PTR, TYPE, ARGS) new(PTR) TYPE ARGS

		#define Destroy(PTR, TYPE) PTR->~TYPE()

	#endif

//allow memory tracking


	#ifdef BS_PROFILE_MEMORY

	void* setHeader(ui32 size);
	ui32 readHeader(void* ptr);

	void* operator new(std::size_t size);
	void operator delete(void* ptr);
	void* operator new[](std::size_t size);
	void operator delete[](void* ptr);
	

	#endif

#endif // !BS_MEMORY
