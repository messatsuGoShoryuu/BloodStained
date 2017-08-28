#include "bs_Texture2D.h"



namespace bs
{
	Texture2D::Texture2D()
		:m_id(0)
	{

	}

	Texture2D::Texture2D(const Texture2D& t)
		: m_id(t.m_id)
	{

	}

	Texture2D::~Texture2D()
	{

	}

}