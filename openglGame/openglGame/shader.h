#pragma once


class Shader
{
	public:
	Shader(const char* vertexShaderDir, const char* fragmentShaderDir);
	~Shader();
	void use() const;

	private:
	unsigned int ID;
};

