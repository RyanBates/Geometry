#include "flycamera.h"
using namespace glm;


flycamera::flycamera()
{
	up = glm::vec3(0, 1, 0);

	setLookAt(vec3(),vec3(), vec3());
	setPerspective(glm::pi<float>() * .35f,0,0,0);
	lastX = 0;
	lastY = 0;
	firstMouseClick = true;
}


flycamera::~flycamera()
{
}

void flycamera::update(float deltaTime)
{
	mat4 trans = mat4(1);
	mat4 rotate = mat4(1);
	mat4 scale = mat4(1);

	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		double xpos = 0; 
		double ypos = 0;

		float axis = 0.0f;

		float xoffset = lastX - xpos;
		float yoffset = lastY - ypos;

		glfwGetCursorPos(m_window, &xpos, &ypos);


		if (xoffset < 1 || xoffset > 1)
		{
			axis = xoffset;
			rotate[0][0] = cos(axis);
			rotate[0][2] = sin(axis);
			rotate[2][0] = -1.f * sin(axis);
			rotate[2][2] = cos(axis);
		}

		if (yoffset < 1 || yoffset > 1)
		{
			axis = yoffset;
			rotate[0][0] = cos(axis);
			rotate[1][2] = -1 * sin(axis);
			rotate[2][1] = sin(axis);
			rotate[2][2] = cos(axis);
		}

		lastX = xpos;
		lastY = ypos;
	}

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		trans = glm::translate(vec3(0, 0, (-0.10f * deltaTime) * 10));
	}

	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		trans = glm::translate(vec3(-(-0.10f * deltaTime) * 10, 0, 0));
	}

	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		trans = glm::translate(vec3(0, 0, -(-0.10f * deltaTime) * 10));
	}

	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		trans = glm::translate(vec3((-0.10f * deltaTime) * 10, 0, 0));
	}

	viewTransform *= glm::inverse(trans * rotate * scale);
	updateProjectionViewTransform();
}

void flycamera::setSpeed(float speed)
{
}
