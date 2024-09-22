#include "shader.h"
#include "core.h"
#include "../wrapper/checkError.h"
#include <fstream>
#include <sstream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure & e) {
		std::cout << "Error:Shader File Error" << e.what() << std::endl;
	}	//��ȡ�ļ�������
	
    GLuint vertex, fragment;
    const char* vertexShaderSource = vertexCode.c_str();
    const char* framentShaderSource = fragmentCode.c_str();
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);  //����Shader����

    glShaderSource(vertex, 1, &vertexShaderSource, NULL);			// ��������ɫ�������ݴ�����
    // �� glShaderSource ������
    //	�� ��һ��������Ҫ�������ɫ������GLuint shader
    //	�� �ڶ���������ָ�����ݵ�Դ���ַ�������������ֻ��һ����, GLsizei count
    //	�� ������������������ɫ��������Դ�롣���Ǵ�����ǵ�ַ��, const GLchar *const*string
    //	�� ���ĸ�������������ʱ����ʼλ��, const GLint *length
    glShaderSource(fragment, 1, &framentShaderSource, NULL);

    glCompileShader(vertex);
    checkShaderErrors(vertex, "Compile");
    glCompileShader(fragment);
    checkShaderErrors(fragment, "Compile");

    mProgram = glCreateProgram();    /* ������ɫ������ */
    glAttachShader(mProgram, vertex);    //�� glAttachShader ��֮ǰ����� ������ɫ�� ���ӵ����������
    glAttachShader(mProgram, fragment);
    glLinkProgram(mProgram); // ����� glLinkProgram ����
    checkShaderErrors(mProgram, "Link");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


Shader::~Shader() {

};

void Shader::begin() {
	GL_CALL(glUseProgram(mProgram));
}	//��ʼʹ�õ�ǰ��Shader

void Shader::end() {
	GL_CALL(glUseProgram(0));
}
//����ʹ�õ�ǰ��Shader

void Shader::setFloat(const std::string& name, float value) {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str())); //ͨ�������õ�Uniform������λ��location
    GL_CALL(glUniform1f(location, value));
}

void Shader::setVector3(const std::string& name, float x, float y, float z) {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str())); //ͨ�������õ�Uniform������λ��location
    GL_CALL(glUniform3f(location, x, y, z));
}

void Shader::setVector3(const std::string& name, const float* values) {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str())); //ͨ�������õ�Uniform������λ��location
    GL_CALL(glUniform3fv(location, 1, values));    //��ǰҪ���µ�Uniform�����������ٸ�vec3
}

void Shader::setInt(const std::string& name, int value) {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str())); //ͨ�������õ�Uniform������λ��location
    GL_CALL(glUniform1i(location, value));
}



void Shader::checkShaderErrors(GLuint target, std::string type){
    int success = 0;
    char infoLog[1024];
    if (type == "Compile") {
        glGetShaderiv(target, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(target, 1024, NULL, infoLog);
            std::cout << "Error:shader compile error" << "\n" << infoLog << std::endl;
        }
    }
    else if (type == "Link") {
        glGetProgramiv(target, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(target, 1024, NULL, infoLog);
            std::cout << "Error:shader link error --program" << "\n" << infoLog << std::endl;
        }
    }
    else {
        std::cout << "checkShaderErrors: type error" << std::endl;
    }
}
    