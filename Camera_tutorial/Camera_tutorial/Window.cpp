#include "Window.h"
#include "Sources.h"

using namespace glm;
GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

Window::Window()
{
}


Window::~Window()
{
}

void Window::run()
{

}

bool Window::startup()
{
	return false;
}

bool Window::update(float deltatime)
{
	return false;
}

void Window::draw()
{
}

void Window::shutdown()
{
}

bool Window::createWindow(const char * title, int width, int height)
{
	if (glfwInit() == false)
		return false;

	if (window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{

		glfwDestroyWindow(window);
		glfwTerminate();
		return false;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	Gizmos::create();
	mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
	return false;
}

void Window::destroyWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}