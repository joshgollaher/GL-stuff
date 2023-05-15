#pragma once
#include <fwd.hpp>
#include <string>

class Shader
{
private:

	unsigned int m_id;
	std::string m_fSource;
	std::string m_vSource;

public:

	Shader() = default;
	Shader(const char* fragment_path, const char* vertex_path);

	void bind() const;
	void unbind();

	void setFloat(const std::string& name, float value) const;
	void setInt(const std::string& name, int value) const;
	void setBool(const std::string& name, bool value) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
	void setVec3(const std::string& name, const glm::vec3& vec) const;
};

