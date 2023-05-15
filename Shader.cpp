#define _CRT_SECURE_NO_WARNINGS

#include "Shader.h"

#include "glad.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <gtc/type_ptr.hpp>

#include "Camera.h"
#include "Camera.h"

static bool shaderCompiled(unsigned int shader)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	return success;
}

Shader::Shader(const char* fragment_path, const char* vertex_path)
{
	std::ifstream fStream(fragment_path);
	std::ifstream vStream(vertex_path);
	std::stringstream vss;
	std::stringstream fss;
	vss << vStream.rdbuf();
	fss << fStream.rdbuf();
	m_fSource = fss.str();
	m_vSource = vss.str();


	const char* fragmentShaderSource = m_fSource.c_str();
	const char* vertexShaderSource = m_vSource.c_str();

	const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	if (!shaderCompiled(vertexShader))
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(vertexShader, 1024, &log_length, message);

		std::cout << "Vertex shader failed to compile: " << message << std::endl;
		return;
	}

	const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	if (!shaderCompiled(fragmentShader))
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(fragmentShader, 1024, &log_length, message);
		std::cout << "Fragment shader failed to compile: " << message << std::endl;
		return;
	}

	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::bind() const
{
	glUseProgram(m_id);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	const int loc = glGetUniformLocation(m_id, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setVec3(const std::string& name, const glm::vec3& vec) const
{
	const int loc = glGetUniformLocation(m_id, name.c_str());
	glUniform3fv(loc, 1, glm::value_ptr(vec));
}
