#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "Framework/Scene.h"
#include "../../../Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"
#include "Framework/Actor.h"
#include <Framework/Emitter .h>
#include "Core/MathUtils.h"
#include "Framework/Actor.h"
#include "Renderer/ParticleSystem.h"

bool SpaceGame::Initialize()
{
	// create font / text objects
	m_font = std::make_shared<kiko::Font>("Begok.ttf", 32);

	m_scoreText = std::make_unique<kiko::Text>(m_font);
	m_scoreText->Create(kiko::g_renderer, "0000", kiko::Color{ 1, 1, 1, 1 });

	m_titleText = std::make_unique<kiko::Text>(m_font);
	m_titleText->Create(kiko::g_renderer, "space invader", kiko::Color{ 1, 1, 1, 1 });

	m_gameoverText = std::make_unique<kiko::Text>(m_font);
	m_gameoverText->Create(kiko::g_renderer, "game over", kiko::Color{ 1, 1, 1, 1 });

	m_gameTimerText = std::make_unique<kiko::Text>(m_font);
	m_gameTimerText->Create(kiko::g_renderer, "timer", kiko::Color{ 1, 1, 1, 1 });
	
	m_retryText = std::make_unique<kiko::Text>(m_font);
	m_retryText->Create(kiko::g_renderer, "press space to retry", kiko::Color{ 1, 1, 1, 1 });

	m_startText = std::make_unique<kiko::Text>(m_font);
	m_startText->Create(kiko::g_renderer, "press space to start", kiko::Color{ 1, 1, 1, 1 });

	m_healthText = std::make_unique<kiko::Text>(m_font);
	m_healthText->Create(kiko::g_renderer, "3", kiko::Color{ 1, 1, 1, 1 });
	
	// load audio
	kiko::g_audiosystem.AddAudio("laser", "Laser_Shoot.wav");

	m_scene = std::make_unique<kiko::Scene>();

	return true;
}

void SpaceGame::Shutdown()
{

}


void SpaceGame::Update(float dt)
{
	switch (state)
	{
	case SpaceGame::eState::Title:
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			state = eState::StartGame;
		}
		break;
	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		state = eState::StartLevel;
		break;
	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
		{
			std::unique_ptr<Player> player = std::make_unique<Player>(20.0f, kiko::pi, kiko::Transform{ {400, 300}, 0, 6 }, kiko::g_manager.Get("Hourglass.txt"));
			player->m_tag = "Player";
			player->m_game = this;
			m_scene->Add(std::move(player));
		}
		state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		m_gameTimer += dt;

		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomF(75.0f, 300.0f), kiko::pi, kiko::Transform{ {400, 300}, kiko::randomF(kiko::twoPi), 3}, kiko::g_manager.Get("enemy.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));
		}
			break;
	case SpaceGame::eState::PlayerDeadStart:
		m_spawnTime = 3;
		if (m_lives == 0) state = eState::GameOver;
		else state = eState::PlayerDead;
		break;
	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			state = SpaceGame::eState::StartLevel;
		}

		break;
	case SpaceGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll();
			if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
			{
				state = eState::StartLevel;
				m_score = 0;
				m_gameTimer = 0;
			}

			
		}
		break;
	default:
		break;
		}

		m_scoreText->Create(kiko::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 });
		m_healthText->Create(kiko::g_renderer, std::to_string(m_lives), { 1, 1, 1, 1 });
		m_gameTimerText->Create(kiko::g_renderer, std::to_string((int)m_gameTimer), { 1, 1, 1, 1 });
		m_scene->Update(dt);
	}

	void SpaceGame::Draw(kiko::Renderer & renderer)
	{
		if (state == eState::Title)
		{
			m_titleText->Draw(renderer, 250, 300);
			m_startText->Draw(renderer, 150, 200);
		}
		if (state == eState::GameOver)
		{
			m_gameoverText->Draw(renderer, 250, 300);

			m_retryText->Draw(renderer, 150, 200);
		}

		m_scoreText->Draw(renderer, 40, 40);

		m_healthText->Draw(renderer, 700, 40);
		
		m_scene->Draw(renderer);

		m_gameTimerText->Draw(renderer, 350, 40);

		

		kiko::g_particleSystem.Draw(renderer);
	}
