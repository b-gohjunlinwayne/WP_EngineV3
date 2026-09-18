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
	static std::optional<WP_Shader> GetShader(const std::string& _shaderName);

	//Cleanup
	static void Cleanup();
};