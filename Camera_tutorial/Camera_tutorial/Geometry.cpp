#include "Geometry.h"

using namespace glm;

Geometry::Geometry()
	:m_cam(nullptr),
	m_dir(false) {};

Geometry::~Geometry()
{
}

void Geometry::generatePlane()
{
	Vertex vertices[4];
	unsigned int indices[4] = { 0,2,1,3 };

	vertices[0].position = vec4(-5, 0, -5, 1);
	vertices[1].position = vec4(5, 0, -5, 1);
	vertices[2].position = vec4(-5, 0, 5, 1);
	vertices[3].position = vec4(5, 0, 5, 1);

	vertices[0].colour = vec4(1, 0, 0, 1);
	vertices[1].colour = vec4(0, 1, 0, 1);
	vertices[2].colour = vec4(0, 0, 1, 1);
	vertices[3].colour = vec4(1, 1, 1, 1);

	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	//Add the following line to generate a VertexArrayObject
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	//i need to give the information for the layout location 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);


	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	// ....Code Segment here to bind and fill VBO + IBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//	delete[] vertices;
}

void Geometry::generateSquare()
{
	Vertex vertices[8];
	unsigned int indices[8] = {0, 2, 1, 3, 4, 6, 5, 7};

	vertices[0].position = vec4(-1,0,-1,1);
	vertices[1].position = vec4(1,0,-1, 1);
	vertices[2].position = vec4(-1, 0, 1, 1);
	vertices[3].position = vec4(1, 0, 1, 1);
	vertices[4].position = vec4(-3, 0, -3, 1);
	vertices[5].position = vec4(3, 0, -3, 1);
	vertices[6].position = vec4(-3, 0, 3, 1);
	vertices[7].position = vec4(3, 0, 3, 1);

	vertices[0 - 7].colour = vec4(1, 0, 0, 1);

	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	//Add the following line to generate a VertexArrayObject
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	//i need to give the information for the layout location 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	// ....Code Segment here to bind and fill VBO + IBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Geometry::generateSphere(const int radius, bool isfilled)
{
	Vertex vertices[24];
	unsigned int indices[16] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };

	for (int i = 0; i < 16; i++)
	{
		double angle = i * (2 * 3.14159 / 22);

		double X = cos(angle) * radius;
		double Z = cos(angle) * radius;
	}

	vertices[0 - 24].colour = vec4(0, 1, 1, 1);

	//generate buffers
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);
	//generate vertex arrays
	glGenVertexArrays(1, &m_VAO);
	//bind vertex arrays
	glBindVertexArray(m_VAO);
	//bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//set buffer data for vertices
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	//set buffer data for indinces
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

}

void Geometry::generateShader()
{
	// create shader
	const char* vsSource = "#version 410\n \
							layout(location=0) in vec4 Position; \
							layout(location=1) in vec4 Colour; \
							out vec4 vColour; \
							uniform mat4 ProjectionViewWorld; \
							void main() { vColour = Colour; \
							gl_Position = ProjectionViewWorld * Position; }";

	const char* fsSource = "#version 410\n \
							in vec4 vColour; \
							out vec4 FragColor; \
							void main() { FragColor = vColour; }";

	int success = GL_FALSE;
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	glLinkProgram(m_programID);

	// check that it compiled and linked correctly
	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength + 1];
		glGetProgramInfoLog(m_programID, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}
	
	// we don't need to keep the individual shaders around
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
}

bool Geometry::startup()
{
	createWindow("AIE OpenGL Application", 1280, 720);

	m_cam->setPerspective(glm::pi<float>() * .25f, 16.0f / 9.0f, 0.0f, 20.0f);
	m_cam->setLookAt(vec3(10,10,10), vec3(0), vec3(1));
	
	generateShader();
	generatePlane();
	generateSquare();
	generateSphere(5, true);

	return false;
}

void Geometry::shutdown()
{
	delete m_cam;

	destroyWindow();
}

bool Geometry::update(float deltatime)
{
	if (glfwWindowShouldClose(m_window) == false || glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return true;
	}
	return false;
}

void Geometry::draw_Plane()
{
	// clear the screen for this frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind shader
	glUseProgram(m_programID);

	// where to send the matrix
	int matUniform = glGetUniformLocation(m_programID, "ProjectionViewWorld");

	// send the matrix
	glUniformMatrix4fv(matUniform, 1, GL_FALSE, glm::value_ptr(m_cam->getProjectionView()));
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)0);
}

void Geometry::draw_Square()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_programID);

	int matUniform = glGetUniformLocation(m_programID, "ProjectionViewWorld");

	glUniformMatrix4fv(matUniform, 1, GL_FALSE, glm::value_ptr(m_cam->getProjectionView()));
	glBindVertexArray(m_VAO);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void*)0);
}

void Geometry::draw_Sphere()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_programID);

	int matUniform = glGetUniformLocation(m_programID, "ProjectionViewWorld");

	glUniformMatrix4fv(matUniform, 1, GL_FALSE, glm::value_ptr(m_cam->getProjectionView()));
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)0);
}

void Geometry::draw()
{
	draw_Plane();
	//draw_Square();
	//draw_Sphere();
}

void Geometry::inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	Geometry* myThis = (Geometry*)glfwGetWindowUserPointer(window);

	if (key == GLFW_KEY_SPACE)
		if (action == GLFW_PRESS)
			myThis->m_dir = true;
		else if (action == GLFW_RELEASE)
			myThis->m_dir = false;
}