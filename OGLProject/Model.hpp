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

	Model(string const &path, Config *cfg, bool gamma = false)
		: gammaCorrection(gamma), cfg(cfg)
	{
		loadModel(path);
	}
	Model(const Model& model) 
	: 
		textures_loaded(model.textures_loaded),
		meshes(model.meshes),
		directory(model.directory),
		gammaCorrection(model.gammaCorrection),
		cfg(model.cfg)
	{}
	~Model() {}
	void Draw(Shader *shader, int objType, Boids *boids = NULL);

private:
	Config *cfg;
	void loadModel(string const &path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
	GLuint loadTexture(const char *name, const string &directory, bool gamma);

};
