#include <App/IMCApplication.h>
#include <Random.h>

void IMCApplication::OnCreate()
{
	srand(time(NULL));
	m_Window = std::make_unique<IMCWindow>(1080, 720);
	m_Camera = std::make_unique<IMCCamera>();
	m_ParticleRenderer = std::make_unique<IMCParticleRenderer>(); 

	m_ParticleProp.colorBegin = { Random::Float(), Random::Float(), Random::Float(), 1.0f };
	m_ParticleProp.sizeBegin = Random::Int(103);
	m_ParticleProp.lifeTime = Random::Int(6);
	m_ParticleProp.velocity = { 0.0f, 0.0f };
	m_ParticleProp.position = { 0.0f, 0.0f };

	OnUpdate();
}

void IMCApplication::OnUpdate()
{
	double x;
	double y;
	while (m_Window->IsOpen())
	{
		m_Window->PollEvents();
		m_Camera->UpdateCamera(m_Window);

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		if (m_Window->isMousePressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			m_Window->GetMousePos(&x, &y);
			m_ParticleProp.position = { x * m_Camera->GetZoom() + m_Camera->position.x, y * m_Camera->GetZoom() + m_Camera->position.y };

			m_ParticleProp.colorBegin = { Random::Float(), Random::Float(), Random::Float(), 1.0f };
			m_ParticleProp.sizeBegin = Random::Int(103);
			m_ParticleProp.lifeTime = Random::Int(15);
			m_ParticleProp.velocity = { 0.0f, 0.0f };

			float vel_X = 6000;
			float vel_Y = 6000;
			m_ParticleProp.velocity = { vel_X, vel_Y };
			for (int i = 0; i < 7; i++)
				m_ParticleRenderer->Emit(m_ParticleProp);
		}

		m_ParticleRenderer->OnUpdate(m_Window->getDeltaTime(), m_Camera, m_Window);
		m_ParticleRenderer->OnRender(m_Camera, m_Window);

		m_Window->SwapBuffers();
	}
}
