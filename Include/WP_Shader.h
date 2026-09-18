#pragma once
#
struct WP_Shader
{
	unsigned int shaderProgramID;

	WP_Shader(unsigned int _shaderProgramID);

	void Use() const;
};