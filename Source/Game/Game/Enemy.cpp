#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Projectile.h"
#include "SpaceGame.h"
#include "Renderer/ModelManager.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 foward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		kiko::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() + kiko::hlfPi;

		float turnAngle = kiko::vec2::SignedAngle(foward, direction.Normalized());
		m_transform.rotation = turnAngle * 5 * dt;
	
		if (std::fabs(turnAngle) < kiko::DegreestoRadians(30.0f))
		{
			
		}
	}

	
	m_transform.position += foward * m_speed * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	if (m_fireTimer <= 0) {
		m_fireTimer = m_fireTime;

		kiko::Transform transforms{ m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(40.0f, transforms, kiko::g_manager.Get("pew.txt"));
		projectile->m_tag = "Enemy";
		m_scene->Add(std::move(projectile));
	}
	else
	{
		m_fireTimer -= dt;
	}
}

void Enemy::onCollision(Actor* other)
{
	Player* p = dynamic_cast<Player*>(other);
	if (other->m_tag == "Player")
	{
		m_game->AddPoints(100);
		m_destroyed = true;
	}
}
