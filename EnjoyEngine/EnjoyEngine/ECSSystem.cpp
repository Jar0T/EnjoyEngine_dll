#include "pch.h"

#include "ECSSystem.hpp"

namespace EE {
	BaseECSSystem::BaseECSSystem(const std::vector<std::uint32_t>& componentTypes) : _componentTypes(componentTypes) {}

	void BaseECSSystem::updateComponents(BaseECSComponent** components) {}

	const std::vector<std::uint32_t>& BaseECSSystem::getComponentTypes() {
		return _componentTypes;
	}

}