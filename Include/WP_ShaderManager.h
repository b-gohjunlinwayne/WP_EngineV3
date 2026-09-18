#pragma once
#include <unordered_map>
#include <WP_Shader.h>
#include <string>
#include <optional>
class WP_ShaderManager
{
	std::unordered_map<std::string, WP_Shader> m_shaderDictionary;

public:

	static WP_ShaderManager& GetInstance();

	void LoadShader(const std::string& shaderName, 
		const std::string& vertexPath, 
		const std::string& fragmentPath);
	std::optional<WP_Shader> GetShader(const std::string& shaderName) const;
	void CleanUp();
};