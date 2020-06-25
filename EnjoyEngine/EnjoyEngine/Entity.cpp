// Precompiled headers
#include "pch.h"

// System headers

// My headers
#include "Entity.hpp"

namespace EE {
	Entity::Entity() {
		entityID = EntityManager::getID();
	}

	Entity::~Entity() {
		ComponentManager::deleteAllFromEntity(entityID);
		EntityManager::entityDestroyed(entityID);
	}
}
