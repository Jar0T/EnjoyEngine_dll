#include "pch.h"
#include "Transform2DSystem.hpp"

namespace EE {
	Transform2DSystem::Transform2DSystem() {

	}
	
	Transform2DSystem::~Transform2DSystem() {

	}

	void Transform2DSystem::update() {
		float deltaTime = Time::deltaTime();
		Vector2D<float> friction{ 0.f, 0.f };
		Vector2D<float> gravity{ 0.f, 9.81f };
		for (auto& entity : EntityManager::getEntities()) {
			Transform2DComponent* transform = ComponentManager::getComponent<Transform2DComponent>(entity);
			if (transform) {
				if (transform->getStackLayer() == 0) {
					if (transform->grounded()) {
						friction = (transform->velocity() * -1).normalize();
						friction.setMagnitude(9.81f * 0.3f);
						transform->acceleration() += friction * deltaTime;
						friction.setMagnitude(0.f);
					}
					if (transform->affectedByGravity() && !transform->grounded()) {
						transform->acceleration() += gravity * deltaTime;
					}
					transform->velocity() += transform->acceleration() * deltaTime;
					transform->position() += transform->velocity() * deltaTime;
					transform->acceleration().setMagnitude(0.f);
				}
			}
		}
	}

}
