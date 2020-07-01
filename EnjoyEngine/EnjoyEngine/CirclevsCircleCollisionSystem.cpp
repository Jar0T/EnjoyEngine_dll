#include "pch.h"

#include "CirclevsCircleCollisionSystem.hpp"

namespace EE {
	CirclevsCircleCollisionSystem::CirclevsCircleCollisionSystem() {

	}

	CirclevsCircleCollisionSystem::~CirclevsCircleCollisionSystem() {

	}

	void CirclevsCircleCollisionSystem::update() {
		std::vector<std::uint32_t> entities = EntityManager::getEntities();
		for (int i = 0; i < entities.size() - 1; i++) {
			for (int j = i + 1; j < entities.size(); i++) {
				CircleCollider2DComponent* c1 = ComponentManager::getComponent<CircleCollider2DComponent>(entities[i]);
				CircleCollider2DComponent* c2 = ComponentManager::getComponent<CircleCollider2DComponent>(entities[j]);
				if (c1 && c2) {
					if (c1->getStackLayer() == 0 && c2->getStackLayer() == 0) {
						float distance = (c2->position() - c1->position()).magnitude();
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