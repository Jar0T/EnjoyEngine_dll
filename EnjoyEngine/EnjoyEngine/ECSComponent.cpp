#include "pch.h"

#include "ECSComponent.hpp"

namespace EE {
	std::vector<std::tuple< ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>>* BaseECSComponent::componentTypes = 0;
}