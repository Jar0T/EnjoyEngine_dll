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

		void removeComponentInternal(std::uint32_t componentID, std::uint32_t index);

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
		void addComponent(EntityHandle entityHandle, Component* component);
		template<class Component>
		void removeComponent(EntityHandle entityHandle);
		template<class Component>
		void getComponent(EntityHandle entityHandle);

		// System methods
		inline void addSystem(BaseECSSystem& system);
		void updateSystems();
		void removeSystem(BaseECSSystem& system);

	};
}
