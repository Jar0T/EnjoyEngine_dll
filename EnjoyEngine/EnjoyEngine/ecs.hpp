#pragma once

#include <map>

#include "ECSComponent.hpp"
#include "ECSSystem.hpp"


namespace EE {
	class ECS {
	private:
		std::vector<BaseECSSystem*> _systems;
		std::map<std::uint32_t, std::vector<std::uint8_t>> _components;
		std::vector<std::pair<std::uint32_t, std::vector<std::pair<std::uint32_t, std::uint32_t>>>*> _entities;

		inline std::pair<std::uint32_t, std::vector<std::pair<std::uint32_t, std::uint32_t>>>* handleToRawType(EntityHandle entityHandle) {
			return (std::pair<std::uint32_t, std::vector<std::pair<std::uint32_t, std::uint32_t>>>*)entityHandle;
		}
		inline std::vector<std::pair<std::uint32_t, std::uint32_t>>& handleToEntity(EntityHandle entityHandle) {
			return handleToRawType(entityHandle)->second;
		}
		inline std::uint32_t handleToEntityIndex(EntityHandle entityHandle) {
			return handleToRawType(entityHandle)->first;
		}

		void deleteComponent(std::uint32_t componentID, std::uint32_t index) {
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
		bool removeComponentInternal(EntityHandle entityHandle, std::uint32_t componentID) {
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
		void addComponentInternal(EntityHandle handle, std::vector<std::pair<std::uint32_t, std::uint32_t>>& entity, std::uint32_t id, BaseECSComponent* component) {
			ECSComponentCreateFunction createfn = BaseECSComponent::getTypeCreateFunction(id);
			std::pair<std::uint32_t, std::uint32_t> newPair;
			newPair.first = id;
			newPair.second = createfn(_components[id], handle, component);
			entity.push_back(newPair);
		}
		BaseECSComponent* getComponetnInternal(std::vector<std::pair<std::uint32_t, std::uint32_t>>& entityComponents, std::vector<uint8_t>& components, std::uint32_t id) {
			for (std::uint32_t i = 0; i < entityComponents.size(); i++) {
				if (id == entityComponents[i].first) {
					return (BaseECSComponent*)&_components[id][entityComponents[i].second];
				}
			}
			return nullptr;
		}

		void updateSystemWithMultipleComponents(uint32_t index, const std::vector<std::uint32_t>& componentTypes, std::vector<BaseECSComponent*>& baseComponentsVector, std::vector<std::vector<uint8_t>*>& componentsVector) {
			std::vector<std::uint32_t> componetnFlags = _systems[index]->getComponentFlags();

			baseComponentsVector.resize(std::max(baseComponentsVector.size(), componentTypes.size()));
			componentsVector.resize(std::max(componentsVector.size(), componentTypes.size()));

			for (size_t i = 0; i < componentTypes.size(); i++) {
				componentsVector[i] = &_components[componentTypes[i]];
			}

			size_t minSizeIndex = findLeastCommonComponent(componentTypes, componetnFlags);

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
					if (baseComponentsVector[j] == nullptr && ((componetnFlags[j] & (uint32_t)BaseECSSystem::Flags::OPTIONAL_COMPONENT) == 0)) {
						isValid = false;
						break;
					}
				}

				if (isValid) {
					_systems[index]->updateComponents(&baseComponentsVector[0]);
				}
			}
		}
		size_t findLeastCommonComponent(const std::vector<uint32_t>& componentTypes, std::vector<std::uint32_t>& componetnFlags) {
			size_t minSize = (size_t)-1;
			size_t minIndex = (size_t)-1;

			for (size_t i = 0; i < componentTypes.size(); i++) {
				if ((componetnFlags[i] & (uint32_t)BaseECSSystem::Flags::OPTIONAL_COMPONENT) != 0) {
					continue;
				}
				size_t typeSize = BaseECSComponent::getTypeSize(componentTypes[i]);
				size_t size = _components[componentTypes[i]].size() / typeSize;
				if (size <= minSize) {
					minSize = size;
					minIndex = i;
				}
			}

			return minIndex;
		}

	public:
		ECS() {}
		~ECS() {
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
		ECS(const ECS&) = delete;
		ECS& operator=(const ECS&) = delete;

		// Entity methods
		EntityHandle createEntity(BaseECSComponent** components, const std::uint32_t* componentIDs, size_t noComponents) {
			std::pair<std::uint32_t, std::vector<std::pair<std::uint32_t, std::uint32_t>>>* newEntity =
				new std::pair<std::uint32_t, std::vector<std::pair<std::uint32_t, std::uint32_t>>>();
			EntityHandle handle = (EntityHandle)newEntity;

			for (size_t i = 0; i < noComponents; i++) {
				// Check if component's ID is valid
				if (!BaseECSComponent::isTypeValid(componentIDs[i])) {
					delete newEntity;
					return nullptr;
				}

				addComponentInternal(handle, newEntity->second, componentIDs[i], components[i]);
			}

			newEntity->first = _entities.size();
			_entities.push_back(newEntity);

			return handle;
		}
		template<class A>
		EntityHandle createEntity();
		template<class A, class B>
		EntityHandle createEntity();
		template<class A, class B, class C>
		EntityHandle createEntity();
		template<class A, class B, class C, class D>
		EntityHandle createEntity();
		template<class A, class B, class C, class D, class E>
		EntityHandle createEntity();
		void destroyEntity(EntityHandle entityHandle) {
			std::vector<std::pair<std::uint32_t, std::uint32_t>>& entity = handleToEntity(entityHandle);
			for (size_t i = 0; i < entity.size(); i++) {
				deleteComponent(entity[i].first, entity[i].second);
			}
			size_t dstIndex = handleToEntityIndex(entityHandle);
			size_t srcIndex = _entities.size() - 1;
			delete _entities[dstIndex];
			_entities[dstIndex] = _entities[srcIndex];
			_entities[dstIndex]->first = dstIndex;
			_entities.pop_back();
		}

		// Component methods
		template<class Component>
		inline void addComponent(EntityHandle entityHandle, Component* component);
		template<class Component>
		void removeComponent(EntityHandle entityHandle);
		template<class Component>
		Component* getComponent(EntityHandle entityHandle);

		// System methods
		inline bool addSystem(BaseECSSystem& system) {
			if (system.isValid()) {
				_systems.push_back(&system);
				return true;
			}
			return false;
		}
		void updateSystems() {
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
		bool removeSystem(BaseECSSystem& system) {
			for (size_t i = 0; i < _systems.size(); i++) {
				if (&system == _systems[i]) {
					_systems.erase(_systems.begin() + i);
					return true;
				}
			}
			return false;
		}

	};
	
	template<class A>
	inline EntityHandle ECS::createEntity() {
		A* a = new A;
		BaseECSComponent* components[] = { a };
		uint32_t componentIDs[] = { A::ID };
		return createEntity(components, componentIDs, 1);
	}

	template<class A, class B>
	inline EntityHandle ECS::createEntity() {
		A* a = new A;
		B* b = new B;
		BaseECSComponent* components[] = { a, b };
		uint32_t componentIDs[] = { A::ID, B::ID };
		return createEntity(components, componentIDs, 2);
	}

	template<class A, class B, class C>
	inline EntityHandle ECS::createEntity() {
		A* a = new A;
		B* b = new B;
		C* c = new C;
		BaseECSComponent* components[] = { a, b, c };
		uint32_t componentIDs[] = { A::ID, B::ID, C::ID };
		return createEntity(components, componentIDs, 3);
	}

	template<class A, class B, class C, class D>
	inline EntityHandle ECS::createEntity() {
		A* a = new A;
		B* b = new B;
		C* c = new C;
		D* d = new D;
		BaseECSComponent* components[] = { a, b, c, d };
		uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID };
		return createEntity(components, componentIDs, 4);
	}

	template<class A, class B, class C, class D, class E>
	inline EntityHandle ECS::createEntity() {
		A* a = new A;
		B* b = new B;
		C* c = new C;
		D* d = new D;
		E* e = new E;
		BaseECSComponent* components[] = { a, b, c, d, e };
		uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID, D::ID };
		return createEntity(components, componentIDs, 5);
	}

	template<class Component>
	inline void ECS::addComponent(EntityHandle entityHandle, Component* component) {
		addComponentInternal(entityHandle, handleToEntity(entityHandle), Component::ID, component);
	}

	template<class Component>
	inline void ECS::removeComponent(EntityHandle entityHandle) {
		removeComponentInternal(entityHandle, Component::ID);
	}

	template<class Component>
	inline Component* ECS::getComponent(EntityHandle entityHandle) {
		return (Component*)getComponetnInternal(handleToEntity(entityHandle), _components[Component::ID], Component::ID);
	}

}
