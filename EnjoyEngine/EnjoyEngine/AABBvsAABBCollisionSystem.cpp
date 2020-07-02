#include "pch.h"
#include "AABBvsAABBCollisionSystem.hpp"

namespace EE {
	AABBvsAABBCollisionSystem::AABBvsAABBCollisionSystem() {

	}

	AABBvsAABBCollisionSystem::~AABBvsAABBCollisionSystem() {

	}

	void AABBvsAABBCollisionSystem::update() {
		std::vector<std::uint32_t> entities = EntityManager::getEntities();
		AABBCollider2DComponent* c1;
		AABBCollider2DComponent* c2;
		Transform2DComponent* t1;
		Transform2DComponent* t2;
		Vector2D<float> separationVector;
		for (int i = 0; i < entities.size() - 1; i++) {
			for (int j = i + 1; j < entities.size(); i++) {
				c1 = ComponentManager::getComponent<AABBCollider2DComponent>(entities[i]);
				c2 = ComponentManager::getComponent<AABBCollider2DComponent>(entities[j]);
				t1 = ComponentManager::getComponent<Transform2DComponent>(entities[i]);
				t2 = ComponentManager::getComponent<Transform2DComponent>(entities[j]);

				if (c1 && c2 && t1 && t2) {
					if (c1->getStackLayer() == 0 && c2->getStackLayer() == 0) {
						if (t1->position().x < t2->position().x + c2->size().x &&
							t1->position().x + c1->size().x > t2->position().x &&
							t1->position().y < t2->position().y + c2->size().y &&
							t1->position().y + c1->size().y > t2->position().y) {
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