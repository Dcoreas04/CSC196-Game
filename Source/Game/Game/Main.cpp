#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include <iostream>
using namespace std;

class Star
{
public:
	Star(const kiko::Vector2& pos, const kiko::Vector2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update()
	{
		m_pos += m_vel;
	}

	void Draw(kiko::Renderer& renderer) {
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::Vector2 m_pos;
	kiko::Vector2 m_vel;
};


int main(int argc, char* argv[])
{
	kiko::seedRandom((unsigned int)time(nullptr));



	kiko::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC196", 800, 600);
	
	vector<Star> stars;
	for (int i = 0; i < 1000; i++) {
		kiko::Vector2 pos(kiko::randomF(renderer.GetWidth()), kiko::randomF(renderer.GetHeight()));
		kiko::Vector2 vel(kiko::randomF(1.0f, 4.0f), 0.0f);
		stars.push_back(Star(pos, vel));
	}

	while (true) 
	{
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		for (auto& star : stars) {

			star.Update();
			if (star.m_pos.x >= renderer.GetWidth()) star.m_pos.x = 0;
			if (star.m_pos.y >= renderer.GetHeight()) star.m_pos.y = 0;

			//renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			renderer.SetColor(255, 255, 255, 255);
			star.Draw(renderer);
		}
		

		
		renderer.EndFrame();
	}
}