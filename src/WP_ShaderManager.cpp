#include <WP_ShaderManager.h>
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <string>
#include <WP_Logger.h>

void WP_ShaderManager::LoadShader(const
	const std::string& shaderName,
	const std::string& vertexPath,
	const std::string& fragmentPath)
{
	WP_Logger() << "LOADING::SHADER : " << shaderName;

	unsigned int newShaderProgramID = glCreateProgram();
	WP_Shader newShaderProgram = WP_Shader(newShaderProgramID);

	{
		std::ifstream file(vertexPath);
		if (!file.is_open())
		{
			WP_Logger(WP_LogLevel::Error) <<
				"Vertex Path Invalid:" << shaderName;
			WP_Logger(WP_LogLevel::Error) << 
				"Path : " << vertexPath;
		}

		std::string shaderSource;

		std::string fileLine;
		// Read each line from the file
		while (std::getline(file, fileLine))
			shaderSource += fileLine + "\n";

		// Close the file
		file.close();

		const char* shaderVertSourceCstr = shaderSource.c_str();

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &shaderVertSourceCstr, NULL);
		glCompileShader(vertexShader);

		int  success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			WP_Logger(WP_LogLevel::Error) << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
				<< infoLog;
		}

		glAttachShader(newShaderProgram.shaderProgramID, vertexShader);
	}

	{
		std::ifstream file(fragmentPath);
		if (!file.is_open())
		{
			WP_Logger(WP_LogLevel::Error)  << "Fragment Path Invalid:" << shaderName;
			WP_Logger(WP_LogLevel::Error)  << "Path : " + fragmentPath;
		}

		std::string shaderSource;

		std::string fileLine;
		// Read each line from the file
		while (std::getline(file, fileLine))
			shaderSource += fileLine + "\n";

		// Close the file
		file.close();

		const char* shaderFragSourceCstr = shaderSource.c_str();

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &shaderFragSourceCstr, NULL);
		glCompileShader(fragmentShader);

		int  success;
		char infoLog[512];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			 WP_Logger(WP_LogLevel::Error) << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
				<< infoLog;
		}

		glAttachShader(newShaderProgram.shaderProgramID, fragmentShader);
	}

	glLinkProgram(newShaderProgram.shaderProgramID);
	glUseProgram(newShaderProgram.shaderProgramID);

	//add new shader program to dictionary
	m_shaderDictionary.emplace(shaderName, newShaderProgram);
}

std::optional<WP_Shader> WP_ShaderManager::GetShader(const std::string& shaderName) const
{
	auto searchResult = m_shaderDictionary.find(shaderName);
	if (searchResult != m_shaderDictionary.end())
	{
		return searchResult->second;
	}
	return std::nullopt;
}

void WP_ShaderManager::CleanUp()
{
	for (auto i : m_shaderDictionary)
	{
		glDeleteProgram(i.second.shaderProgramID);
	}
}