#include "flycamera.h"
using namespace glm;


flycamera::flycamera()
{
	up = glm::vec3(0, 1, 0);

	setLookAt(vec3(10.f, 10.f, 10.f), vec3(0.f, 0.f, -1.0f), up);
	setPerspective(glm::pi<float>() * 0.35f, 16 / 9.f, 0.1f, 1000.f);
	lastX = 0;
	lastY = 0;
	firstMouseClick = true;	
}


flycamera::~flycamera()
{
}

void flycamera::update(float deltaTime)
{
	mat4 rotate = mat4(1);

	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT))
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
			rotate[1][1] = cos(axis);
			rotate[1][2] = -1 * sin(axis);
			rotate[2][1] = sin(axis);
			rotate[2][2] = cos(axis);
		}

		lastX = xpos;
		lastY = ypos;
	}

	viewTransform *= glm::inverse(rotate);
	updateProjectionViewTransform();
}

void flycamera::setSpeed(float speed)
{
}
