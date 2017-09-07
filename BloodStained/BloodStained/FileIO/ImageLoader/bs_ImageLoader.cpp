#include "bs_ImageLoader.h"
#include "../bs_FileSystem.h"
#include <External/ImageLoading/LodePng/lodepng.h>
#include <Utilities/bs_Error.h>


namespace bs
{
	byte*	PNGLoader::load(byte* buffer, ui32& width, ui32& height, ptrsize size)
	{
		byte* result = NULL;
		ui32 error = lodepng_decode32(&result, &width, &height, buffer, size);
		if (error)
		{
			fatalError(ERROR_ID::IMAGE_LOADING_FAIL, lodepng_error_text(error));
			return nullptr;
		}
		return result;
	}

	byte*	ImageLoader::load(byte* buffer, const FileInfo* file, ui32& width, ui32& height)
	{
		byte* result = NULL;
		if (strcmp(file->extension, "png") == 0)
		{
			result = PNGLoader::load(buffer, width, height, file->size);
			return result;
		}
		else
		{
			fatalError(ERROR_ID::IMAGE_FORMAT_NOT_SUPPORTED, file->extension);
			return NULL;
		}

		free(result);
		return nullptr;
	}
	
}