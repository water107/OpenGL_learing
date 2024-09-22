#include "Application.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


Application* Application::mInstance = nullptr;
Application* Application::getInstance() {
	//if mInstance已经实例化了（new）出来了，就直接返回，否则就先new再返回
	if (mInstance == nullptr){
		mInstance = new Application();
	}
	return mInstance;
}

//初始化Application的静态变量

Application::Application() {
	
}

Application::~Application() {
	
}

bool Application::init(const int& width, const int& height)
{
	mWidth = width;
	mHeight = height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  // 主版本号 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);  // 次版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 使用core模式 不是立即渲染模式

	mWindow = glfwCreateWindow(mWidth, mHeight, "test", NULL, NULL);    // 窗体对象
	if (mWindow == NULL)
		return false;
	glfwMakeContextCurrent(mWindow); // 设置当前窗口为opengl绘制舞台

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD初始化失败！" << "\n";
		return false;
	}

	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);    //设置监听
	glfwSetKeyCallback(mWindow, keyCallback);
	glfwSetMouseButtonCallback(mWindow, MouseButtonCallback);

	glfwSetWindowUserPointer(mWindow, this);	//this就是当前全局唯一的Application对象指针

	return true;
}

bool Application::updata()
{
	if(glfwWindowShouldClose(mWindow))
		return false;

	glfwPollEvents();   // 接受窗口并发送消息(键盘鼠标等)
	glfwSwapBuffers(mWindow);      //双缓存

	return true;
}

void Application::destroy()
{
	glfwTerminate();
	std::cout << "窗口已关闭" << std::endl;
}



void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	//if(Application::getInstance()->mResizeCallback != nullptr)
	//	Application::getInstance()->mResizeCallback(width, height);
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if(self->mResizeCallback != nullptr)
		self->mResizeCallback(width, height);
}
void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mKeyBoardCallback != nullptr)
		self->mKeyBoardCallback(key, action, mods);
}

void Application::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mMouseButtonCallback != nullptr)
		self->mMouseButtonCallback(button, action, mods);
}