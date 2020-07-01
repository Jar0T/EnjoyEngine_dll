#include "pch.h"
#include "AABBvsAABBCollisionSystem.hpp"

namespace EE {
	AABBvsAABBCollisionSystem::AABBvsAABBCollisionSystem() {

	}

	AABBvsAABBCollisionSystem::~AABBvsAABBCollisionSystem() {

	}

	void AABBvsAABBCollisionSystem::update() {
		std::vector<std::uint32_t> entities = EntityManager::getEntities();
		for (int i = 0; i < entities.size() - 1; i++) {
			for (int j = i + 1; j < entities.size(); i++) {
				AABBCollider2DComponent* c1 = ComponentManager::getComponent<AABBCollider2DComponent>(entities[i]);
				AABBCollider2DComponent* c2 = ComponentManager::getComponent<AABBCollider2DComponent>(entities[j]);
				if (c1 && c2) {
					if (c1->getStackLayer() == 0 && c2->getStackLayer() == 0) {
						if (c1->position().x < c2->position().x + c2->size().x &&
							c1->position().x + c1->size().x > c2->position().x &&
							c1->position().y < c2->position().y + c2->size().y &&
							c1->position().y + c1->size().y > c2->position().y) {
							std::cout << "AABB vs AABB collision detected\n";
						}
					}
				}
			}
		}
	}

}