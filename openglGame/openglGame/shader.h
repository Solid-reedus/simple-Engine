#pragma once

#include <string>
#include "glm/glm.hpp"
#include <glad/glad.h>

class Shader
{
	public:
	unsigned int ID;

	Shader(const char* p_vertexShaderDir, const char* p_fragmentShaderDir);
	~Shader() {};
	void use() const { glUseProgram(ID); };

	void setBool(const std::string& p_name, bool p_value) const;
	void setInt(const std::string& p_name, int p_value) const;
	void setFloat(const std::string& p_name, float p_value) const;

	void setVec3(const std::string& p_name, const glm::vec3& p_value) const;
	void setVec3(const std::string& p_name, float p_x, float p_y, float p_z) const;

	void setMat4(const std::string& p_name, const glm::mat4& p_mat) const;

	private:
};

