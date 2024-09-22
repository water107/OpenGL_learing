#pragma once

#include "core.h"

class Texture {
public:
	Texture(const std::string& picPath, unsigned int unit);
	~Texture();

	void bind();

private:
	GLuint mTexture{ 0 };
	int mWidth{ 0 };
	int mHeight{ 0 };
	int mChannels{ 0 };
	unsigned int mUnit{ 0 };	//ÎÆÀíµ¥Ôª
};
