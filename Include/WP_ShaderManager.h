#pragma once
#include <map>
#include <WP_Shader.h>
#include <string>
#include <optional>
#include <vector>

using WP_ShaderID = size_t;

class WP_ShaderManager
{
	//used for searching by name
	std::map<std::string, WP_ShaderID> m_shaderDictionary;
	//used for id access for faster if already have id
	std::vector<WP_Shader> m_shaderIDToShaderList;

public:

	static WP_ShaderManager& GetInstance();

	void LoadShader(const std::string& _shaderName, 
		const std::string& _vertexPath, 
		const std::string& _fragmentPath);

	//get shader ID
	std::optional<WP_ShaderID> GetShaderID(const std::string& _shaderName) const;
	const WP_Shader& GetShader(WP_ShaderID _shaderProgramID) const;
	void CleanUp();
};