#pragma once
#include "Framework/Actor.h"
#include <Renderer/Model.h>
using namespace kiko;
class Projectile : public kiko::Actor
{
public:
	Projectile(float speed, const kiko::Transform& transform, std::shared_ptr<Model> model) :
		Actor{ transform, model },
		m_speed{ speed }
	{
		m_lifespan = 2.0f;
	}

	virtual void Update(float dt) override;
	void onCollision(Actor* actor) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;

};