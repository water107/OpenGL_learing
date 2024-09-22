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

void OnKey(int key,        //字母按键码
    int action,     //按下还是抬起 1按下 0抬起
    int mods        //是否有shift ctrl
    ) {
    
    std::cout << "key=" << key << "\n";
    std::cout << "action=" << action << std::endl;
    std::cout << "mods=" << mods << std::endl;
}

void OnResize(int width, int height) {
    GL_CALL(glViewport(0, 0, width, height));
    std::cout << "更新窗体的大小为:(宽×高)" << width << "*" << height << std::endl;
}

void OnMouseButton(int button, int action, int mods) {
    std::cout << "鼠标" << button << "键" << std::endl;
    std::cout << "action=" << action << std::endl;
    std::cout << "mods=" << mods << std::endl;
}

//void prepareVBO_gen() {
//    GLuint vbo = 0;
//    GL_CALL(glGenBuffers(1, &vbo));
//    GLuint vboArr[] = { 0, 0, 0 };
//    GL_CALL(glGenBuffers(3, vboArr));
//    //n： 创建多少个vbo
//    //buffers: 创建出来的vbo编号们 （句柄），都放到buffer指向的数组中
//    // 创建n个VBO，还没有分配显存
//
//    GL_CALL(glDeleteBuffers(1, &vbo));
//    GL_CALL(glDeleteBuffers(3, vboArr));
//    // 销毁
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
//    // GL_ARRAY_BUFFER表示当前vbo这个插槽
//    // target: 把当前的vbo绑定到状态机的哪个状态插槽
//    // buffer 绑定的vbo编号；0表示不绑定任何buffer
//
//    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
//    //开辟显存
//    //target: 针对状态机的哪个状态插槽的buffer
//    //size: 装入当前buffer的数据大小
//    //data：装有数据的数组指针
//    //usage 当前buffer的用法
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

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));  //绑定posVbo，接下来设置的属性与这个buffer有关
    GL_CALL(glEnableVertexAttribArray(0));   //位置属性放在vao属性的0号位置，要先激活
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
     //GLuint index, 位置属性，放0号位置
     //GLint size, 一个属性3个数字
     //GLenum type, float类型
     //GLboolean normalized, 是否归一化 
     //GLsizei stride, 每个数据之间的跨度
     //const void *pointer 顶点数据内部偏移

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colVbo));  //绑定colVbo，接下来设置的属性与这个buffer有关
    GL_CALL(glEnableVertexAttribArray(1));   //颜色属性放在vao属性的1号位置，要先激活
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, uvVbo));  //绑定uvVbo，接下来设置的属性与这个buffer有关
    GL_CALL(glEnableVertexAttribArray(2));   //贴图属性放在vao属性的2号位置，要先激活
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
//    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));  //绑定posVbo，接下来设置的属性与这个buffer有关
//    GL_CALL(glEnableVertexAttribArray(0));   //位置属性放在vao属性的0号位置，要先激活
//    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0));
//    // GLuint index, 位置属性，放0号位置
//    // GLint size, 一个属性3个数字
//    // GLenum type, float类型
//    // GLboolean normalized, 是否归一化 
//    // GLsizei stride, 每个数据之间的跨度
//    // const void *pointer 顶点数据内部偏移
//    GL_CALL(glEnableVertexAttribArray(1));   //位置属性放在vao属性的0号位置，要先激活
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
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));  //画布清理
    shader->begin();  // 渲染调用着色器程序
    shader->setFloat("time", glfwGetTime());
    shader->setFloat("speed", 0.3);
    shader->setInt("grass_sampler", 0); 
    shader->setInt("land_sampler", 1);
    shader->setInt("noise_sampler", 2);    
    //shader->setFloat("speed", 6.0);
    //shader->setVector3("uColor", 0.3, 0.4, 0.5);
    glBindVertexArray(vao);		// 绑定 VAO
    //glDrawArrays(GL_TRIANGLES, 0, 6);	// 画三角形  从第0个顶点开始 一共画3次 不足三个点则忽略 无法复用边
    //glDrawArrays(GL_LINES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // 如果使用了ebo， 最后一个参数可以写0
    // 如果使用了ebo， 假设最后一个参数是数字，表示ebo内偏移量,比如只用后三个点画三角形
    // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(int) * 3));
    // 如果没有使用ebo， 可以直接将cpu的indices数组传输进去
    glBindVertexArray(0);				// 解绑定
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
