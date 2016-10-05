#ifndef _FLYCAMERA_H_
#define _FLYCAMERA_H_

#include "Camera.h"

#pragma once
class flycamera : public Camera
{
public:
	flycamera();
	~flycamera();

	void update(float deltaTime);
	void setSpeed(float speed);

private:
	float speed;
	glm::vec3 up;
	double lastX;
	double lastY;
	bool firstMouseClick;

	GLFWwindow* m_window;
};
#endif