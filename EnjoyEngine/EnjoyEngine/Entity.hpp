#pragma once
#include <iostream>
#include "ComponentManager.hpp"
#include "EntityManager.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	using EntityID = std::uint32_t;

	/// <summary>
	/// Entity class for managing every entitie's component
	/// </summary>
	class ENJOYENGINE_API  Entity {
	public:
		Entity();
		virtual ~Entity();

		/// <summary>
		/// ID assigned to this specific entity
		/// </summary>
		EntityID entityID;

		/// <summary>
		/// Adds new component to entity
		/// </summary>
		/// <typeparam name="T">Derived component class</typeparam>
		/// <param name="component">Component pointer</param>
		template<typename T>
		void addComponent(T* component) {
			ComponentManager::addComponent<T>(entityID, component);
		}

		/// <summary>
		/// Checks if entity has component
		/// </summary>
		/// <typeparam name="T">Derived component class</typeparam>
		/// <returns><c>true</c> if entity has component, <c>false</c> otherwise</returns>
		template<typename T>
		bool hasComponent() {
			return ComponentManager::hasComponent<T>(entityID);
		}

		/// <summary>
		/// Getter for entitie's specific component
		/// </summary>
		/// <typeparam name="T">Derived component class</typeparam>
		/// <returns>Reference to component</returns>
		template<typename T>
		T& getComponent() {
			return *ComponentManager::getComponent<T>(entityID);
		}

		/// <summary>
		/// Removes component from entity
		/// </summary>
		/// <typeparam name="T">Derived component class</typeparam>
		template<typename T>
		void removeComponent() {
			ComponentManager::removeComponent<T>(entityID);
		}
	};
}
