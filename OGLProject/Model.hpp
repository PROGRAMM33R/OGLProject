#pragma once

#include "Std.hpp"
#include "stb_image.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

class Model {

public:
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;

	Model(string const &path, bool gamma = false) : gammaCorrection(gamma)
	{
		loadModel(path);
	}
	~Model() {}
	void Draw(GLuint ID);

private:
	void loadModel(string const &path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
	GLuint loadTexture(const char *name, const string &directory, bool gamma);

};
