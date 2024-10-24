#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class IMCWindow
{
public:
	IMCWindow(int width, int height);
	~IMCWindow();

	void PollEvents();
	void SwapBuffers();
	void GetMousePos(double* x, double* y);

	int GetWidth();
	int GetHeight();

	bool IsOpen();
	bool isKeyPressed(int key);
	bool isMousePressed(int key);

	float getDeltaTime() const;
private:
	GLFWwindow* m_Window = nullptr;
	int m_Width = 0, m_Height = 0;

	float m_DeltaTime = 0.0f;
	float m_LastFrame = 0.0f;

	int m_FrameCount = 0;

	void CalculateDeltaTime();
};
