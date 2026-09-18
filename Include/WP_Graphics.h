#pragma once
#include <WP_ShaderManager.h>
#include <WP_Mesh.h>
#include <WP_GraphicsDefine.h>

class WP_Graphics
{
private:
	static bool s_glewInit;

	static std::vector<WP_Mesh> s_meshList;

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

	//mesh Manager
	static void LoadMesh();
	
	static std::optional<WP_MeshID> GetMeshID(const std::string& _meshName);
	static const WP_Mesh& GetMesh(const WP_MeshID _meshID);

	//Cleanup
	static void Cleanup();
};
