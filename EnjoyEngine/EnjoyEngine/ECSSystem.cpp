#include "pch.h"

#include "ECSSystem.hpp"

namespace EE {
	void BaseECSSystem::addComponentType(uint32_t componetnType, Flags componentFlag) {
		_componentTypes.push_back(componetnType);
		_componetnFlags.push_back((uint32_t)componentFlag);
	}

	BaseECSSystem::BaseECSSystem() {}

	void BaseECSSystem::updateComponents(BaseECSComponent** components) {}

	const std::vector<std::uint32_t>& BaseECSSystem::getComponentTypes() { return _componentTypes; };

	const std::vector<uint32_t>& BaseECSSystem::getComponentFlags() { return _componetnFlags; };

	bool BaseECSSystem::isValid() {
		for (size_t i = 0; i < _componetnFlags.size(); i++) {
			if ((_componetnFlags[i] & (uint32_t)BaseECSSystem::Flags::OPTIONAL_COMPONENT) == 0) {
				return true;
			}
		}
		return false;
	}
}