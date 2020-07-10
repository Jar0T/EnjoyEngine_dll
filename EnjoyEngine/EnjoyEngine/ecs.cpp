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

	void ECS::deleteComponent(std::uint32_t componentID, std::uint32_t index) {
		std::vector<std::uint8_t>& vector = _components[componentID];
		ECSComponentFreeFunction freefn = BaseECSComponent::getTypeFreeFunction(componentID);
		size_t typeSize = BaseECSComponent::getTypeSize(componentID);
		size_t srcIndex = vector.size() - typeSize;

		BaseECSComponent* srcComponent = (BaseECSComponent*)&vector[srcIndex];
		BaseECSComponent* dstComponent = (BaseECSComponent*)&vector[index];
		freefn(dstComponent);

		if (index == srcIndex) {
			vector.resize(srcIndex);
			return;
		}

		std::memcpy(dstComponent, srcComponent, typeSize);

		std::vector<std::pair<std::uint32_t, std::uint32_t>>& entityComponents = handleToEntity(srcComponent->entity);

		for (std::uint32_t i = 0; i < entityComponents.size(); i++) {
			if (componentID == entityComponents[i].first && srcIndex == entityComponents[i].second) {
				entityComponents[i].second = index;
				break;
			}
		}

		vector.resize(srcIndex);
	}

	bool ECS::removeComponentInternal(EntityHandle entityHandle, std::uint32_t componentID) {
		std::vector<std::pair<std::uint32_t, std::uint32_t>>& entityComponents = handleToEntity(entityHandle);
		for (size_t i = 0; i < entityComponents.size(); i++) {
			if (componentID == entityComponents[i].first) {
				deleteComponent(entityComponents[i].first, entityComponents[i].second);
				size_t srcIndex = entityComponents.size() - 1;
				size_t dstIndex = i;
				entityComponents[dstIndex] = entityComponents[srcIndex];
				entityComponents.pop_back();
				return true;
			}
		}

		return false;
	}

	void ECS::addComponentInternal(EntityHandle handle, std::vector<std::pair<std::uint32_t, std::uint32_t>>& entity, std::uint32_t id, BaseECSComponent* component) {
		ECSComponentCreateFunction createfn = BaseECSComponent::getTypeCreateFunction(id);
		std::pair<std::uint32_t, std::uint32_t> newPair;
		newPair.first = id;
		newPair.second = createfn(_components[id], handle, component);
		entity.push_back(newPair);
	}

	BaseECSComponent* ECS::getComponetnInternal(std::vector<std::pair<std::uint32_t, std::uint32_t>>& entityComponents, std::vector<uint8_t>& components, std::uint32_t id) {
		for (std::uint32_t i = 0; i < entityComponents.size(); i++) {
			if (id == entityComponents[i].first) {
				return (BaseECSComponent*)&_components[id][entityComponents[i].second];
			}
		}
		return nullptr;
	}

	void ECS::updateSystemWithMultipleComponents(uint32_t index, const std::vector<std::uint32_t>& componentTypes, std::vector<BaseECSComponent*>& baseComponentsVector, std::vector<std::vector<uint8_t>*>& componentsVector) {
		baseComponentsVector.resize(std::max(baseComponentsVector.size(), componentTypes.size()));
		componentsVector.resize(std::max(componentsVector.size(), componentTypes.size()));

		for (size_t i = 0; i < componentTypes.size(); i++) {
			componentsVector[i] = &_components[componentTypes[i]];
		}

		size_t minSizeIndex = findLeastCommonComponent(componentTypes);

		size_t typeSize = BaseECSComponent::getTypeSize(componentTypes[minSizeIndex]);
		std::vector<uint8_t>& components = *componentsVector[minSizeIndex];
		for (size_t i = 0; i < components.size(); i += typeSize) {
			baseComponentsVector[minSizeIndex] = (BaseECSComponent*)&components[i];
			std::vector<std::pair<std::uint32_t, std::uint32_t>>& entityComponents = handleToEntity(baseComponentsVector[minSizeIndex]->entity);

			bool isValid = true;
			for (size_t j = 0; j < componentTypes.size(); j++) {
				if (j == minSizeIndex) {
					continue;
				}
				baseComponentsVector[j] = getComponetnInternal(entityComponents, *componentsVector[j], componentTypes[j]);
				if (baseComponentsVector[j] == nullptr) {
					isValid = false;
					break;
				}
			}

			if (isValid) {
				_systems[index]->updateComponents(&baseComponentsVector[0]);
			}
		}
	}

	size_t ECS::findLeastCommonComponent(const std::vector<uint32_t>& componentTypes) {
		size_t minSize = _components[componentTypes[0]].size() / BaseECSComponent::getTypeSize(componentTypes[0]);
		size_t minIndex = 0;

		for (size_t i = 1; i < componentTypes.size(); i++) {
			size_t typeSize = BaseECSComponent::getTypeSize(componentTypes[i]);
			size_t size = _components[componentTypes[i]].size() / typeSize;
			if (size < minSize) {
				minSize = size;
			}
		}

		return minIndex;
	}

	ECS::ECS() {}

	ECS::~ECS() {
		for (std::map<std::uint32_t, std::vector<std::uint8_t>>::iterator it = _components.begin(); it != _components.end(); it++) {
			size_t typeSize = BaseECSComponent::getTypeSize(it->first);
			ECSComponentFreeFunction freefn = BaseECSComponent::getTypeFreeFunction(it->first);

			for (size_t i = 0; i < it->second.size(); i += typeSize) {
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
			if (!BaseECSComponent::isTypeValid(componentIDs[i])) {
				delete newEntity;
				return nullptr;
			}

			addComponentInternal(handle, newEntity->second, componentIDs[i], &components[i]);
		}

		newEntity->first = _entities.size();
		_entities.push_back(newEntity);

		return handle;
	}

	void ECS::destroyEntity(EntityHandle entityHandle) {
		std::vector<std::pair<std::uint32_t, std::uint32_t>>& entity = handleToEntity(entityHandle);
		for (size_t i = 0; i < entity.size(); i++) {
			deleteComponent(entity[i].first, entity[i].second);
		}
		size_t dstIndex = handleToEntityIndex(entityHandle);
		size_t srcIndex = _entities.size() - 1;
		delete _entities[dstIndex];
		_entities[dstIndex] = _entities[srcIndex];
		_entities.pop_back();
	}

	inline void ECS::addSystem(BaseECSSystem& system) {
		_systems.push_back(&system);
	}

	void ECS::updateSystems() {
		std::vector<BaseECSComponent*> baseComponentsVector;
		std::vector<std::vector<uint8_t>*> componentsVector;
		for (size_t i = 0; i < _systems.size(); i++) {
			const std::vector<std::uint32_t>& componentTypes = _systems[i]->getComponentTypes();
			if (componentTypes.size() == 1) {
				size_t typeSize = BaseECSComponent::getTypeSize(componentTypes[0]);
				std::vector<uint8_t>& componetns = _components[componentTypes[0]];
				for (size_t j = 0; j < componetns.size(); j += typeSize) {
					BaseECSComponent* component = (BaseECSComponent*)&componetns[j];
					_systems[i]->updateComponents(&component);
				}
			}
			else {
				updateSystemWithMultipleComponents(i, componentTypes, baseComponentsVector, componentsVector);
			}
		}
	}

	bool ECS::removeSystem(BaseECSSystem& system) {
		for (size_t i = 0; i < _systems.size(); i++) {
			if (&system == _systems[i]) {
				_systems.erase(_systems.begin() + i);
				return true;
			}
		}
		return false;
	}

}