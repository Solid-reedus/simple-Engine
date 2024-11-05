#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> p_vertices, std::vector<unsigned int> p_indices, std::vector<Texture> p_textures)
{
	vertices = p_vertices;
	indices = p_indices;
	textures = p_textures;
}
