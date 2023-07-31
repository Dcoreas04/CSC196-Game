#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "../../../Audio/AudioSystem.h"
#include "projectile.h"
#include "Framework/Scene.h"
#include "SpaceGame.h"
#include <Framework/Emitter .h>
#include "Renderer/ModelManager.h"
void Player::Update(float dt)
{
	Actor::Update(dt);

	// movement
	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	kiko::vec2 foward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	AddForce(foward * m_speed * thrust);


	// fire projectile
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && (!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)))
	{
		kiko::Transform transform1{ m_transform.position, m_transform.rotation + kiko::DegreestoRadians(10.0f), 1};
		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(40.0f, transform1, kiko::g_manager.Get("pew.txt"));
		projectile->m_tag = "Player";
		m_scene->Add(std::move(projectile));

		kiko::Transform transform2{ m_transform.position, m_transform.rotation - kiko::DegreestoRadians(10.0f), 1};
		projectile = std::make_unique<Projectile>(40.0f, transform2, kiko::g_manager.Get("pew.txt"));
		projectile->m_tag = "Player";
		m_scene->Add(std::move(projectile));

		g_audiosystem.PlayOneShot("laser");
	
		EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = kiko::pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = kiko::Color{ 1, 0, 0, 1 };
		Transform transform{ { g_inputSystem.GetMousePosition() }, 0, 1 };
		auto emitter = std::make_unique<Emitter>(transform, data);
		emitter->m_lifespan = 0;
		m_scene->Add(std::move(emitter));
	}
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_Q) && (!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_Q)))
	{
		kiko::Transform transform3{ m_transform.position, m_transform.rotation + kiko::DegreestoRadians(10.0f), 1};
		std::unique_ptr<Projectile> wall = std::make_unique<Projectile>(10.0f, transform3, kiko::g_manager.Get("wall.txt"));
		wall->m_tag = "Player";
		m_scene->Add(std::move(wall));

		g_audiosystem.PlayOneShot("laser");
	}

	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_P)) kiko::g_time.setTimeScale(0.5f);
	else kiko::g_time.setTimeScale(1.0f);

}

void Player::onCollision(Actor* other)
{
	if (other->m_tag == "Enemy")
	{
		EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = kiko::pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = kiko::Color{ 1, 0, 0, 1 };
		Transform transform{ { m_transform.position }, 0, 1 };
		auto emitter = std::make_unique<Emitter>(transform, data);
		emitter->m_lifespan = 0;
		m_scene->Add(std::move(emitter));

		m_game->SetLives(m_game->GetLives() - 1);
		m_destroyed = true;
		dynamic_cast<SpaceGame*>(m_game)->setState(SpaceGame::eState::PlayerDeadStart);
	}

}
