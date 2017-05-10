//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.

#ifndef BS_MURMURHASH3_H
#define BS_MURMURHASH3_H

#include "../../../Utilities/bs_types.h"

//-----------------------------------------------------------------------------
// Platform-specific functions and macros

// Microsoft Visual Studio

#if defined(_MSC_VER)



// Other compilers

#else	// defined(_MSC_VER)

#include <stdint.h>

#endif // !defined(_MSC_VER)


//-----------------------------------------------------------------------------

void MurmurHash3_x86_32(const void * key, int len, uint32_t seed, void * out);

void MurmurHash3_x86_128(const void * key, int len, uint32_t seed, void * out);

void MurmurHash3_x64_128(const void * key, int len, uint32_t seed, void * out);

//-----------------------------------------------------------------------------

#endif // _MURMURHASH3_H_