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
		for (auto& entity : EntityManager::getEntities()) {
			Transform2DComponent* transform = ComponentManager::getComponent<Transform2DComponent>(entity);
			if (transform) {
				if (transform->getStackLayer() == 0) {
					if (transform->grounded()) {
						friction = (transform->velocity() * -1.f);
						friction.setMagnitude(9.81f * transform->frictionCoefficient());
						transform->acceleration() += friction * deltaTime;
						friction.setMagnitude(0.f);
					}
					transform->velocity() += transform->acceleration() * deltaTime;
					transform->position() += transform->velocity() * deltaTime;
					transform->acceleration().setMagnitude(0.f);
				}
			}
		}
	}

}
