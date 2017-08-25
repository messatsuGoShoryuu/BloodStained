#include "bs_Path.h"

#include <Platform/bs_Platform.h>

namespace bs
{
#ifdef BS_WINDOWS

#define GET_APP_FILE_NAME getWindowsFileName()


	static String getWindowsFileName()
	{
		wchar_t buffer[MAX_PATH];
		int bytes = GetModuleFileNameW(NULL, buffer, MAX_PATH);
		return String(buffer);
	}

	

#endif	

#ifdef BS_APPLE
#include <sys/param.h>

#define GET_APP_FILE_NAME getMacOSXFileName()

	static String getMacOSXFileName()
	{
		char buffer[256];
		getcwd(buffer, 256);
		return String(buffer);
	}

#endif




	Path Path::s_root;
	Path Path::s_data;

	Path::Path()
	{

	}

	Path::Path(const Path& p)
		:m_string(p.m_string)
	{

	}

	Path::Path(String p)
		:m_string(p)
	{
		_convertSlashes();
	}

	Path::~Path()
	{

	}

	void Path::toParent()
	{
		if (m_string.length() > 1)
		{
			char c = ' ';

			m_string.backSpace();
			c = m_string[m_string.length() - 1];
			if (c == '/')	m_string.backSpace();

			//remove until next slash
			while (c != '/' && m_string.length() > 1)
			{
				m_string.backSpace();
				c = m_string[m_string.length() - 1];
			}
		}
	}

	String Path::relativeName()
	{
		//String to store relative name.
		String result;

		//Store length in local variable.
		ui32 length = m_string.length();
		i32 i = length - 1;
		
		//If this is an ending slash, start from the previous character.
		if (m_string[i] == '/') i--;
		

		//We should only continue if the index is valid
		if (i > 0)
		{
			//Backtrack until a slash is found.
			for (i; i >= 0; i--)
			{
				if (m_string[i] == '/')
				{
					i++;
					break;
				}
			}

			//Copy the string until next slash, or the end.
			for (ui32 j = i; j < length; j++)
			{
				result.add(m_string[j]);
				if (m_string[j] == '/') break;
			}
		}
		return result;
	}

	String Path::relativeName() const
	{
		String result;
		ui32 length = m_string.length();
		i32 i = length - 1;
		if (m_string[i] == '/') i--;

		if (i > 0)
		{
			for (i = m_string.length() - 1; i >= 0; i--)
			{
				if (m_string[i] == '/')
				{
					i++;
					break;
				}
			}
		}

		for (ui32 j = i; j < length; j++)
		{
			result.add(m_string[j]);
			if (m_string[j] == '/') break;
		}
		return result;
	}

	void Path::toChild(String childName)
	{
		//Add folder name.
		m_string += childName;
		//Add slash.
		if (m_string[m_string.length() - 1] != '/')
			m_string += '/';
	}

	void Path::toFileName(String fileName)
	{
		m_string += fileName;
	}

	//Converts back slashes to forward slashes
	void Path::_convertSlashes()
	{
		ui32 l = m_string.length();
		for (ui32 i = 0; i < l; i++)
		{
			if (m_string[i] == '\\') m_string[i] = '/';
		}
	}

	void Path::operator=(const Path& p)
	{
		m_string = p.m_string;
	}

	void Path::operator=(const String& s)
	{
		m_string = s;
	}

	void Path::operator=(const char* c)
	{
		m_string = c;
	}

	void Path::operator=(const wchar_t* c)
	{
		m_string = c;
	}

	const Path&	Path::root()
	{
		if (s_root.length() == 0)
		{
			s_root = Path(GET_APP_FILE_NAME);

#ifdef _WIN32 || WIN64
			s_root.toParent();
#elif defined __APPLE__
			root.m_string += '/';
#endif
		}
		return s_root;
	}

	const Path& Path::data()
	{

		if (s_data.length() == 0)
		{
			s_data = Path(GET_APP_FILE_NAME);
#ifdef BS_WINDOWS
			s_data.toParent();
#elif defined BS_APPLE
			s_data.m_string.m_buffer.last() = '/';
#endif
			s_data.toChild("Data");
		}
		return s_data;
	}
}