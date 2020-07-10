#include "pch.h"

#include "ECSComponent.hpp"

namespace EE {
	std::vector<std::tuple< ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>> BaseECSComponent::componentTypes;

	std::uint32_t BaseECSComponent::registerComponentType(ECSComponentCreateFunction createfn, ECSComponentFreeFunction freefn, size_t size) {
		std::uint32_t componentTypeID = componentTypes.size();
		componentTypes.push_back(
			std::tuple< ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>(
				createfn, freefn, size
				)
		);
		return componentTypeID;
	}

	inline ECSComponentCreateFunction BaseECSComponent::getTypeCreateFunction(std::uint32_t id) {
		return std::get<0>(componentTypes[id]);
	}

	inline ECSComponentFreeFunction BaseECSComponent::getTypeFreeFunction(std::uint32_t id) {
		return std::get<1>(componentTypes[id]);
	}

	inline size_t BaseECSComponent::getTypeSize(std::uint32_t id) {
		return std::get<2>(componentTypes[id]);
	}

}