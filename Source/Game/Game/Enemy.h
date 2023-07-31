#pragma once
#include "Framework/Actor.h"
#include <Renderer/Model.h>
using namespace kiko;
class Enemy : public kiko::Actor
{
public:
	Enemy(float speed, float turnRate, const kiko::Transform& transform, std::shared_ptr<Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireTime = 7.0f;
		m_fireTimer = m_fireTime;
	}

	virtual void Update(float dt) override;
	void onCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireTime = 0;
	float m_fireTimer = 0;
};