#include "TestShader.h"
#include <Globals\bs_globals.h>
#include <Rendering\bs_Shader.h>

TestShader::TestShader()
	:bs::ShaderScript()
{

}

TestShader::~TestShader()
{

}

void	TestShader::initialize()
{
	name = "TestShader";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	bs::String vertexSourceString = bs::g_resourceManager.loadText("Shaders/TestVertex.txt");
	bs::String fragmentSourceString = bs::g_resourceManager.loadText("Shaders/TestFragment.txt");

	const char* vertexSource = vertexSourceString.utf8();
	const char* fragmentSource = fragmentSourceString.utf8();

	GLint	vertexSourceLength = vertexSourceString.length();
	GLint	fragmentSourceLength = fragmentSourceString.length();

	glShaderSource(vertexShader, 1, &vertexSource, &vertexSourceLength);
	glShaderSource(fragmentShader, 1, &fragmentSource, &fragmentSourceLength);

	glCompileShader(vertexShader);

	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
	}


	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
	}

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindFragDataLocation(shaderProgram, 0, "outColor");

	glLinkProgram(shaderProgram);
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	//Get shader
	bs::g_shaderManager.getShaderMap()[name] = bs::Shader(name, shaderProgram);
	bs::Shader* s = &bs::g_shaderManager.getShaderMap()[name];

	s->addUniform("view", bs::UNIFORM_TYPE::MATRIX4);
	s->addUniform("projection", bs::UNIFORM_TYPE::MATRIX4);
	s->addUniform("model", bs::UNIFORM_TYPE::MATRIX4);
	s->addUniform("ratio", bs::UNIFORM_TYPE::FLOAT);
	s->addUniform("height", bs::UNIFORM_TYPE::FLOAT);
}