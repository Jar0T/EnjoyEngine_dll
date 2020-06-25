// Precompiled headers
#include "pch.h"

// System headers

// My headers
#include "SystemManager.hpp"

namespace EE {
	SystemManager::SystemManager() {}

	SystemManager::~SystemManager() {}

	void SystemManager::update() {
		for (auto& system : _systemsVector) {
			system->update();
		}
	}
}
