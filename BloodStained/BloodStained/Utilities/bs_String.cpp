#include "../External/HashFunctions/MurmurHash/bs_MurmurHash.h"
#include "bs_String.h"

namespace bs
{
#ifdef	_MSC_VER
	//visual studio
	void encodeUtf8(const wchar_t* source, Array<char>* out)
	{
		size_t	wideStringLength = wcslen(source);
		ui32 utf8StringLength = (ui32)WideCharToMultiByte(CP_UTF8, 0, source, wideStringLength, NULL, 0, NULL, NULL);
		char* utf8String = (char*)BS_Malloc(utf8StringLength);
		if ((*out).count() > 0)(*out).clear();
		WideCharToMultiByte(CP_UTF8, 0, source, wideStringLength, utf8String, utf8StringLength, NULL, NULL);
		char c = utf8String[0];
		size_t i = 0;
		while (i<utf8StringLength)
		{
			(*out).add(c);
			i++;
			c = utf8String[i];
		}
		(*out).add(NULL_CHARACTER);

		BS_Free(utf8String);
	}

	void	decodeUtf8(const Array<char>& a, wchar_t* out)//don't forget to free out
	{
		if (a.count() == 0) return;
		int wideStringLength = MultiByteToWideChar(CP_UTF8, 0, &a[0], (int)a.count(), NULL, 0);
		out = (wchar_t*)BS_Malloc(wideStringLength * sizeof(wchar_t));
		MultiByteToWideChar(CP_UTF8, 0, &a[0], (int)a.count(), out, wideStringLength);
	}
#endif

#ifdef __APPLE__
#include <stdlib.h>

	void encodeUtf8(const wchar_t* source, Array<char>* out)
	{
		size_t	wideStringLength = wcslen(source);

		size_t utf8StringLength = wcstombs(NULL, source, wideStringLength);
		char* utf8String = (char*)BS_Malloc(char, utf8StringLength);
		if ((*out).size() > 0)(*out).clear();
		wcstombs(utf8String, source, wideStringLength);
		char c = utf8String[0];
		size_t i = 0;
		while (i<utf8StringLength)
		{
			(*out).add(c);
			i++;
			c = utf8String[i];
		}
		(*out).add(NULL_CHARACTER);

		BS_Free(utf8String);
	}

	void	decodeUtf8(Array<char>& a, wchar_t* out)//don't forget to free out
	{
		if (a.size() == 0) return;
		size_t wideStringLength = mbstowcs(NULL, &a[0], a.size());
		out = (wchar_t*)BS_Malloc(wchar_t, wideStringLength);
		mbstowcs(out, &a[0], a.size());
	}


#endif

	//Constructors:

	//Default constcutor:
	String::String()
		:m_floatPrecision(2)
	{

	}
	//Default destructor:
	String::~String()
	{

	}
	//Copy constructor
	String::String(const String& s)
		:m_buffer(s.m_buffer),
		m_hashedId(s.m_hashedId),
		m_floatPrecision(s.m_floatPrecision)
	{
		
	}

	//8-bit char constructor:
	String::String(const char* string)
		:m_floatPrecision(2)
	{
		if (!string) return;
		for (ui32 i = 0; string[i] != NULL_CHARACTER; i++)
		{
			m_buffer.add(string[i]);
		}
		m_buffer.add(NULL_CHARACTER);
		_hash();
	}

	//Wide char constructor:
	String::String(const wchar_t* string)
		:m_floatPrecision(2)
	{
		encodeUtf8(string, &m_buffer);
		_hash();
	}

	void String::_hash()
	{
		MurmurHash3_x86_32(&m_buffer[0], m_buffer.count(), 0, &m_hashedId);
	}

	//Operators:
	String	String::operator+(const String& other)
	{
		String result(SELF);

		//Remove null character from assembly point.
		result.m_buffer.pop();

		//Assemble two strings.
		result.m_buffer += other.m_buffer;

		//Ensure null character is inserted to the end.
		if (result.m_buffer.last() != NULL_CHARACTER) result.m_buffer.add(NULL_CHARACTER);

		//Calculate hash.
		result._hash();

		return result;
	}
	String	String::operator+(const char* string)
	{
		String result(SELF);

		//Remove null character from assembly point.
		result.m_buffer.pop();

		//Assemble two strings.
		for (ui32 i = 0; string[i] != NULL_CHARACTER; i++)
			result.m_buffer.add(string[i]);

		//Ensure null character is inserted to the end.
		if (result.m_buffer.last() != NULL_CHARACTER) result.m_buffer.add(NULL_CHARACTER);

		//Calculate hash.
		result._hash();

		return result;
	}
	String	String::operator+(const wchar_t* wstring)
	{
		String result(SELF);

		//Encode array for new string
		Array<char> other;
		encodeUtf8(wstring, &other);

		//Remove null character from assembly point.
		result.m_buffer.pop();

		//Assemble two strings.
		result.m_buffer += other;

		//Ensure null character is inserted to the end.
		if (result.m_buffer.last() != NULL_CHARACTER) result.m_buffer.add(NULL_CHARACTER);

		//Calculate hash.
		result._hash();

		return result;
	}
	String	String::operator+(char c)
	{
		String result(SELF);

		//Remove null character from assembly point.
		result.m_buffer.pop();

		//Assemble two strings.
		result.m_buffer.add(c);

		//Ensure null character is inserted to the end.
		if (result.m_buffer.last() != NULL_CHARACTER) result.m_buffer.add(NULL_CHARACTER);

		//Calculate hash.
		result._hash();

		return result;
	}
	String	String::operator+(const i32& i)
	{
		String result(SELF);

		char buffer[10];
#if _MSC_VER
		_itoa_s(i, buffer, 10);
#endif
		result += buffer;
		return result;

		return result;
	}
	String	String::operator+(const f32& f)
	{
		String result(SELF);

		char buffer[32];
		char* precision;
		switch (m_floatPrecision)
		{
			case 1:
				precision = "%.1f";
				break;
			case 2:
				precision = "%.2f";
				break;
			case 3:
				precision = "%.3f";
				break;
			case 4:
				precision = "%.4f";
				break;
			case 5:
				precision = "%.5f";
				break;
			case 6:
				precision = "%.6f";
				break;
			case 7:
				precision = "%.7f";
				break;
			case 8:
				precision = "%.8f";
				break;
			case 9:
				precision = "%.9f";
				break;
			default:
				precision = "%.1f";
		}

#if _MSC_VER
		sprintf_s(buffer, precision, f);
#else
		sprintf(buffer, precision, f);
#endif

		result += buffer;
		return result;
	}

	void	String::operator+=(char c)
	{
		m_buffer.pop();

		//Assemble two strings.
		m_buffer.add(c);

		//Ensure null character is inserted to the end.
		if (m_buffer.last() != NULL_CHARACTER) m_buffer.add(NULL_CHARACTER);

		//Calculate hash.
		_hash();
	}
	void	String::operator+=(const char* string)
	{
		//Remove null character from assembly point.
		m_buffer.pop();

		//Assemble two strings.
		for (ui32 i = 0; string[i] != NULL_CHARACTER; i++)
			m_buffer.add(string[i]);

		//Ensure null character is inserted to the end.
		if (m_buffer.last() != NULL_CHARACTER) m_buffer.add(NULL_CHARACTER);

		//Calculate hash.
		_hash();
	}
	void	String::operator+=(const wchar_t* wstring)
	{
		//Encode array for new string
		Array<char> other;
		encodeUtf8(wstring, &other);

		//Remove null character from assembly point.
		m_buffer.pop();

		//Assemble two strings.
		m_buffer += other;

		//Ensure null character is inserted to the end.
		if (m_buffer.last() != NULL_CHARACTER) m_buffer.add(NULL_CHARACTER);

		//Calculate hash.
		_hash();
	}

	void	String::operator+=(const i32& i)
	{
		char buffer[10];
#if _MSC_VER
		_itoa_s(i, buffer, 10);
#endif
		SELF += buffer;
	}

	void	String::operator+=(const f32& f)
	{
		char buffer[32];
		char* precision;
		switch (m_floatPrecision)
		{
			case 1:
				precision = "%.1f";
				break;
			case 2:
				precision = "%.2f";
				break;
			case 3:
				precision = "%.3f";
				break;
			case 4:
				precision = "%.4f";
				break;
			case 5:
				precision = "%.5f";
				break;
			case 6:
				precision = "%.6f";
				break;
			case 7:
				precision = "%.7f";
				break;
			case 8:
				precision = "%.8f";
				break;
			case 9:
				precision = "%.9f";
				break;
			default:
				precision = "%.1f";
		}
#if _MSC_VER
		sprintf_s(buffer, precision, f);
#else
		sprintf(buffer, precision, f);
#endif

		SELF += buffer;
	}
	void	String::operator+=(const String& other)
	{
		//Remove null character from assembly point.
		m_buffer.pop();

		//Assemble two strings.
		m_buffer += other.m_buffer;

		//Ensure null character is inserted to the end.
		if (m_buffer.last() != NULL_CHARACTER) m_buffer.add(NULL_CHARACTER);

		//Calculate hash.
		_hash();
	}


	void	String::operator=(const String& other)
	{
		m_buffer = other.m_buffer;
		m_hashedId = other.m_hashedId;
	}

	void	String::operator=(const char* other)
	{
		m_buffer.clear();
		if (!other) return;
		for (ui32 i = 0; other[i] != NULL_CHARACTER; i++)
		{
			m_buffer.add(other[i]);
		}
		m_buffer.add(NULL_CHARACTER);
		_hash();
	}
	void	String::operator=(const wchar_t* other)
	{
		m_buffer.clear();
		encodeUtf8(other, &m_buffer);
		_hash();
	}

	bool	String::operator==(const String& other)
	{
		return m_hashedId == other.m_hashedId;
	}

	bool	String::operator==(const String& other) const
	{
		return m_hashedId == other.m_hashedId;
	}

	bool	String::operator==(const char* other) 
	{
		return strcmp(&m_buffer[0], other) == 0;
	}

	bool	String::operator==(const char* other) const
	{
		return strcmp(&m_buffer[0], other) == 0;
	}

	bool	String::operator==(const wchar_t* other) 
	{
		wchar_t* out = nullptr;
		decodeUtf8(m_buffer, out);

		bool result = wcscmp(out, other) == 0;

		BS_Free(out);

		return result;
	}

	bool	String::operator==(const wchar_t* other) const
	{
		wchar_t* out = nullptr;
		decodeUtf8(m_buffer, out);

		bool result = wcscmp(out, other) == 0;

		BS_Free(out);

		return result;
	}

	bool	String::operator!=(const String& other)
	{
		return !(SELF == other);
	}
	bool	String::operator!=(const char* other)
	{
		return !(SELF == other);
	}
	bool	String::operator!=(const wchar_t* other)
	{
		return !(SELF == other);
	}

	char&	String::operator[](const size_t& index)
	{
		return m_buffer[index];
	}

	const char&	String::operator[](const size_t& index) const
	{
		return m_buffer[index];
	}
}