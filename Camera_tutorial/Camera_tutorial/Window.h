#pragma once

class Window
{
public:
	Window();
	~Window();


	void run();

	virtual bool startup();
	virtual bool update(float deltatime) = 0;
	virtual void draw();
	virtual void shutdown();

	virtual bool createWindow(const char* title, int width, int height);
	virtual void destroyWindow();
};

