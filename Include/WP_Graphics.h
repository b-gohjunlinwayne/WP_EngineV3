#pragma once
#include <WP_ShaderManager.h>
class WP_Graphics
{
private:
	static bool s_glewInit;
	static WP_ShaderManager s_shaderManager;

public:

	//GLFW
	static void InitialiseGLFW();

	//Glew
	static void InitialiseGlew();
	static bool GetIsGlewInit();

	//shader Manager
	static void LoadShader(const std::string& shaderName,
		const std::string& vertexPath, const std::string& fragmentPath);
	static std::optional<WP_Shader> GetShader(const std::string& shaderName);

	//Cleanup
	static void Cleanup();
};