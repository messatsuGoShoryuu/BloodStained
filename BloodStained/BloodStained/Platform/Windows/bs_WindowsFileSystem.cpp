#include "bs_WindowsFileSystem.h"

#include <Containers/bs_Array.h>
#include <Utilities/bs_String.h>

#include <Windows.h>



namespace bs
{
	void* WindowsFileSystem::open(const char* filename)
	{
		HANDLE h =  CreateFileA(filename, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (h == INVALID_HANDLE_VALUE)
		{
			DWORD error = GetLastError();

			std::cout << "Error : invalid handle" << std::endl;
		}
		return h;
	}

	void WindowsFileSystem::close(void* handle)
	{
		CloseHandle(handle);
	}

	bool WindowsFileSystem::read(void* handle, void* buffer, size_t size)
	{
		//Empty DWORD to store read bytes.
		DWORD bytesRead;
		bool success = false;

		//Attempt to read
		ReadFile(handle, buffer, size, &bytesRead, NULL);

		//Did we read bytes?
		if (bytesRead != 0) success = true;
		return success;
	}

	bool WindowsFileSystem::read(void* handle, char* buffer, size_t size)
	{
		//Empty DWORD to store read bytes.
		DWORD bytesRead;
		bool success = false;
		ReadFile(handle, buffer, size, &bytesRead, NULL);

		//Did we read bytes?
		if (bytesRead != 0) success = true;

		//Add nullcharacter to the end of the string if read bytes are less than allocated size.
		if (bytesRead < size) buffer[bytesRead] = '\0';
		return success;
	}

	ui32	WindowsFileSystem::write(void* handle, const void* buffer, ui32 length)
	{
		DWORD bytesWritten;

		WriteFile(handle, buffer, length, &bytesWritten, NULL);
		return (ui32)bytesWritten;
	}

	ui32	WindowsFileSystem::writeBuffered(void* handle, const void* buffer, ui32 length)
	{
		DWORD bytesWritten;
		WriteFile(handle, buffer, length, &bytesWritten, NULL);
		SetFilePointer(handle, bytesWritten, NULL, FILE_CURRENT);
		return (ui32)bytesWritten;
	}

	bool	WindowsFileSystem::readLine(void* handle, char* buffer, size_t size)
	{
		DWORD bytesRead;
		bool success = false;
		ReadFile(handle, buffer, size, &bytesRead, NULL);
		if (bytesRead != 0) success = true;
		ui32 i;

		for (i = 0; i < bytesRead; i++)
		{
			if (i <bytesRead)
			{
				if (buffer[i] == ('\r'))
				{
					buffer[i] = '\0';
					if (buffer[i + 1] == '\n')
					{
						i++;
						break;
					}
				}
			}
			else if (buffer[i] == ('\n'))
			{
				buffer[i] = '\0';
				break;
			}
		}

		if (i >= bytesRead) buffer[i] = '\0';
		else i++;

		SetFilePointer(handle, i - bytesRead, NULL, FILE_CURRENT);

		return success;
	}

	ui32	WindowsFileSystem::getFileSize(void* handle)
	{
		LARGE_INTEGER i;
		GetFileSizeEx((HANDLE)handle, &i);
		std::cout << "Size = " << i.QuadPart << std::endl;

		return i.QuadPart;
	//	return GetFileSize(handle, NULL);
	}

	void	WindowsFileSystem::createDirectory(const char* fileName)
	{
	 	CreateDirectoryA(fileName, NULL);
	}

	bool	WindowsFileSystem::getDirectoryContent(const char* directory, Array<String>& array)
	{
		//Initialize WIN32_FIND_DATA structure
		WIN32_FIND_DATA findData;
		memset(&findData, 0, sizeof(WIN32_FIND_DATA));

		String fullPath = directory;
		fullPath += '*';
		//Start scanning directory.
		HANDLE handle = FindFirstFile(fullPath.utf8(), &findData);

		//Create string for full path once, use it through the iteration
		//to avoid multiple allocations.
		

		while (handle != INVALID_HANDLE_VALUE)
		{
			//Turn fileName into full path + fileName
			fullPath = directory;
			fullPath.backSpace();
			fullPath = fullPath + "/" + findData.cFileName;

			//Get file attribute to check if file is folder.
			DWORD fileAttributes = GetFileAttributes(fullPath.utf8());

			//If this is a folder add a slash.
			if (fileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				String fileName = findData.cFileName;
				fileName.add('/');
				array.add(fileName);
			}
			else array.add(findData.cFileName);

			//Check for errors.
			if (!FindNextFile(handle, &findData)) return false;
		}

		return true;
	}
}
