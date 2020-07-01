#include "pch.h"
#include "AABBvsCircleCollisionSystem.hpp"

namespace EE {
	bool AABBvsCircleCollisionSystem::checkCollision(AABBCollider2DComponent* a, CircleCollider2DComponent* b) {
		if (a && b) {
			Vector2D<float> ab = a->position() - b->position();
			if (ab.x > a->size().x)
				ab.x = a->size().x;
			if (ab.x < 0)
				ab.x = 0;
			if (ab.y > a->size().y)
				ab.y = a->size().y;
			if (ab.y < 0)
				ab.y = 0;
			float distance = (ab - b->position()).magnitude();
			if (distance <= b->radius()) {
				return true;
			}
		}
		return false;
	}

	AABBvsCircleCollisionSystem::AABBvsCircleCollisionSystem() {

	}

	AABBvsCircleCollisionSystem::~AABBvsCircleCollisionSystem() {

	}

	void AABBvsCircleCollisionSystem::update() {
		std::vector<std::uint32_t> entities = EntityManager::getEntities();
		for (int i = 0; i < entities.size() - 1; i++) {
			for (int j = i + 1; j < entities.size(); i++) {
				AABBCollider2DComponent* a = ComponentManager::getComponent<AABBCollider2DComponent>(entities[i]);
				CircleCollider2DComponent* b = ComponentManager::getComponent<CircleCollider2DComponent>(entities[j]);
				if (checkCollision(a, b)) {
					std::cout << "AABB vs Circle collision detected\n";
				}
				else {
					a = ComponentManager::getComponent<AABBCollider2DComponent>(entities[j]);
					b = ComponentManager::getComponent<CircleCollider2DComponent>(entities[i]);
					if (checkCollision(a, b)) {
						std::cout << "Circle vs AABB collision detected\n";
					}
				}
			}
		}
	}

}