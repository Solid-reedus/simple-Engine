#pragma once

#include "iostream"
#include "vector"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader;

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};


struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;

};


class Mesh
{
	public:
    std::vector<Vertex>       m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Texture>      m_textures;
    unsigned int VAO;

	Mesh(std::vector<Vertex> p_vertices, std::vector<unsigned int> p_indices, std::vector<Texture> p_textures);
    void Draw(Shader& p_shader);

	private:
    unsigned int VBO, EBO;

};

