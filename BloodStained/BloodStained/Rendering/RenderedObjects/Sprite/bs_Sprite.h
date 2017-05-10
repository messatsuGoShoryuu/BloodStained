#ifndef BS_SPRITE_H
#define	BS_SPRITE_H

#include "../../../Math/bs_Matrix4x4.h"
#include "../../../Math/bs_Rect.h"
#include "../../bs_Vertex.h"
#include "../../bs_Color.h"
#include "../../bs_Texture2D.h"

namespace bs
{
	class Shader;

	class Sprite
	{
	public:

		friend class SpriteRenderer;
		//Default constructor.
		Sprite();

		//Copy constructor.
		Sprite(const Sprite& s);

		//Destructor.
		~Sprite();

		
		//Setters & getters
		inline			void		setPosition(const Vector2& position)			{ m_position = position; setDirty(); }
		inline			void		setPosition(real x, real y)						{ m_position.x = x; m_position.y = y; setDirty(); }
		inline	const	Vector2&	position()								const	{ return m_position; }

		inline			void		setOrientation(real orientation)				{ m_orientation = orientation; setDirty(); }
		inline			real		orientation()									{ return m_orientation; }

		inline			void		setColor(const ColorRGBA32 color)				{ m_color = color; setDirty(); }
		inline			void		setColor(ui8 r, ui8 g, ui8 b, ui8 a)
		{
			m_color.r = r;
			m_color.g = g;
			m_color.b = b;
			m_color.a = a;
		}
		inline	const	ColorRGBA32&	color()								const	{ return m_color; }

		inline			void		setWidth(real width)							{ m_width = width; setDirty(); }
		inline			real		width()									const	{ return m_width; }

		inline			void		setHeight(real height)							{ m_height = height; setDirty(); }
		inline			real		height()								const	{ return m_height; }

		inline			void		setDepth(real depth)							{ m_depth = depth; setDirty(); }
		inline			real		depth()									const	{ return m_depth; }

		inline			void		setTexture(const Texture2D& texture)			{ m_texture = texture; setDirty(); }
		inline	const	Texture2D&	texture()								const	{ return m_texture; }

		inline			void		setNormalMap(const Texture2D& texture)			{ m_normalMap = texture; setDirty(); }
		inline	const	Texture2D&  normalMap()								const	{ return m_normalMap; }

		inline			void		setUvRect(const Rectf32& rect)					{ m_uvRect = rect; setDirty(); }
		inline  const	Rectf32&	uvRect()								const	{ return m_uvRect; }

		inline			void		setParallaxFactor(f32 factor)					{ m_parallaxFactor = factor; setDirty(); }
		inline			f32			parallaxFactor()						const	{ return m_parallaxFactor; }

		inline			void		setParallaxOffset(const Vector2& offset)		{ m_parallaxOffset = offset; setDirty(); }
		inline			void		setParallaxOffset(real x, real y)				{ m_parallaxOffset.x = x, m_parallaxOffset.y = y; setDirty(); }
		inline	const	Vector2&	parallaxOffset()						const	{ return m_parallaxOffset; }

		inline			Vertex2D_PUC* vertices()									{ return m_vertices; }

		inline			void		setShader(Shader* shader)						{ m_shader = shader; setDirty(); }
		inline	const	Shader*		shader()								const	{ return m_shader; }

		inline			void		setDirty()										{ m_isDirty = true; }
		inline			bool		isDirty()										{ return m_isDirty; }
	private:
		void	_setupVertices();
		inline void					_setDirty(bool value)							{ m_isDirty = value; }

	private:
		//Get this from parent's transform.
		Vector2		m_position;
		real		m_orientation;

		//Clip rect (in case of animation)
		Rectf32		m_uvRect;

		//Color
		ColorRGBA32	m_color;

		//Vertices
		Vertex2D_PUC	m_vertices[4];

		//Metrics in world coordinates
		real			m_width;
		real			m_height;
		real			m_depth;

		//Main texture
		Texture2D	m_texture;

		//Normal map
		Texture2D	m_normalMap;

		bool		m_useParallax;

		//Parallax coefficient (multiply the position displacement by this in the shader to get parallaxed value)
		f32			m_parallaxFactor;

		Vector2	m_parallaxOffset;

		Shader*	m_shader;

		bool m_isDirty;
	};
}
#endif // !BS_SPRITE_H
