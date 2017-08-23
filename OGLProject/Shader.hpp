#pragma once

class Shader {

private:
public:
	Shader() {}
	~Shader() {}
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path) const;

};