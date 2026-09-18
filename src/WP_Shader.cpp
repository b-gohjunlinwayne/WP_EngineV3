#include <WP_Shader.h>
#include <GL/glew.h>

WP_Shader::WP_Shader(unsigned int _shaderProgramID)
{
	p_shaderProgramID = _shaderProgramID;
}

WP_Shader::~WP_Shader()
{
	glDeleteProgram(p_shaderProgramID);
}

void WP_Shader::Use() const
{
	glUseProgram(p_shaderProgramID);
}