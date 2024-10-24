#include <Window/IMCWindow.h>

#include <IMCPrerequisites.h>

IMCWindow::IMCWindow(int width, int height)
	: m_Width(width), m_Height(height)
{ 
	if (!glfwInit())
		IMC_ERROR("IMCWindow Error | Failed to init GLFW.");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	m_Window = glfwCreateWindow(m_Width, m_Height, "Particle Simulator - OpenGL", NULL, NULL);
	if (!m_Window)
	{
		glfwTerminate();
		IMC_ERROR("IMCWindow Error | Failed to create GLFWwindow.");
	}
	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		IMC_ERROR("IMCWindow Error | Failed to initialize GLAD.");
	}

	glViewport(0, 0, m_Width, m_Height);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

#ifdef _DEBUG
	IMC_INFO("IMCWindow | Vendor: " << glGetString(GL_VENDOR));
	IMC_INFO("IMCWindow | OpenGL Version: " << glGetString(GL_VERSION));
	IMC_INFO("IMCWindow | OpenGL GPU: " << glGetString(GL_RENDERER));
#endif
}

IMCWindow::~IMCWindow()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void IMCWindow::PollEvents()
{
	CalculateDeltaTime();
	glfwPollEvents();
}

void IMCWindow::SwapBuffers()
{
	glfwSwapBuffers(m_Window);
}

int IMCWindow::GetWidth()
{
	return m_Width;
}

int IMCWindow::GetHeight()
{
	return m_Height;
}

bool IMCWindow::IsOpen()
{
	return !glfwWindowShouldClose(m_Window);
}

bool IMCWindow::isKeyPressed(int key)
{
	return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

bool IMCWindow::isMousePressed(int key)
{
	return glfwGetMouseButton(m_Window, key) == GLFW_PRESS;
}

void IMCWindow::GetMousePos(double* x, double* y)
{
	glfwGetCursorPos(m_Window, x, y);
}

float IMCWindow::getDeltaTime() const
{
	return m_DeltaTime;
}

void IMCWindow::CalculateDeltaTime()
{
	float newFrame = glfwGetTime();
	m_DeltaTime = newFrame - m_LastFrame;
	m_LastFrame = newFrame;
}
