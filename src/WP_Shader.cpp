#include <WP_Shader.h>
#include <GL/glew.h>

WP_Shader::WP_Shader(unsigned int _shaderProgramID)
{
	shaderProgramID = _shaderProgramID;
}

void WP_Shader::Use() const
{
	glUseProgram(shaderProgramID);
}