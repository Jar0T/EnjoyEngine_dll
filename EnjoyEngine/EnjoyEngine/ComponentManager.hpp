#pragma once
#include <map>
#include <memory>

#include "Component.hpp"
#include "Entity.hpp"
#include "ComponentMap.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API ComponentManager {
	private:
		static ComponentManager* _componentManager;

		std::map<ComponentTypeID, std::shared_ptr<IComponentMap>> _componentMap{};

		ComponentManager() {};
		ComponentManager(const ComponentManager&) = delete;
		ComponentManager& operator=(const ComponentManager&) = delete;

	public:
		~ComponentManager() {};

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

		template<typename T>
		static void addComponent(EntityID entityID, T* component) {
			if (_componentManager == 0)
				_componentManager = new ComponentManager();

			_componentManager->getComponentMap<T>()->addComponent(entityID, component);
		}

		template<typename T>
		static T* getComponent(EntityID entityID) {
			if (_componentManager == 0)
				_componentManager = new ComponentManager();

			return _componentManager->getComponentMap<T>()->getComponent(entityID);
		}

		template<typename T>
		static void removeComponent(EntityID entityID) {
			if (_componentManager == 0)
				_componentManager = new ComponentManager();

			_componentManager->getComponentMap<T>()->removeComponent(entityID);
		}

		template<typename T>
		static bool hasComponent(EntityID entityID) {
			if (_componentManager == 0)
				_componentManager = new ComponentManager();

			if (_componentManager->getComponentMap<T>()->getMap().find(entityID) == _componentManager->getComponentMap<T>()->getMap().end())
				return false;
			return true;
		}

		static void deleteAllFromEntity(EntityID entityID) {
			if (_componentManager == 0)
				_componentManager = new ComponentManager();

			for (auto& a : _componentManager->_componentMap) {
				a.second->removeComponent(entityID);
			}
		}

	};
}
