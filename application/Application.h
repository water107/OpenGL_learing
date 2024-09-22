#pragma once

#include "../glframework/core.h"
// #include "GLFW/glfw3.h"

#define mapp Application::getInstance()

using ResizeCallback = void(*)(int width, int height);
using OnKeyBoardCallback = void(*)(int key, int action, int mods);
using OnMouseButtonCallback = void(*)(int button, int action, int mods);

struct GLFWwindow;

class Application {
public:
	~Application();

	static Application* getInstance();	//用于访问实例函数的静态函数

	bool init(const int& width, const int& height);
	bool updata();
	void destroy();

	void setResizeCallback(ResizeCallback callback) { mResizeCallback = callback; };
	void setKeyBoardCallback(OnKeyBoardCallback callback) { mKeyBoardCallback = callback; };
	void setMuseCallback(OnMouseButtonCallback callback) { mMouseButtonCallback = callback; };
	static void frameBufferSizeCallback(GLFWwindow* mWindow, int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	uint32_t getWidth() const { return mWidth; }
	uint32_t getHeight() const { return mHeight; }
	
private:
	static Application* mInstance;	//全局唯一的静态变量实例

	uint32_t mWidth{ 0 };
	uint32_t mHeight{ 0 };
	GLFWwindow* mWindow{nullptr};

	ResizeCallback mResizeCallback{nullptr};	//ResizeCallback类型的成员变量
	OnKeyBoardCallback mKeyBoardCallback{nullptr};
	OnMouseButtonCallback mMouseButtonCallback{nullptr};

	Application();	//构造函数
};

