#include "Actor.h"
namespace kiko {

	void Actor::Update(float dt) {
		if (m_lifespan != -1)
		{
			m_lifespan -= dt;
			if (m_lifespan <= 0)
			{
				m_destroyed = true;
			}
		}
		m_transform.position += m_Velocity * dt;
		m_Velocity *= std::pow(1 - m_damping, dt);
	}

	void Actor::Draw(kiko::Renderer& renderer) {
		m_model->Draw(renderer, m_transform);
	}
}