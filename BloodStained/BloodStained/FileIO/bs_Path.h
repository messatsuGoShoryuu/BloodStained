#ifndef _BS_PATH_H_
#define _BS_PATH_H_

#include "../Utilities/bs_String.h"

namespace bs
{
	class Path
	{
	public:

		//Default constructor
		Path();

		//Copy construttor
		Path(const Path& p);

		//Init by string
		Path(String p);

		//Destructor
		~Path(); 

	public:
		//Change the path to parent folder.
		void	toParent();

		//Change the path to specified child folder.
		void	toChild(String	childName);

		//Add filename to the end of the path.
		void	toFileName(String fileName);

		//Get the relative name after tha path
		String	relativeName();

		String	relativeName() const;

	public:
		//Operators
		void operator=(const Path& p);
		void operator=(const String& s);
		void operator=(const char* c);
		void operator=(const wchar_t* c);

	private:

		//Convert back slashes to forward slashes.
		void	_convertSlashes();

	public:
		//Static accessors
		static const Path&	root();
		static const Path&	data();

		//Member accessors
		inline	const char*	utf8()				{ return m_string.utf8(); }
		inline	const char*	utf8()		const	{ return m_string.utf8(); }
		inline	String		string()			{ return m_string; }
		inline	String		string()	const	{ return m_string; }
		inline	ui32		length()			{ return m_string.length(); }
		inline	ui32		length()	const	{ return m_string.length(); }

	private:
		//Folder containing the .exe file
		static Path	s_root;
		
		//Folder containing the resources.
		static Path	s_data;

	private:
		String m_string;
	};
}


#endif // !BS_PATH_H
