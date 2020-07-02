// Precompiled headers
#include "pch.h"

// System headers

// My headers
#include "EntityManager.hpp"

namespace EE {
	EntityManager* EntityManager::_entityManager = 0;

	EntityManager::EntityManager(std::uint32_t maxIDs) {
		for (std::uint32_t i = 0; i < maxIDs; i++) {
			_freeIDs.push(i);
		}
	}

	EntityManager::~EntityManager() {}

	void EntityManager::init(std::uint32_t maxIDs) {
		if (_entityManager == 0)
			_entityManager = new EntityManager(maxIDs);
	}

	std::uint32_t EntityManager::getID() {
		if (_entityManager == 0)
			return -1;

		std::uint32_t ID = _entityManager->_freeIDs.front();
		_entityManager->_freeIDs.pop();
		_entityManager->entities.push_back(ID);
		return ID;
	}

	void EntityManager::entityDestroyed(std::uint32_t ID) {
		if (_entityManager == 0)
			return;

		_entityManager->entities.erase(std::remove(_entityManager->entities.begin(), _entityManager->entities.end(), ID), _entityManager->entities.end());
		_entityManager->_freeIDs.push(ID);
	}

	std::vector<std::uint32_t> EntityManager::getEntities() {
		if (_entityManager == 0) {
			// TO DO throw exception
		}

		return _entityManager->entities;
	}
}
