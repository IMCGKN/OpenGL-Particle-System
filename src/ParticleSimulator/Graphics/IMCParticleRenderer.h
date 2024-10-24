#pragma once

#include <vector>
#include <cmath>

#include <Graphics/IMCShader.h>
#include <Graphics/IMCVao.h>
#include <Graphics/IMCCamera.h>
#include <Window/IMCWindow.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

struct Particle
{
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec4 colorBegin;
	glm::vec4 colorEnd;
	float sizeBegin, sizeEnd;

	float lifeTime = 1.0f;
	float lifeRemaining = 0.0f;

	bool active = false;
};

class IMCParticleRenderer
{
public:
	IMCParticleRenderer();
	~IMCParticleRenderer();

	void OnUpdate(float dt, std::unique_ptr<IMCCamera>& camera, std::unique_ptr<IMCWindow>& window);
	void OnRender(std::unique_ptr<IMCCamera>& camera, std::unique_ptr<IMCWindow>& window);
	
	void Emit(const Particle& particleProps);
private:
	
	std::vector<Particle> m_Particles;

	std::unique_ptr<IMCVao> m_Vao;
	std::unique_ptr<IMCShader> m_Shader;

	int m_PoolIndex = 999;
};
