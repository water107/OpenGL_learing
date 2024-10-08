#pragma once

#include "core.h"

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void begin();	//开始使用当前的Shader
	void end();	//结束使用当前的Shader

	void setFloat(const std::string& name, float value);
	void setVector3(const std::string& name, float x, float y, float z);
	void setVector3(const std::string& name, const float* values);
	void setInt(const std::string& name, int value);

private:
	GLuint mProgram{ 0 };
	void checkShaderErrors(GLuint target, std::string type);
};
