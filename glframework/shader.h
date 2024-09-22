#pragma once

#include "core.h"

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void begin();	//��ʼʹ�õ�ǰ��Shader
	void end();	//����ʹ�õ�ǰ��Shader

	void setFloat(const std::string& name, float value);
	void setVector3(const std::string& name, float x, float y, float z);
	void setVector3(const std::string& name, const float* values);
	void setInt(const std::string& name, int value);

private:
	GLuint mProgram{ 0 };
	void checkShaderErrors(GLuint target, std::string type);
};
