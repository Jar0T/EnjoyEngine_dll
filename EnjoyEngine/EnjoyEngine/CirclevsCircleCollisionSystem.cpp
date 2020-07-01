#include "pch.h"

#include "CirclevsCircleCollisionSystem.hpp"

namespace EE {
	CirclevsCircleCollisionSystem::CirclevsCircleCollisionSystem() {

	}

	CirclevsCircleCollisionSystem::~CirclevsCircleCollisionSystem() {

	}

	void CirclevsCircleCollisionSystem::update() {
		std::vector<std::uint32_t> entities = EntityManager::getEntities();
		CircleCollider2DComponent* c1;
		CircleCollider2DComponent* c2;
		Transform2DComponent* t1;
		Transform2DComponent* t2;
		for (int i = 0; i < entities.size() - 1; i++) {
			for (int j = i + 1; j < entities.size(); i++) {
				c1 = ComponentManager::getComponent<CircleCollider2DComponent>(entities[i]);
				c2 = ComponentManager::getComponent<CircleCollider2DComponent>(entities[j]);
				t1 = ComponentManager::getComponent<Transform2DComponent>(entities[i]);
				t2 = ComponentManager::getComponent<Transform2DComponent>(entities[j]);
				if (c1 && c2 && t1 && t2) {
					if (c1->getStackLayer() == 0 && c2->getStackLayer() == 0) {
						float distance = (t2->position() - t1->position()).magnitude();
						float rr = c1->radius() + c2->radius();
						if (distance <= rr) {
							std::cout << "Circle vs Circle collision detected\n";
						}
					}
				}
			}
		}
	}

}