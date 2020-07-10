#include "pch.h"

#include "ecs.hpp"

namespace EE {
	inline std::pair<std::uint32_t, std::vector<std::pair<std::uint32_t, std::uint32_t>>>* ECS::handleToRawType(EntityHandle entityHandle) {
		return (std::pair<std::uint32_t, std::vector<std::pair<std::uint32_t, std::uint32_t>>>*)entityHandle;
	}

	inline std::vector<std::pair<std::uint32_t, std::uint32_t>>& ECS::handleToEntity(EntityHandle entityHandle) {
		return handleToRawType(entityHandle)->second;
	}

	inline std::uint32_t ECS::handleToEntityIndex(EntityHandle entityHandle) {
		return handleToRawType(entityHandle)->first;
	}

	ECS::ECS() {}

	ECS::~ECS() {
		
	}

	inline void ECS::addSystem(BaseECSSystem& system) {
		_systems.push_back(&system);
	}

}