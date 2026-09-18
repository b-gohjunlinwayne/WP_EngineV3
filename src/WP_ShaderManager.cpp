#include <WP_ShaderManager.h>
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <string>
#include <WP_Logger.h>

WP_ShaderManager& WP_ShaderManager::GetInstance()
{
	static WP_ShaderManager instance;
	return instance;
}

void WP_ShaderManager::LoadShader(const
	const std::string& _shaderName,
	const std::string& _vertexPath,
	const std::string& _fragmentPath)
{
	WP_Logger() << "LOADING::SHADER : " << _shaderName;

	unsigned int newShaderProgramID = glCreateProgram();
	WP_Shader newShaderProgram = WP_Shader(newShaderProgramID);

	{
		std::ifstream file(_vertexPath);
		if (!file.is_open())
		{
			WP_Logger(WP_LogLevel::Error) <<
				"Vertex Path Invalid:" << _shaderName;
			WP_Logger(WP_LogLevel::Error) << 
				"Path : " << _vertexPath;
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

		glAttachShader(newShaderProgram.p_shaderProgramID, vertexShader);
	}

	{
		std::ifstream file(_fragmentPath);
		if (!file.is_open())
		{
			WP_Logger(WP_LogLevel::Error)  << "Fragment Path Invalid:" << _shaderName;
			WP_Logger(WP_LogLevel::Error)  << "Path : " + _fragmentPath;
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

		glAttachShader(newShaderProgram.p_shaderProgramID, fragmentShader);
	}

	glLinkProgram(newShaderProgram.p_shaderProgramID);
	glUseProgram(newShaderProgram.p_shaderProgramID);

	//add new shader program to dictionary
	m_shaderDictionary.emplace(_shaderName, newShaderProgram);
}

std::optional<WP_Shader> WP_ShaderManager::GetShader(const std::string& _shaderName) const
{
	auto searchResult = m_shaderDictionary.find(_shaderName);
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
		glDeleteProgram(i.second.p_shaderProgramID);
	}
}