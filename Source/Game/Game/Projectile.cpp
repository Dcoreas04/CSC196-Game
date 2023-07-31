#include "Projectile.h"

void Projectile::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 foward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += foward * m_speed * m_speed * dt;
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());
}

void Projectile::onCollision(Actor* other)
{
	if (other->m_tag != m_tag)
	{
 		m_destroyed = true;
	}
}
