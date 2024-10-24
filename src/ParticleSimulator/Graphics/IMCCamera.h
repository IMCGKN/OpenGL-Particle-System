#pragma once

#include <memory>

#include <Window/IMCWindow.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class IMCCamera
{
public:
	IMCCamera();
	~IMCCamera();

	void UpdateCamera(std::unique_ptr<IMCWindow>& window);

	glm::mat4& GetProjectionViewMatrix(std::unique_ptr<IMCWindow>& window) const;
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	float GetZoom()
	{
		return Zoom;
	}
private:
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);


	float speed = 500.0f;
	float speedZoom = 5.0f;
	float Zoom = 1.0f;
};
