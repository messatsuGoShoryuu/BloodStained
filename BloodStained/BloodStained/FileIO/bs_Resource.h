#ifndef _BS_RESOURCE_H_
#define _BS_RESOURCE_H_

#include "../Utilities/bs_String.h"

namespace bs
{
	enum class ERROR_ID;

	//Nature of our resource
	enum class RESOURCE_TYPE
	{
		NONE,
		TEXT,
		IMAGE,
		MESH,
		AUDIO,
		FONT,
		SHADER_SCRIPT,
	};

	//Polymorphic resource class. Each type of resource will implement this interface.
	class Resource
	{
		friend class ResourceManager;
		friend class ResourceTester;
	public:
		//Default constructor.
		Resource();
		//Type initializer constructor
		Resource(RESOURCE_TYPE type);
		//Copy constructor.
		Resource(const Resource& r);
		//Virtual destructor.
		virtual ~Resource() = 0;

		//Load interface
		virtual ERROR_ID	load() = 0;
		//Unload interface
		virtual ERROR_ID	unload() = 0;

	public:
		//Accessors
		inline	const bool				isLoaded()			{ return m_isLoaded; }
		inline	const bool				isLoaded()	const	{ return m_isLoaded; }
		inline	const String&			fileName()			{ return m_fileName; }
		inline	const String&			fileName()	const	{ return m_fileName; }
		inline  const RESOURCE_TYPE		type()				{ return m_type; }
		inline  const RESOURCE_TYPE		type()		const	{ return m_type; }
	protected:

		//These should be accessed by ResourceManager
		inline void		_setLoaded(bool value)		{ m_isLoaded = value; }
		inline void		_setType(RESOURCE_TYPE type) { m_type = type; }
		inline void		_setFileName(String fileName){ m_fileName = fileName; }
	protected:
		bool			m_isLoaded;
		RESOURCE_TYPE	m_type;
		String			m_fileName;
	};


	class TextResource : public Resource
	{
	public:
		TextResource();
		TextResource(const TextResource& t);
		virtual ~TextResource() override;

		virtual ERROR_ID load()		override;
		virtual ERROR_ID unload()	override;

		inline const String&	getData() { return m_data; }

	protected:
		String	m_data;
	};

	class ShaderScriptResource : public TextResource
	{
	public:
		ShaderScriptResource();
		ShaderScriptResource(const ShaderScriptResource& s);

		void	compile();		
	};
}

#endif // !BS_RESOURCE_H
