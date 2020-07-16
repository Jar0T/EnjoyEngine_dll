#include "pch.h"

#include "ECSComponent.hpp"

namespace EE {
	std::vector<std::tuple< ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>>* BaseECSComponent::componentTypes = 0;

	std::uint32_t BaseECSComponent::registerComponentType(ECSComponentCreateFunction createfn, ECSComponentFreeFunction freefn, size_t size) {
		if (componentTypes == nullptr) {
			componentTypes = new std::vector<std::tuple< ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>>;
		}
		std::uint32_t componentTypeID = componentTypes->size();
		componentTypes->push_back(
			std::tuple< ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>(
				createfn, freefn, size
				)
		);
		return componentTypeID;
	}

	ECSComponentCreateFunction BaseECSComponent::getTypeCreateFunction(std::uint32_t id) {
		return std::get<0>((*componentTypes)[id]);
	}

	ECSComponentFreeFunction BaseECSComponent::getTypeFreeFunction(std::uint32_t id) {
		return std::get<1>((*componentTypes)[id]);
	}

	size_t BaseECSComponent::getTypeSize(std::uint32_t id) {
		return std::get<2>((*componentTypes)[id]);
	}

	bool BaseECSComponent::isTypeValid(std::uint32_t id) {
		return id < componentTypes->size();
	}

}