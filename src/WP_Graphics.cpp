#include <WP_Graphics.h>
#include <iostream>
#include <WP_Logger.h>

bool WP_Graphics::s_glewInit = false;

void WP_Graphics::InitialiseGLFW()
{
	if (!glfwInit())
	{
		throw std::runtime_error("GLFWInit failed");
	}
}

void WP_Graphics::InitialiseGlew()
{
	s_glewInit = true;
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		std::string errorMsg = "GLEW init failed: " +
			std::string(reinterpret_cast<const char*>(glewGetErrorString(err)));

		throw std::runtime_error(errorMsg);
	}

	WP_Logger() << "GLEW initialized successfully!\n";
	WP_Logger() << "GLEW version: "
		<< glewGetString(GLEW_VERSION) << '\n';

}

void WP_Graphics::LoadShader(const std::string& _shaderName,
	const std::string& _vertexPath, const std::string& _fragmentPath)
{
	WP_ShaderManager::GetInstance().LoadShader(_shaderName, _vertexPath, _fragmentPath);
}

std::optional<WP_ShaderID> WP_Graphics::GetShaderID(const std::string& _shaderName)
{
	return WP_ShaderManager::GetInstance().GetShaderID(_shaderName);
}
const WP_Shader& WP_Graphics::GetShader(const WP_ShaderID _shaderID)
{
	return WP_ShaderManager::GetInstance().GetShader(_shaderID);
}

void WP_Graphics::LoadMesh()
{
	WP_MeshManager::GetInstance().LoadMesh();
}

std::optional<WP_MeshID> WP_Graphics::GetMeshID(const std::string& _meshName)
{
	return WP_MeshManager::GetInstance().GetMeshID(_meshName);
}
const WP_Mesh& WP_Graphics::GetMesh(const WP_MeshID _meshID)
{
	return WP_MeshManager::GetInstance().GetMesh(_meshID);
}

bool WP_Graphics::GetIsGlewInit()
{
	return s_glewInit;
}

void WP_Graphics::Cleanup()
{
	WP_ShaderManager::GetInstance().CleanUp();
	WP_MeshManager::GetInstance().CleanUp();
	glfwTerminate();
}