#ifndef _BS_MEMORY_H_
#define _BS_MEMORY_H_

#include <Windows.h>
#include <memory>

#include "../Utilities/bs_types.h"
#include "../Math/bs_math.h"
#include "../Utilities/bs_define.h"
#include <assert.h>


		#define BS_Malloc(SIZE) malloc(SIZE)

		#define BS_Free(ITEM) free(ITEM)

		#define Place(PTR, TYPE, ARGS) new(PTR) TYPE(ARGS)

		#define Destroy(PTR, TYPE) PTR->~TYPE()

#define BS_KILOBYTE	0x400
#define BS_MEGABYTE 0x100000
#define BS_GIGABYTE 0x40000000

#endif // !BS_MEMORY
