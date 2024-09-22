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
	}	//读取文件正常吗？
	
    GLuint vertex, fragment;
    const char* vertexShaderSource = vertexCode.c_str();
    const char* framentShaderSource = fragmentCode.c_str();
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);  //创建Shader程序

    glShaderSource(vertex, 1, &vertexShaderSource, NULL);			// 将顶点着色器的内容传进来
    // ● glShaderSource 函数：
    //	▼ 第一个参数：要编译的着色器对象。GLuint shader
    //	▼ 第二个参数：指定传递的源码字符串数量，这里只有一个。, GLsizei count
    //	▼ 第三个参数：顶点着色器真正的源码。我们传入的是地址。, const GLchar *const*string
    //	▼ 第四个参数：读数据时的起始位。, const GLint *length
    glShaderSource(fragment, 1, &framentShaderSource, NULL);

    glCompileShader(vertex);
    checkShaderErrors(vertex, "Compile");
    glCompileShader(fragment);
    checkShaderErrors(fragment, "Compile");

    mProgram = glCreateProgram();    /* 创建着色器程序 */
    glAttachShader(mProgram, vertex);    //用 glAttachShader 把之前编译的 顶点着色器 附加到程序对象上
    glAttachShader(mProgram, fragment);
    glLinkProgram(mProgram); // 最后用 glLinkProgram 链接
    checkShaderErrors(mProgram, "Link");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


Shader::~Shader() {

};

void Shader::begin() {
	GL_CALL(glUseProgram(mProgram));
}	//开始使用当前的Shader

void Shader::end() {
	GL_CALL(glUseProgram(0));
}
//结束使用当前的Shader

void Shader::setFloat(const std::string& name, float value) {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str())); //通过名称拿到Uniform变量的位置location
    GL_CALL(glUniform1f(location, value));
}

void Shader::setVector3(const std::string& name, float x, float y, float z) {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str())); //通过名称拿到Uniform变量的位置location
    GL_CALL(glUniform3f(location, x, y, z));
}

void Shader::setVector3(const std::string& name, const float* values) {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str())); //通过名称拿到Uniform变量的位置location
    GL_CALL(glUniform3fv(location, 1, values));    //当前要更新的Uniform变量包括多少个vec3
}

void Shader::setInt(const std::string& name, int value) {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str())); //通过名称拿到Uniform变量的位置location
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
    