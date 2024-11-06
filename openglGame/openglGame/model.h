#pragma once

#include <string>
#include <vector>
#include <mesh.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <common.h>

class Shader;
struct Camera;


class Model
{
	public:
	Model(std::string const& p_path);

	// might chnage Instance to a mat4 since it doesnt change the instace vals
	void Draw(Shader* p_shader, Camera& p_cameraRef);

	private:
	bool LoadModel(std::string const& p_path);

	void processNode(aiNode* p_node, const aiScene* p_scene);
	Mesh processMesh(aiMesh* p_mesh, const aiScene* p_scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* p_mat, aiTextureType p_type, std::string p_typeName);
	unsigned int TextureFromFile(const char* p_path, const std::string& p_directory, bool p_gamma = false);

	std::vector<Mesh> m_meshes;
	std::string m_directory;
	std::vector<Texture> m_textures_loaded;

};

