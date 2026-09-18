#pragma once

struct WP_Shader
{
	unsigned int p_shaderProgramID;

	WP_Shader(unsigned int _shaderProgramID);
	~WP_Shader();

	void Use() const;

};