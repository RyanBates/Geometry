#ifndef _CAMERA_H
#define _CAMERA_H

#include "dep\AIEUtilities\Gizmos.h"
#include "dep\AIEUtilities\gl_core_4_4.h"
#include "dep\glfw\include\GLFW\glfw3.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm\gtx\transform.hpp>

class Camera 
{
public:
	Camera();
	~Camera();
	
	glm::mat4 viewTransform;


	virtual void update(float deltaTime) = 0;
	virtual void setPerspective(float fieldOfView, float aspectRatio, float near, float far);
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