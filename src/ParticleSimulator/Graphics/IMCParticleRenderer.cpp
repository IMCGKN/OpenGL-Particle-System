#include <Graphics/IMCParticleRenderer.h>
#include <Random.h>

float lerp(float a, float b, float f)
{
	return a * (1.0 - f) + (b * f);
}

IMCParticleRenderer::IMCParticleRenderer()
{
	m_Particles.reserve(4000);
	m_Vao = std::make_unique<IMCVao>();
	m_Shader = std::make_unique<IMCShader>("res/shaders/main.vert", "res/shaders/main.frag");
}

IMCParticleRenderer::~IMCParticleRenderer()
{
}

void IMCParticleRenderer::OnUpdate(float dt, std::unique_ptr<IMCCamera>& camera, std::unique_ptr<IMCWindow>& window)
{
	for (int i = 0; i < m_Particles.size(); i++)
	{
		if (!m_Particles[i].active)
			continue;

		if (m_Particles[i].lifeRemaining <= 0.0f)
		{
			m_Particles.erase(m_Particles.begin() + i);
			continue;
		}

		m_Particles[i].lifeRemaining -= dt;
		m_Particles[i].position += m_Particles[i].velocity * (float)dt;
		if (m_Particles[i].position.x <= camera->position.x)
		{
			m_Particles[i].velocity.x *= -1.0f;
		}
		else if (m_Particles[i].position.x >= camera->position.x + window->GetWidth() * camera->GetZoom())
		{
			m_Particles[i].velocity.x *= -1.0f;
			m_Particles[i].position.x = camera->position.x + window->GetWidth() * camera->GetZoom();
		}
		else if (m_Particles[i].position.y <= camera->position.y)
		{
			m_Particles[i].velocity.y *= -1.0f;
		}
		else if (m_Particles[i].position.y >= camera->position.y + window->GetHeight() * camera->GetZoom())
		{
			m_Particles[i].velocity.y *= -1.0f;
			m_Particles[i].position.y = camera->position.y + window->GetHeight() * camera->GetZoom();
		}
	}
}

void IMCParticleRenderer::OnRender(std::unique_ptr<IMCCamera>& camera, std::unique_ptr<IMCWindow>& window)
{
	m_Shader->Use();
	glm::mat4 p_v = camera->GetProjectionViewMatrix(window);
	m_Shader->SetMat4("projView", p_v);
	m_Vao->Use();
	for (auto& particle : m_Particles)
	{
		if (!particle.active)
			continue;

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, { particle.position.x, particle.position.y, 0.0f });
		transform = glm::scale(transform, { particle.sizeBegin, particle.sizeBegin, 1.0f });
		m_Shader->Use();
		m_Shader->SetMat4("model", transform);
		m_Shader->SetVec4("col", particle.colorBegin);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
	m_Vao->Unuse();
	m_Shader->Unuse();
}

void IMCParticleRenderer::Emit(const Particle& particle_template)
{
	Particle particle;
	particle.active = true;
	particle.position = particle_template.position;

	// Velocity
	particle.velocity = particle_template.velocity;
	particle.velocity.x += particle_template.velocity.x * (Random::Float() - 1.5f);
	particle.velocity.y += particle_template.velocity.y * (Random::Float() - 1.5f);

	// Color
	particle.colorBegin.r = particle_template.colorBegin.r;
	particle.colorBegin.g = particle_template.colorBegin.g;
	particle.colorBegin.b = particle_template.colorBegin.b;

	particle.lifeTime = particle_template.lifeTime;
	particle.lifeRemaining = particle_template.lifeTime;
	particle.sizeBegin = Random::Int(40) + 2;
	particle.sizeEnd = 0.0f;

	m_Particles.push_back(particle);
}
