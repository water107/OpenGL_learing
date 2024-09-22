#include "Application.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


Application* Application::mInstance = nullptr;
Application* Application::getInstance() {
	//if mInstance�Ѿ�ʵ�����ˣ�new�������ˣ���ֱ�ӷ��أ��������new�ٷ���
	if (mInstance == nullptr){
		mInstance = new Application();
	}
	return mInstance;
}

//��ʼ��Application�ľ�̬����

Application::Application() {
	
}

Application::~Application() {
	
}

bool Application::init(const int& width, const int& height)
{
	mWidth = width;
	mHeight = height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  // ���汾�� 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);  // �ΰ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // ʹ��coreģʽ ����������Ⱦģʽ

	mWindow = glfwCreateWindow(mWidth, mHeight, "test", NULL, NULL);    // �������
	if (mWindow == NULL)
		return false;
	glfwMakeContextCurrent(mWindow); // ���õ�ǰ����Ϊopengl������̨

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD��ʼ��ʧ�ܣ�" << "\n";
		return false;
	}

	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);    //���ü���
	glfwSetKeyCallback(mWindow, keyCallback);
	glfwSetMouseButtonCallback(mWindow, MouseButtonCallback);

	glfwSetWindowUserPointer(mWindow, this);	//this���ǵ�ǰȫ��Ψһ��Application����ָ��

	return true;
}

bool Application::updata()
{
	if(glfwWindowShouldClose(mWindow))
		return false;

	glfwPollEvents();   // ���ܴ��ڲ�������Ϣ(��������)
	glfwSwapBuffers(mWindow);      //˫����

	return true;
}

void Application::destroy()
{
	glfwTerminate();
	std::cout << "�����ѹر�" << std::endl;
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