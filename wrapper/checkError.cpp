#include "checkError.h"
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include <assert.h> //����

void checkError() {
    GLenum errorCode = glGetError();
    std::string error = "";
    if (errorCode != GL_NO_ERROR)
    {
        switch (errorCode)
        {
        case GL_INVALID_ENUM: error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE: error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION: error = "INVALID_OPERATION"; break;
        case GL_OUT_OF_MEMORY: error = "OUT OF MEMORY"; break;
        default:
            error = "unkown"; break;

        }
        std::cout << error << "\n";
        assert(false);  //���ݴ����boolֵ��true���У�falseֹͣ

    }
}