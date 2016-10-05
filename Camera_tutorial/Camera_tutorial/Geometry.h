#pragma once
#include "Sources.h"
#include "Window.h"
#include "Camera.h"

struct Vertex {
	glm::vec4 position;
	glm::vec4 colour;
};

class Geometry : public Window
{
public:
	Geometry();
	~Geometry();

	bool startup() override;
	void shutdown() override;
	void generatePlane();
	void generateSquare();
	void generateSphere(const int radius, bool isfilled);
	void generateShader();

	bool update(float deltatime);
	void draw_Plane();
	void draw_Square();
	void draw_Sphere();
	void draw() override;
	void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	unsigned int m_programID;
	GLFWwindow* m_window;

	Camera* m_cam;
	bool m_dir;
};