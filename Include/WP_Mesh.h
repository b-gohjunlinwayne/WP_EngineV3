#include <vector>
#include <WP_Math.h>
#include <WP_GraphicsDefine.h>
#include <WP_Logger.h>



struct WP_Mesh
{
	std::vector<WP_Vec3f> p_vertices;
	std::vector<WP_Index> p_indices;

	GLuint p_VAO;
	GLuint p_VBO;
	GLuint p_EBO;

	WP_Mesh()
		: 
		p_VAO(0),
		p_VBO(0),
		p_EBO(0)
	{
	}
	WP_Mesh(WP_Mesh&& other) noexcept
		: 
		p_vertices(std::move(other.p_vertices)),
		p_indices(std::move(other.p_indices)),
		p_VAO(other.p_VAO),
		p_VBO(other.p_VBO),
		p_EBO(other.p_EBO)
	{
		other.p_VAO = 0;
		other.p_VBO = 0;
		other.p_EBO = 0;
	}
	~WP_Mesh()
	{
		glDeleteVertexArrays(1, &p_VAO);
		glDeleteBuffers(1, &p_VBO);
		glDeleteBuffers(1, &p_EBO);
	}
	WP_Mesh(const WP_Mesh&) = delete;
	WP_Mesh& operator=(const WP_Mesh&) = delete;
};

class WP_MeshManager
{
	std::vector<WP_Mesh> m_meshList;
	std::map<std::string, size_t> m_meshDictionary;


public:
	unsigned int VAO;
	unsigned int VBO;


	static WP_MeshManager& GetInstance()
	{
		static WP_MeshManager instance;
		return instance;
	}

	void LoadMesh()
	{
		//for now just do a test mesh, later will load from file
		WP_Vec3f triangle[] =
		{
			WP_Vec3f(-0.5,-0.5,0),
			WP_Vec3f(0.5,-0.5,0),
			WP_Vec3f(0,0.5f,0)
		};

		std::vector<WP_Index> indices = { 0, 1, 2 };

		WP_Mesh newMesh;
		newMesh.p_vertices.assign(std::begin(triangle), std::end(triangle));
		newMesh.p_indices.assign(std::begin(indices), std::end(indices));

		glGenVertexArrays(1, &newMesh.p_VAO);
		glBindVertexArray(newMesh.p_VAO);
		glGenBuffers(1, &newMesh.p_VBO);

		glBindBuffer(GL_ARRAY_BUFFER, newMesh.p_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//Add new mesh program to dictionary and list
		m_meshDictionary.emplace("testMesh", m_meshList.size());
		m_meshList.emplace_back(std::move(newMesh));
	}
	
	std::optional<WP_MeshID> GetMeshID(const std::string& _meshName) const
	{
		auto searchResult = m_meshDictionary.find(_meshName);
		if (searchResult != m_meshDictionary.end())
		{
			return searchResult->second;
		}
		return std::nullopt;
	}
	const WP_Mesh& GetMesh(WP_MeshID _meshID) const
	{
		return m_meshList[_meshID];
	}

	void CleanUp()
	{
		m_meshDictionary.clear();
		m_meshList.clear();
	}
};
