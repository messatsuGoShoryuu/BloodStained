#include "bs_FileSystem.h"

#ifdef BS_WINDOWS
#include "../Platform/Windows/bs_WindowsFileSystem.h"

#define OPEN(filename)							bs::WindowsFileSystem::open(filename)
#define CLOSE(handle)							bs::WindowsFileSystem::close(handle)
#define READ(handle,buffer,size)				bs::WindowsFileSystem::read(handle,buffer,size);
#define READ_LINE(handle,buffer,size)			bs::WindowsFileSystem::readLine(handle,buffer,size);
#define WRITE(handle,buffer,length)				bs::WindowsFileSystem::write(handle,buffer,length);
#define WRITE_BUFFERED(handle, buffer, length)	bs::WindowsFileSystem::writeBuffered(handle,buffer,length);
#define GET_FILE_SIZE(handle)					bs::WindowsFileSystem::getFileSize(handle);
#define CREATE_DIRECTORY(pathName)				bs::WindowsFileSystem::createDirectory(pathName);
#define GET_DIRECTORY_CONTENT(directory, array)	bs::WindowsFileSystem::getDirectoryContent(directory, array);

#elif defined BS_APPLE
#include "bs_MacOSXFileSystem.hpp"

#define OPEN(filename)							bs::MacOSXFileSystem::open(filename)
#define CLOSE(handle)							bs::MacOSXFileSystem::close(handle)
#define READ(handle,buffer,size)				bs::MacOSXFileSystem::read(handle,buffer,size);
#define READ_LINE(handle,buffer,size)			bs::MacOSXFileSystem::readLine(handle,buffer,size);
#define WRITE(handle,buffer,length)				bs::MacOSXFileSystem::write(handle,buffer,length);
#define GET_FILE_SIZE(handle)					bs::MacOSXFileSystem::getFileSize(handle);
#define CREATE_DIRECTORY(pathName)				bs::MacOSXFileSystem::createDirectory(pathName);

#endif


namespace bs
{
	void FileSystem::initialize()
	{
		createDirectory(Path::data().utf8());
	}

	void FileSystem::shutDown()
	{
		Path::data().~Path();
	}
	FileInfo	FileSystem::open(String fileName)
	{
		//Open file.
		FileInfo result;
		FileHandle handle = OPEN(fileName.utf8());

		//Fill fileinfo
		result.handle = handle;
		result.size = GET_FILE_SIZE(handle);
		result.path = Path(fileName);
		getExtension(result.path, result.extension);
		return result;
	}

	void	FileSystem::close(const FileInfo& fileInfo)
	{
		CLOSE(fileInfo.handle);
	}

	bool	FileSystem::read(const FileInfo& info, char* buffer)
	{
		return READ(info.handle, buffer, info.size);
	}

	bool	FileSystem::read(const FileInfo& info, byte* buffer)
	{
		return READ(info.handle, buffer, info.size);
	}

	bool	FileSystem::readLine(const FileInfo& info, char* buffer)
	{
		return READ_LINE(info.handle, buffer, info.size);
	}

	ptrsize	FileSystem::write(const FileInfo& info, const void* buffer, ptrsize length)
	{
		return WRITE(info.handle, buffer, info.size);
	}

	ptrsize	FileSystem::writeBuffered(const FileInfo& info, const void* buffer, ptrsize length)
	{
		return	WRITE_BUFFERED(info.handle, buffer, info.size);
	}

	void	FileSystem::createDirectory(String pathName)
	{
		CREATE_DIRECTORY(pathName.utf8());
	}

	void	FileSystem::getExtension(Path& path, char* buffer)
	{
		String s(path.string());
		char tempBuffer[8];
		char c = s.backSpace();
		ui32 i = 0;
		while (c != NULL_CHARACTER && i < 8)
		{
			if (c != '/')
			{
				tempBuffer[i] = c;
			}
			c = s.backSpace();
			if (c == '.')
			{
				break;
			}
			else i++;
		}

		ui32 j = 0;

		for (j = 0; j <= i; j++)
		{
			buffer[j] = tempBuffer[i - j];
		}
		buffer[j] = NULL_CHARACTER;
	}

	void FileSystem::getDirectoryContent(const char* directory, Array<String>& array)
	{
		GET_DIRECTORY_CONTENT(directory, array);
	}
}
