#include "pch.h"

#include "CirclevsCircleCollisionSystem.hpp"

namespace EE {
	CirclevsCircleCollisionSystem::CirclevsCircleCollisionSystem() {

	}

	CirclevsCircleCollisionSystem::~CirclevsCircleCollisionSystem() {

	}

	void CirclevsCircleCollisionSystem::update() {
		std::vector<std::uint32_t> entities = EntityManager::getEntities();
		std::shared_ptr<CircleCollider2DComponent> c1;
		std::shared_ptr<CircleCollider2DComponent> c2;
		std::shared_ptr<Transform2DComponent> t1;
		std::shared_ptr<Transform2DComponent> t2;
		Vector2D<float> separationVector;
		for (int i = 0; i < (int)entities.size() - 1; i++) {
			for (int j = i + 1; j < entities.size(); j++) {
				c1 = ComponentManager::getComponent<CircleCollider2DComponent>(entities[i]);
				c2 = ComponentManager::getComponent<CircleCollider2DComponent>(entities[j]);
				t1 = ComponentManager::getComponent<Transform2DComponent>(entities[i]);
				t2 = ComponentManager::getComponent<Transform2DComponent>(entities[j]);
				if (c1 && c2 && t1 && t2) {
					if (c1->getStackLayer() == 0 && c2->getStackLayer() == 0) {
						float distance = (t2->position() - t1->position()).magnitude();
						float rr = c1->radius() + c2->radius();
						if (distance <= rr) {
							separationVector = t1->position() - t2->position();
							c1->callHandler(*t2, separationVector);
							c2->callHandler(*t1, separationVector * -1);
						}
					}
				}
			}
		}
	}

}