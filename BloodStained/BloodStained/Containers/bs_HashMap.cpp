#include "bs_HashMap.h"
#include "../Utilities/bs_String.h"


ui32 getStringHash(const bs::String& key)
{
	return key.hashedId();
}