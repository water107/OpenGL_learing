#include "glframework/core.h"
#include "wrapper/checkError.h"
#include "application/Application.h"
#include "glframework/shader.h"
#include "glframework/texture.h"

GLuint vao = 0;
Shader* shader = nullptr;
Texture* noise_texture = nullptr;
Texture* grass_texture = nullptr;
Texture* land_texture = nullptr;

void OnKey(int key,        //��ĸ������
    int action,     //���»���̧�� 1���� 0̧��
    int mods        //�Ƿ���shift ctrl
    ) {
    
    std::cout << "key=" << key << "\n";
    std::cout << "action=" << action << std::endl;
    std::cout << "mods=" << mods << std::endl;
}

void OnResize(int width, int height) {
    GL_CALL(glViewport(0, 0, width, height));
    std::cout << "���´���Ĵ�СΪ:(�����)" << width << "*" << height << std::endl;
}

void OnMouseButton(int button, int action, int mods) {
    std::cout << "���" << button << "��" << std::endl;
    std::cout << "action=" << action << std::endl;
    std::cout << "mods=" << mods << std::endl;
}

//void prepareVBO_gen() {
//    GLuint vbo = 0;
//    GL_CALL(glGenBuffers(1, &vbo));
//    GLuint vboArr[] = { 0, 0, 0 };
//    GL_CALL(glGenBuffers(3, vboArr));
//    //n�� �������ٸ�vbo
//    //buffers: ����������vbo����� ������������ŵ�bufferָ���������
//    // ����n��VBO����û�з����Դ�
//
//    GL_CALL(glDeleteBuffers(1, &vbo));
//    GL_CALL(glDeleteBuffers(3, vboArr));
//    // ����
//
//}
//void prepareVBO_bind() {
//    float vertices[] = {
//    -0.5f, -0.5f, 0.0f,
//    0.5f, -0.5f, 0.0f,
//    0.0f, 0.5f, 0.0f
//    };
//    GLuint vbo = 0;
//    GL_CALL(glGenBuffers(1, &vbo));
//
//    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
//    // GL_ARRAY_BUFFER��ʾ��ǰvbo������
//    // target: �ѵ�ǰ��vbo�󶨵�״̬�����ĸ�״̬���
//    // buffer �󶨵�vbo��ţ�0��ʾ�����κ�buffer
//
//    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
//    //�����Դ�
//    //target: ���״̬�����ĸ�״̬��۵�buffer
//    //size: װ�뵱ǰbuffer�����ݴ�С
//    //data��װ�����ݵ�����ָ��
//    //usage ��ǰbuffer���÷�
//}

void prepareVaoForTri() {
    float positions[] = {
        -0.7f, -0.7f, 0.0f,
        0.7f, -0.7f, 0.0f,
        -0.7f, 0.7f, 0.0f,
        0.7f, 0.7f, 0.0f
    };
    float colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.5f, 0.2f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        3, 2, 1
    };
    float uvs[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f
    };

    GLuint posVbo, colVbo, uvVbo= 0;
    GL_CALL(glGenBuffers(1, &posVbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
    GL_CALL(glGenBuffers(1, &colVbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));
    GL_CALL(glGenBuffers(1, &uvVbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, uvVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW));

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GL_CALL(glGenVertexArrays(1, &vao));
    GL_CALL(glBindVertexArray(vao));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));  //��posVbo�����������õ����������buffer�й�
    GL_CALL(glEnableVertexAttribArray(0));   //λ�����Է���vao���Ե�0��λ�ã�Ҫ�ȼ���
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
     //GLuint index, λ�����ԣ���0��λ��
     //GLint size, һ������3������
     //GLenum type, float����
     //GLboolean normalized, �Ƿ��һ�� 
     //GLsizei stride, ÿ������֮��Ŀ��
     //const void *pointer ���������ڲ�ƫ��

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colVbo));  //��colVbo�����������õ����������buffer�й�
    GL_CALL(glEnableVertexAttribArray(1));   //��ɫ���Է���vao���Ե�1��λ�ã�Ҫ�ȼ���
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, uvVbo));  //��uvVbo�����������õ����������buffer�й�
    GL_CALL(glEnableVertexAttribArray(2));   //��ͼ���Է���vao���Ե�2��λ�ã�Ҫ�ȼ���
    GL_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    GL_CALL(glBindVertexArray(0));
}

//void prepareInter() {
//    float vertices[] = {
//        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
//        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
//        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
//    };
//    GLuint vbo = 0;
//    GL_CALL(glGenBuffers(1, &vbo));
//    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
//    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
//
//    GLuint vao = 0;
//    GL_CALL(glGenVertexArrays(1, &vao));
//    GL_CALL(glBindVertexArray(vao));
//    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));  //��posVbo�����������õ����������buffer�й�
//    GL_CALL(glEnableVertexAttribArray(0));   //λ�����Է���vao���Ե�0��λ�ã�Ҫ�ȼ���
//    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0));
//    // GLuint index, λ�����ԣ���0��λ��
//    // GLint size, һ������3������
//    // GLenum type, float����
//    // GLboolean normalized, �Ƿ��һ�� 
//    // GLsizei stride, ÿ������֮��Ŀ��
//    // const void *pointer ���������ڲ�ƫ��
//    GL_CALL(glEnableVertexAttribArray(1));   //λ�����Է���vao���Ե�0��λ�ã�Ҫ�ȼ���
//    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(3*sizeof(float))));
//    GL_CALL(glBindVertexArray(0));
//}
void prepareShader() {
    shader = new Shader("./assets/shaders/vertex.glsl", "./assets/shaders/fragment.glsl");
}

void prepareTexture() {
    grass_texture = new Texture("./assets/textures/grass.jpg", 0);
    land_texture = new Texture("./assets/textures/land.jpg", 1);
    noise_texture = new Texture("./assets/textures/OIP.jpg", 2);
}

void render() {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));  //��������
    shader->begin();  // ��Ⱦ������ɫ������
    shader->setFloat("time", glfwGetTime());
    shader->setFloat("speed", 0.3);
    shader->setInt("grass_sampler", 0); 
    shader->setInt("land_sampler", 1);
    shader->setInt("noise_sampler", 2);    
    //shader->setFloat("speed", 6.0);
    //shader->setVector3("uColor", 0.3, 0.4, 0.5);
    glBindVertexArray(vao);		// �� VAO
    //glDrawArrays(GL_TRIANGLES, 0, 6);	// ��������  �ӵ�0�����㿪ʼ һ����3�� ��������������� �޷����ñ�
    //glDrawArrays(GL_LINES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // ���ʹ����ebo�� ���һ����������д0
    // ���ʹ����ebo�� �������һ�����������֣���ʾebo��ƫ����,����ֻ�ú������㻭������
    // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(int) * 3));
    // ���û��ʹ��ebo�� ����ֱ�ӽ�cpu��indices���鴫���ȥ
    glBindVertexArray(0);				// ���
    shader->end();
}

int main(int argc, char* argv) {

    if (mapp->init(800, 600) == false)
        return -1;

    mapp->setResizeCallback(OnResize);
    mapp->setKeyBoardCallback(OnKey);
    mapp->setMuseCallback(OnMouseButton);
     
    glViewport(0, 0, 800, 600);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    prepareVaoForTri();
    prepareShader();
    prepareTexture();
    
    while (mapp->updata()) {
        render();
    }

    mapp->destroy();
    return 0;
}
