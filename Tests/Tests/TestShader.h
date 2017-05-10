#ifndef TESTSHADER_H
#define TESTSHADER_H

#include <Rendering/bs_ShaderScript.h>

class TestShader : public bs::ShaderScript
{
public:
	TestShader();
	~TestShader();

	static	TestShader instance;

	void	initialize();
};

#endif // !TESTSHADER_H
