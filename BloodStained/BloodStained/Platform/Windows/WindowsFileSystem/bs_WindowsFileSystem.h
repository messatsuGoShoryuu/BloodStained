#ifndef BS_WINDOWSFILESYSTEM_H
#define BS_WINDOWSFILESYSTEM_H

#include "../../../Utilities/bs_types.h"



namespace bs
{
	template <class T>
	class Array;

	class String;

	class WindowsFileSystem
	{
	public:
		static void*	open(const char* filename);
		static void		close(void* handle);
		static bool		read(void* handle, void* buffer, size_t size);
		static bool		read(void* handle, char* buffer, size_t size);
		static bool		readLine(void* handle, char* buffer, size_t size);
		static ui32		write(void* handle, const void* buffer, ui32 length);
		static ui32		writeBuffered(void* handle, const void* buffer, ui32 length);
		static ui32		getFileSize(void* handle);
		static void		createDirectory(const char* pathName);
		static bool		getDirectoryContent(const char* directory, Array<String>& array);
	};
}


#endif // !BS_WINDOWSFILESYSTEM_H
