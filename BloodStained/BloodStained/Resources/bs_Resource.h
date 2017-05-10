#ifndef BS_RESOURCE_H
#define BS_RESOURCE_H

#include "../Utilities/bs_String.h"

namespace bs
{
	//Nature of our resource
	enum class RESOURCE_TYPE
	{
		NONE,
		TEXT,
		IMAGE,
		MESH,
		AUDIO,
		FONT
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
		virtual bool	load() = 0;
		//Unload interface
		virtual bool	unload() = 0;

	protected:
		//Error to be displayed on load failure
		bool	_loadError();

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

		virtual bool load()		override;
		virtual bool unload()	override;

		inline const String&	getData(){ return m_data; }

	private:
		String	m_data;
	};

	class ImageResource : public Resource
	{
	public:
		ImageResource();
		ImageResource(const ImageResource& i);
		virtual ~ImageResource() override;

		virtual bool load()		override;
		virtual bool unload()	override;

		inline void setTiled(bool value){ m_isTiled = value; }
		inline void setChannels(i32 channels){ m_channels = channels; }

		class Texture2D getData();

	private:
		ui32	m_width;
		ui32	m_height;
		ui32	m_textureId;
		bool	m_isTiled;
		i32		m_channels;
	};

	class MeshResource : public Resource
	{
	public:
		MeshResource();
		MeshResource(const MeshResource& m);
		virtual ~MeshResource() override;

		virtual bool load()		override;
		virtual bool unload()	override;

	private:
	};

	class AudioResource : public Resource
	{
	public:
		AudioResource();
		AudioResource(const AudioResource& a);
		virtual ~AudioResource()	override;

		virtual bool load()			override;
		virtual bool unload()		override;
	private:
	};

	class FontResource : public Resource
	{
	public:
		FontResource();
		FontResource(const FontResource& f);
		virtual ~FontResource()		override;

		virtual bool load()			override;
		virtual bool unload()		override;

	private:
		String	m_name;
		ui32	m_id;
	public:
		class Font*	getData();
	};
}

#endif // !BS_RESOURCE_H
