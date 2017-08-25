#ifndef _BS_STRING_H_
#define _BS_STRING_H_


#include "../Containers/bs_Array.h"

#define NULL_CHARACTER '\0'

namespace bs
{
	class String
	{
	public:
		//Constructors:

		//Default constcutor:
		String();
		//Default destructor:
		~String();
		//Copy constructor
		String(const String& s);

		//8-bit char constructor:
		String(const char* string);
		//Wide char constructor:
		String(const wchar_t* string);

	public:
		//Accessors:

		//UTF-8 C-string
		inline	const char*	utf8(){ return m_buffer.count() <= 0 ? NULL_CHARACTER : &m_buffer[0]; }
		inline	const char* utf8() const { return m_buffer.count() <= 0 ? NULL_CHARACTER : &m_buffer[0]; }

		//Length of the string
		inline const ui32 length(){ return m_buffer.count() > 0 ? m_buffer.count() - 1 : 0; }
		inline const ui32 length() const{ return m_buffer.count() > 0 ? m_buffer.count() - 1 : 0; }

		inline const ui32 hashedId(){ return m_hashedId; }
		inline const ui32 hashedId() const { return m_hashedId; }

		//Float precision when displaying
		inline const ui8  floatPrecision(){ return m_floatPrecision; }
		inline const ui8  floatPrecision() const { return m_floatPrecision; }

		void	setFloatPrecision(ui8 value){ m_floatPrecision = value; }

		String	getNextWord(ui32& current) const;
		String	getSubString(ui32 startIndex, ui32 endIndex) const;
		String	getSubString(ui32 startIndex) const;
		Array<String>	split(const char* splitters);
		Array<String>	split(const String& splitters);
	public:
		//Simple operations:

		inline void clear(){ m_buffer.clear(); }
		inline void clearFromMemory(){ m_buffer.reset(); }

		inline void resize(ui32 size){ m_buffer.resize(size); }

		inline			char	backSpace()
		{
			char last = m_buffer[m_buffer.count() - 2];
			m_buffer.pop();
			m_buffer.last() = NULL_CHARACTER;
			return last;
		}

		inline void		add(char c)
		{
			if (m_buffer.count() == 0)
			{
				m_buffer.add(c);
				m_buffer.add(NULL_CHARACTER);
				return;
			}
			m_buffer.last() = c;
			m_buffer.add(NULL_CHARACTER);

			_hash();
		}

	private:
		void _hash();

	public:
		//Operators:
		String	operator+(const String& other);
		String	operator+(const char* string);
		String	operator+(const wchar_t* wstring);
		String	operator+(char c);
		String	operator+(const i32& i);
		String	operator+(const f32& f);

		void	operator+=(char c);
		void	operator+=(const char* string);
		void	operator+=(const wchar_t* string);
		void	operator+=(const i32& i);
		void	operator+=(const f32& f);
		void	operator+=(const String& other);
		

		void	operator=(const String& other);
		void	operator=(const char* other);
		void	operator=(const wchar_t* other);

		bool	operator==(const String& other);
		bool	operator==(const String& other) const;
		bool	operator==(const char* other);
		bool	operator==(const char* other) const;
		bool	operator==(const wchar_t* other);
		bool	operator==(const wchar_t* other) const;

		bool	operator !=(const String& other);
		bool	operator !=(const String& other) const;
		bool	operator !=(const char* other);
		bool	operator !=(const char* other) const;
		bool	operator !=(const wchar_t* other);
		bool	operator !=(const wchar_t* other) const;

		char&		operator[](const size_t& index);
		const char&	operator[](const size_t& index) const;
		

	private:
		Array<char>	m_buffer;
		ui32 m_hashedId;
		ui8  m_floatPrecision;
	};
}

#endif // !BS_STRING_H
