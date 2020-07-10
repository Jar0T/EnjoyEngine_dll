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
		for (std::map<std::uint32_t, std::vector<std::uint8_t>>::iterator it = _components.begin(); it != _components.end(); it++) {
			size_t typeSize = BaseECSComponent::getTypeSize(it->first);
			ECSComponentFreeFunction freefn = BaseECSComponent::getTypeFreeFunction(it->first);

			for (std::uint32_t i = 0; i < it->second.size(); i += typeSize) {
				freefn((BaseECSComponent*)&it->second[i]);
			}
		}

		for (std::uint32_t i = 0; i < _entities.size(); i++) {
			delete _entities[i];
		}
	}

	EntityHandle ECS::createEntity(BaseECSComponent* components, const std::uint32_t* componentIDs, size_t noComponents) {
		std::pair<std::uint32_t, std::vector<std::pair<std::uint32_t, std::uint32_t>>>* newEntity =
			new std::pair<std::uint32_t, std::vector<std::pair<std::uint32_t, std::uint32_t>>>();
		EntityHandle handle = (EntityHandle)newEntity;

		for (size_t i = 0; i < noComponents; i++) {
			// Check if component's ID is valid

			ECSComponentCreateFunction createfn = BaseECSComponent::getTypeCreateFunction(componentIDs[i]);
			std::pair<std::uint32_t, std::uint32_t> newPair;
			newPair.first = componentIDs[i];
			newPair.second = createfn(_components[componentIDs[i]], handle, &components[i]);
			newEntity->second.push_back(newPair);
		}

		newEntity->first = _entities.size();
		_entities.push_back(newEntity);

		return handle;
	}

	inline void ECS::addSystem(BaseECSSystem& system) {
		_systems.push_back(&system);
	}

}