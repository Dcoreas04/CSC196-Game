#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"

class Player : public kiko::Actor
{
public:
	Player(float speed, float turnRate, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model },
		m_speed { speed },
		m_turnRate{ turnRate }
	{}

	virtual void Update(float dt) override;
	void onCollision(Actor* other) override;

private:
	float m_health = 5;
	float m_speed = 0;
	float m_turnRate = 0;

};