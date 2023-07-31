#include "Scene.h"
#include "Actor.h"
namespace kiko
{
	void Scene::Update(float dt)
	{
		// Remove destroyed actors
		auto iter = m_actor.begin();
		while (iter != m_actor.end())
		{
			(*iter)->Update(dt);
			iter = (iter->get()->m_destroyed) ? m_actor.erase(iter) : ++iter;
		}

		for (auto iter1 = m_actor.begin(); iter1 != m_actor.end(); iter1++)
		{

			for (auto iter2 = std::next(iter1, 1); iter2 != m_actor.end(); iter2++)
			{
				float distance = (*iter1)->m_transform.position.Distance((*iter2)->m_transform.position);
				float radius = (*iter1)->getRadius() + (*iter2)->getRadius();

				if (distance < radius)
				{
					(*iter1)->onCollision(iter2->get());
					(*iter2)->onCollision(iter1->get());
				}
			}
		}
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actor) actor->Draw(renderer);
	}
	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actor.push_back(std::move(actor));
	}
	void Scene::Remove(Actor* actor)
	{
		// m_actor.remove(actor);
	}
	void Scene::RemoveAll()
	{
		m_actor.clear();
	}
}