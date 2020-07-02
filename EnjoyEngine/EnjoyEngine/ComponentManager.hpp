#pragma once
#include <map>
#include <memory>

#include "Component.hpp"
#include "ComponentMap.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	/// <summary>
	/// Component manager class. This class should never be used by user
	/// </summary>
	class ENJOYENGINE_API ComponentManager {
	private:
		static ComponentManager* _componentManager;

		std::map<ComponentTypeID, std::shared_ptr<IComponentMap>> _componentMap{};

		ComponentManager() {};
		ComponentManager(const ComponentManager&) = delete;
		ComponentManager& operator=(const ComponentManager&) = delete;

	public:
		~ComponentManager() {};

		/// <summary>
		/// Method for getting map of all components of specific type
		/// </summary>
		/// <typeparam name="T">Derived component class</typeparam>
		/// <returns><c>std::shared_ptr</c> to map of components of T type</returns>
		template<typename T>
		static std::shared_ptr<ComponentMap<T>> getComponentMap() {
			if (_componentManager == 0)
				_componentManager = new ComponentManager();

			ComponentTypeID typeID = getComponentTypeID<T>();

			if (_componentManager->_componentMap.find(typeID) == _componentManager->_componentMap.end()) {
				_componentManager->_componentMap[typeID] = std::make_shared<ComponentMap<T>>();
			}

			return std::static_pointer_cast<ComponentMap<T>>(_componentManager->_componentMap[typeID]);
		}

		/// <summary>
		/// Adds new component to map
		/// </summary>
		/// <typeparam name="T">Derived component class</typeparam>
		/// <param name="entityID">ID of entity that component should be added to</param>
		/// <param name="component">Pointer to component</param>
		template<typename T>
		static void addComponent(std::uint32_t entityID, std::shared_ptr<T> component) {
			if (_componentManager == 0)
				_componentManager = new ComponentManager();

			_componentManager->getComponentMap<T>()->addComponent(entityID, component);
		}

		/// <summary>
		/// Getter for entitie's component
		/// </summary>
		/// <typeparam name="T">Derived component class</typeparam>
		/// <param name="entityID">ID of entity</param>
		/// <returns>Entitie's component pointer</returns>
		template<typename T>
		static std::shared_ptr<T> getComponent(std::uint32_t entityID) {
			if (_componentManager == 0)
				_componentManager = new ComponentManager();

			return _componentManager->getComponentMap<T>()->getComponent(entityID);
		}

		/// <summary>
		/// Removes component from entity
		/// </summary>
		/// <typeparam name="T">Derived component class</typeparam>
		/// <param name="entityID">ID of entity</param>
		template<typename T>
		static void removeComponent(std::uint32_t entityID) {
			if (_componentManager == 0)
				_componentManager = new ComponentManager();

			_componentManager->getComponentMap<T>()->removeComponent(entityID);
		}

		/// <summary>
		/// Checks if entity has component
		/// </summary>
		/// <typeparam name="T">Derived component class</typeparam>
		/// <param name="entityID">ID of entity</param>
		/// <returns><c>true</c> if entity has component, <c>false</c> otherwise</returns>
		template<typename T>
		static bool hasComponent(std::uint32_t entityID) {
			if (_componentManager == 0)
				_componentManager = new ComponentManager();

			if (_componentManager->getComponentMap<T>()->getMap().find(entityID) == _componentManager->getComponentMap<T>()->getMap().end())
				return false;
			return true;
		}

		/// <summary>
		/// Deletes every component from specific entity
		/// </summary>
		/// <param name="entityID">ID of entity</param>
		static void deleteAllFromEntity(std::uint32_t entityID) {
			if (_componentManager == 0)
				_componentManager = new ComponentManager();

			for (auto& a : _componentManager->_componentMap) {
				a.second->removeComponent(entityID);
			}
		}

	};
}
