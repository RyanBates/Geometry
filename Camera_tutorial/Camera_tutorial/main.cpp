#include <iostream>

#include "dep\AIEUtilities\Gizmos.h"
#include "dep\AIEUtilities\gl_core_4_4.h"
#include "dep\glfw\include\GLFW\glfw3.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm\gtx\transform.hpp>
#include "FlyCamera.h"

using namespace glm;


int main()
{

	if (glfwInit() == false)
		return -1;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	Camera* m_cam = new flycamera;

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{

		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	Gizmos::create();

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);


	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Gizmos::clear();
		Gizmos::addTransform(glm::mat4(1));

		vec4 white(1);
		vec4 black(0, 0, 0, 1);
		for (int i = 0; i < 21; ++i) {
			Gizmos::addLine(vec3(-10 + i, 0, 10),
				vec3(-10 + i, 0, -10),
				i == 10 ? white : black);
			Gizmos::addLine(vec3(10, 0, -10 + i),
				vec3(-10, 0, -10 + i),
				i == 10 ? white : black);
		}

		m_cam->update(deltaTime);

		Gizmos::draw(m_cam->getProjectionView());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}