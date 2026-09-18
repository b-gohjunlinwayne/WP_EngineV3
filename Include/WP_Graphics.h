#pragma once
#include <WP_ShaderManager.h>
class WP_Graphics
{
private:
	static bool s_glewInit;

public:

	//GLFW
	static void InitialiseGLFW();

	//Glew
	static void InitialiseGlew();
	static bool GetIsGlewInit();

	//shader Manager
	static void LoadShader(const std::string& _shaderName,
		const std::string& _vertexPath, const std::string& _fragmentPath);

	static std::optional<WP_ShaderID> GetShaderID(const std::string& _shaderName);
	static const WP_Shader& GetShader(const WP_ShaderID _shaderID);

	//Cleanup
	static void Cleanup();
};