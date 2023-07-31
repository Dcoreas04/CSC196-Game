#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>

namespace kiko {
	class Actor
	{
	public:
		Actor() = default;

		Actor(const kiko::Transform& transform, const std::shared_ptr<Model> model) :
			m_transform{ transform },
			m_model{ model }
		{}
		Actor(const kiko::Transform& transform) :
			m_transform{ transform }
		{}

		virtual void Update(float dt) = 0;
		virtual void Draw(kiko::Renderer& renderer);

		float getRadius() { return (m_model) ? m_model->getRadius() * m_transform.scale: 0; }

		virtual void onCollision(Actor* other) {}
		
		void AddForce(const vec2 force) { m_Velocity += force; }
		void setDamping(float damping) { m_damping = damping; }

		class Scene* m_scene = nullptr;
		friend class Scene;
		class Game* m_game = nullptr;

		kiko::Transform m_transform;
		std::string m_tag;

		float m_lifespan = -1.0f;

	protected:
		bool m_destroyed = false;
		std::shared_ptr<Model> m_model;
	
		vec2 m_Velocity;
		float m_damping = 0;
	};
}