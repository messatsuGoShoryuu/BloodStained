#ifndef BS_IMAGELOADER_H
#define BS_IMAGELOADER_H

#include <Utilities/bs_types.h>


namespace bs
{
	struct FileInfo;

	class PNGLoader
	{
	public:
		static	byte*	load(byte* buffer, ui32& width, ui32& height, size_t size);
	};

	class ImageLoader
	{
	public:
		static	byte*	load(byte* buffer, const struct FileInfo* file, ui32& width, ui32& height);
	};
}

#endif