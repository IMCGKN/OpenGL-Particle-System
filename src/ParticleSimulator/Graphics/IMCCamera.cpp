#include <Graphics/IMCCamera.h>

#include <iostream>

IMCCamera::IMCCamera()
{
}

IMCCamera::~IMCCamera()
{
}

void IMCCamera::UpdateCamera(std::unique_ptr<IMCWindow>& window)
{
	if (window->isKeyPressed(GLFW_KEY_W))
		position.y -= speed * window->getDeltaTime();
	if (window->isKeyPressed(GLFW_KEY_S))
		position.y += speed * window->getDeltaTime();
	if (window->isKeyPressed(GLFW_KEY_A))
		position.x -= speed * window->getDeltaTime();
	if (window->isKeyPressed(GLFW_KEY_D))
		position.x += speed * window->getDeltaTime();
	if (window->isKeyPressed(GLFW_KEY_UP))
	{
		Zoom -= speedZoom * window->getDeltaTime();
	}
	if (window->isKeyPressed(GLFW_KEY_DOWN))
	{
		Zoom += speedZoom * window->getDeltaTime();
	}

	if (Zoom < 0.2f)
		Zoom = 0.2f;
	if (Zoom > 9.0f)
		Zoom = 9.0f;
}

glm::mat4& IMCCamera::GetProjectionViewMatrix(std::unique_ptr<IMCWindow>& window) const
{
	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::ortho(0.0f, (float)window->GetWidth() * Zoom, (float)window->GetHeight() * Zoom, 0.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(position, position + front, { 0.0f, 1.0f, 0.0f });
	glm::mat4 p_v = glm::mat4(1.0f);
	p_v = proj * view;
	return p_v;
}