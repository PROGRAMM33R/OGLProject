#pragma once

#include "Std.hpp"
#include "stb_image.hpp"
#include "Mesh.hpp"

class Shader;
class Boids;
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
	Model(const Model& model) 
	: 
		textures_loaded(model.textures_loaded),
		meshes(model.meshes),
		directory(model.directory),
		gammaCorrection(model.gammaCorrection)
	{}
	~Model() {}
	void Draw(Shader *shader, Boids *boids = NULL);

private:
	void loadModel(string const &path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
	GLuint loadTexture(const char *name, const string &directory, bool gamma);

};
