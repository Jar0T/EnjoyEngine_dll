#pragma once

#include <map>

#include "ECSComponent.hpp"
#include "ECSSystem.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API ECS {
	private:
		std::vector<BaseECSSystem*> _systems;
		std::map<std::uint32_t, std::vector<std::uint8_t>> _components;
		std::vector<std::pair<std::uint32_t, std::vector<std::pair<std::uint32_t, std::uint32_t>>>*> _entities;

		inline std::pair<std::uint32_t, std::vector<std::pair<std::uint32_t, std::uint32_t>>>* handleToRawType(EntityHandle entityHandle);
		inline std::vector<std::pair<std::uint32_t, std::uint32_t>>& handleToEntity(EntityHandle entityHandle);
		inline std::uint32_t handleToEntityIndex(EntityHandle entityHandle);

		void deleteComponent(std::uint32_t componentID, std::uint32_t index);
		bool removeComponentInternal(EntityHandle entityHandle, std::uint32_t componentID);
		void addComponentInternal(EntityHandle handle, std::vector<std::pair<std::uint32_t, std::uint32_t>>& entity, std::uint32_t id, BaseECSComponent* component);
		BaseECSComponent* getComponetnInternal(std::vector<std::pair<std::uint32_t, std::uint32_t>>& entityComponents, std::vector<uint8_t>& components, std::uint32_t id);

		void updateSystemWithMultipleComponents(uint32_t index, const std::vector<std::uint32_t>& componentTypes, std::vector<BaseECSComponent*>& baseComponentsVector, std::vector<std::vector<uint8_t>*>& componentsVector);
		size_t findLeastCommonComponent(const std::vector<uint32_t>& componentTypes, std::vector<std::uint32_t>& componetnFlags);

	public:
		ECS();
		~ECS();
		ECS(const ECS&) = delete;
		ECS& operator=(const ECS&) = delete;

		// Entity methods
		EntityHandle createEntity(BaseECSComponent** components, const std::uint32_t* componentIDs, size_t noComponents);
		template<class A, class B>
		EntityHandle createEntity(A& c1, B& c2);
		template<class A, class B, class C>
		EntityHandle createEntity(A& c1, B& c2, C& c3);
		template<class A, class B, class C, class D>
		EntityHandle createEntity(A& c1, B& c2, C& c3, D& c4);
		template<class A, class B, class C, class D, class E>
		EntityHandle createEntity(A& c1, B& c2, C& c3, D& c4, E& c5);
		void destroyEntity(EntityHandle entityHandle);

		// Component methods
		template<class Component>
		inline void addComponent(EntityHandle entityHandle, Component* component);
		template<class Component>
		void removeComponent(EntityHandle entityHandle);
		template<class Component>
		Component* getComponent(EntityHandle entityHandle);

		// System methods
		inline bool addSystem(BaseECSSystem& system);
		void updateSystems();
		bool removeSystem(BaseECSSystem& system);

	};
	
	template<class A, class B>
	inline EntityHandle ECS::createEntity(A& c1, B& c2) {
		BaseECSComponent* components[] = { &c1, &c2 };
		uint32_t componentIDs[] = { A::ID, B::ID };
		return createEntity(components, componentIDs, 2);
	}

	template<class A, class B, class C>
	inline EntityHandle ECS::createEntity(A& c1, B& c2, C& c3) {
		BaseECSComponent* components[] = { &c1, &c2, &c3 };
		uint32_t componentIDs[] = { A::ID, B::ID, C::ID };
		return createEntity(components, componentIDs, 3);
	}

	template<class A, class B, class C, class D>
	inline EntityHandle ECS::createEntity(A& c1, B& c2, C& c3, D& c4) {
		BaseECSComponent* components[] = { &c1, &c2, &c3, &c4 };
		uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID };
		return createEntity(components, componentIDs, 4);
	}

	template<class A, class B, class C, class D, class E>
	inline EntityHandle ECS::createEntity(A& c1, B& c2, C& c3, D& c4, E& c5) {
		BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5 };
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
