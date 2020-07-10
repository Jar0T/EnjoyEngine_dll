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
		BaseECSComponent* getComponetnInternal(std::vector<std::pair<std::uint32_t, std::uint32_t>>& entityComponents, std::uint32_t id);

		void updateSystemWithMultipleComponents(uint32_t index, const std::vector<std::uint32_t>& componentTypes, std::vector<BaseECSComponent*>& componentsVector);

	public:
		ECS();
		~ECS();
		ECS(const ECS&) = delete;
		ECS& operator=(const ECS&) = delete;

		// Entity methods
		EntityHandle createEntity(BaseECSComponent* components, const std::uint32_t* componentIDs, size_t noComponents);
		void destroyEntity(EntityHandle entityHandle);

		// Component methods
		template<class Component>
		inline void addComponent(EntityHandle entityHandle, Component* component);
		template<class Component>
		void removeComponent(EntityHandle entityHandle);
		template<class Component>
		Component* getComponent(EntityHandle entityHandle);

		// System methods
		inline void addSystem(BaseECSSystem& system);
		void updateSystems();
		bool removeSystem(BaseECSSystem& system);

	};
	
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
		/*return (Component*)*/getComponetnInternal(handleToEntity(entityHandle), Component::ID);
	}

}
