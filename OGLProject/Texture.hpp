#pragma once

class Texture {

private:
	void rotate90(unsigned char *buffer, int width, int height);

public:
	Texture() {}
	~Texture() {}
	GLuint load(const char *name);
	GLuint loadDDS(const char * imagepath);

};