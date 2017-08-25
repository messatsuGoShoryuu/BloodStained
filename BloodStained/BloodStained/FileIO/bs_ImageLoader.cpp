#include "bs_ImageLoader.h"
#include "bs_FileSystem.h"
#include "../External/ImageLoading/LodePng/lodepng.h"


namespace bs
{
	byte*	PNGLoader::load(byte** buffer, ui32& width, ui32& height, size_t size)
	{
		byte* result = NULL;
		ui32 error = lodepng_decode32(&result, &width, &height, *buffer, size);
		if (error)
		{
			std::cout << lodepng_error_text(error) << std::endl;
			return NULL;
		}
		return result;
	}

	byte*	ImageLoader::load(byte** buffer, const FileInfo* file, ui32& width, ui32& height)
	{
		byte* result = NULL;
		if (strcmp(file->extension, "png") == 0)
		{
			result = PNGLoader::load(buffer, width, height, file->size);
			if (result == NULL)
			{
				std::cout << file->path.utf8() << " could not be loaded." << std::endl;
			}
			else return result;
		}
		else
		{
			std::cout << "The format \"" << file->extension << "\" is not supported by Basics Engine" << std::endl;
			return NULL;
		}

		free(result);
		return NULL;
	}
	
}