#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include <iostream>
#include "Renderer/Model.h"
#include <Input/InputSystem.h>
#include <thread>
#include "Player.h"
#include "Enemy.h"
#include <fmod/core/inc/fmod.hpp>
#include "../../../Audio/AudioSystem.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include <memory>
#include "Renderer/ModelManager.h"
#include <Renderer/Font.h>
#include <Renderer/Text.h>
#include "SpaceGame.h"
#include "Renderer/ParticleSystem.h"
using namespace std;



class Star
{
public:
	Star(const kiko::vec2& pos, const kiko::vec2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update()
	{
	}
	void Draw(kiko::Renderer& renderer) {
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::vec2 m_pos;
	kiko::vec2 m_vel;
};


int main(int argc, char* argv[])
{

	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	kiko::Renderer renderer;
	kiko::g_renderer.Initialize();

	kiko::g_renderer.CreateWindow("CSC196", 800, 600);
	kiko::g_inputSystem.Initialize();
	kiko::g_audiosystem.Initialize();



	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++) {
		kiko::Vector2 pos(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight()));
		kiko::Vector2 vel(kiko::randomF(1.0f, 4.0f), 0.0f);
		stars.push_back(Star(pos, vel));
	}

	// Main Game Loop
	bool quit = false;
	while (!quit)
	{
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());

		g_audiosystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		game->Update(kiko::g_time.GetDeltaTime());

		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();

		for (auto& star : stars) {

			star.Update();
			if (star.m_pos.x >= kiko::g_renderer.GetWidth()) star.m_pos.x = 0;
			if (star.m_pos.y >= kiko::g_renderer.GetHeight()) star.m_pos.y = 0;

			kiko::g_renderer.SetColor(255, 255, 255, 255);
			star.Draw(kiko::g_renderer);
		}

		game->Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();

	}
	kiko::MemoryTracker::DisplayInfo();
	return 0;
}
