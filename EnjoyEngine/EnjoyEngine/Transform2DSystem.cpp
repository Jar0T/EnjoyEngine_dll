#include "pch.h"
#include "Transform2DSystem.hpp"

namespace EE {
	Transform2DSystem::Transform2DSystem() {

	}
	
	Transform2DSystem::~Transform2DSystem() {

	}

	void Transform2DSystem::update() {
		float deltaTime = Time::deltaTime();
		for (auto& entity : EntityManager::getEntities()) {
			Transform2DComponent* transform = ComponentManager::getComponent<Transform2DComponent>(entity);
			if (transform) {
				if (transform->getStackLayer() == 0) {
					transform->position() += transform->velocity() * deltaTime;
					transform->velocity() += transform->acceleration() * deltaTime;
					transform->acceleration().setMagnitude(0.f);
				}
			}
		}
	}

}
