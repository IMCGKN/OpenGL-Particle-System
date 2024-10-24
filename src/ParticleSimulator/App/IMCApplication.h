#pragma once
#include <memory>

#include <Window/IMCWindow.h>
#include <Graphics/IMCCamera.h>
#include <Graphics/IMCParticleRenderer.h>

class IMCApplication
{
public:
	void OnCreate();

private:
	void OnUpdate();

private:
	std::unique_ptr<IMCWindow> m_Window;
	std::unique_ptr<IMCCamera> m_Camera;
	std::unique_ptr<IMCParticleRenderer> m_ParticleRenderer;

	Particle m_ParticleProp;
};
