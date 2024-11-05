#pragma once

#include <string>
#include <vector>
#include <mesh.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <common.h>
class Shader;

class Model
{
	public:
	Model(std::string const& path);

	// might chnage Instance to a mat4 since it doesnt change the instace vals
	void Draw(Instance& instance, Shader* shader);
	//~Model();

	private:
	bool LoadModel(std::string const& path);

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;

};

