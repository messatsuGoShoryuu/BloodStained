#ifndef _BS_SPRITE_H_
#define _BS_SPRITE_H_

#include <Math/bs_Vector.h>
#include <Math/bs_Rect.h>
#include "bs_Color.h"
namespace bs
{
	class Texture2D;
	class Shader;
	

	class Sprite
	{
	public:
		Sprite();
		Sprite(const Texture2D* texture, const  Shader* shader);
		Sprite(const Sprite& s);
		~Sprite();

		inline	void				setOrientation(f32 orientation)			{ m_orientation = orientation; }
		inline	f32					orientation() const						{ return m_orientation; }

		inline	void				setPosition(const Vector2& position)	{ m_position = position; }
		inline	void				setPosition(f32 x, f32 y)				{ m_position = Vector2(x, y); }
		inline	const Vector2&		position()	const						{ return m_position; }

		inline	void				setScale(const Vector2& scale)			{ m_scale = scale; }
		inline	void				setScale(f32 x, f32 y)					{ m_scale = Vector2(x, y); }
		inline	const Vector2&		scale()		const						{ return m_scale; }

		inline	void				setTexture(Texture2D* texture)			{ m_texture = texture; }
		inline	const Texture2D*	texture()	const						{ return m_texture; }

		inline	void				setShader(Shader* shader)				{ m_shader = shader; }
		inline const Shader*		shader()	const						{ return m_shader; }

		inline const ColorRGBAf&	color()		const						{ return m_color; }
		inline void					setColor(const ColorRGBAf& color)		{ m_color = color; }
		
		inline const Rectf32&		uvRect()	const						{ return m_uvRect; }
		inline void					setUvRect(const Rectf32& rect)			{ m_uvRect = rect; }

	private:
		const	Texture2D*	m_texture;
		const	Shader*		m_shader;

		ColorRGBAf	m_color;
		Vector2 m_position;
		Vector2 m_scale;
		f32		m_orientation;
		Rectf32 m_uvRect;
	};
}

#endif // !_BS_SPRITE_H_