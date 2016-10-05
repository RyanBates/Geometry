#ifndef _CAMERA_H
#define _CAMERA_H
#include "Sources.h"

class Camera 
{
public:
	Camera();
	~Camera();

	float currentTime = (float)glfwGetTime();
	float previousTime = currentTime;
	float deltaTime = currentTime - previousTime;
	
	glm::mat4 viewTransform;


	virtual void update(float deltaTime) = 0;
	void setPerspective(float fieldOfView, float aspectRatio, float near, float far);
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setPosition(glm::vec3 position);
	glm::mat4 getWorldTransfom();
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::mat4 getProjectionView();
	void updateProjectionViewTransform();

private:
	glm::mat4 worldTransfom;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;
};
#endif