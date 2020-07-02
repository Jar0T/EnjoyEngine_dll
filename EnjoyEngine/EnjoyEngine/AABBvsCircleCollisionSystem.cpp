#include "pch.h"
#include "AABBvsCircleCollisionSystem.hpp"

namespace EE {
	bool AABBvsCircleCollisionSystem::checkCollision(std::shared_ptr<AABBCollider2DComponent> a, std::shared_ptr<CircleCollider2DComponent> b, Vector2D<float> pos1, Vector2D<float> pos2) {
		if (a->getStackLayer() == 0 && b->getStackLayer() == 0) {
			Vector2D<float> ab = pos1 - pos2;
			if (ab.x > a->size().x)
				ab.x = a->size().x;
			if (ab.x < 0)
				ab.x = 0;
			if (ab.y > a->size().y)
				ab.y = a->size().y;
			if (ab.y < 0)
				ab.y = 0;
			float distance = (ab - pos2).magnitude();
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
		std::shared_ptr<AABBCollider2DComponent> a;
		std::shared_ptr<CircleCollider2DComponent> b;
		std::shared_ptr<Transform2DComponent> t1;
		std::shared_ptr<Transform2DComponent> t2;
		Vector2D<float> separationVector;
		for (int i = 0; i < (int)entities.size() - 1; i++) {
			for (int j = i + 1; j < entities.size(); j++) {
				t1 = ComponentManager::getComponent<Transform2DComponent>(entities[i]);
				t2 = ComponentManager::getComponent<Transform2DComponent>(entities[j]);
				if (t1 && t2) {
					a = ComponentManager::getComponent<AABBCollider2DComponent>(entities[i]);
					b = ComponentManager::getComponent<CircleCollider2DComponent>(entities[j]);
					if (a && b) {
						if (checkCollision(a, b, t1->position(), t2->position())) {
							separationVector = t1->position() - t2->position();
							a->callHandler(*t2, separationVector);
							b->callHandler(*t1, separationVector * -1);
						}
					}
					else {
						a = ComponentManager::getComponent<AABBCollider2DComponent>(entities[j]);
						b = ComponentManager::getComponent<CircleCollider2DComponent>(entities[i]);
						if (a && b) {
							if (checkCollision(a, b, t2->position(), t1->position())) {
								separationVector = t2->position() - t1->position();
								a->callHandler(*t1, separationVector);
								b->callHandler(*t2, separationVector);
							}
						}
					}
				}
			}
		}
	}

}