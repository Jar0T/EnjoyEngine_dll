#pragma once
#include <map>
#include <memory>
#include "IComponentMap.hpp"

namespace EE {
	/// <summary>
	/// Class storing all components of specific type
	/// </summary>
	/// <typeparam name="T">Derived component class</typeparam>
	template<typename T>
	class ComponentMap : public IComponentMap {
	private:
		std::map<std::uint32_t, std::shared_ptr<T>> _componentMap;

	public:
		/// <summary>
		/// Gets specific component from component map
		/// </summary>
		/// <param name="entityID">ID of entity possessing component</param>
		/// <returns>Component pointer</returns>
		std::shared_ptr<T> getComponent(std::uint32_t entityID) {
			return _componentMap[entityID];
		}

		/// <summary>
		/// Adds Component to specific entity
		/// </summary>
		/// <param name="entityID">ID of entity component should be added to</param>
		/// <param name="component">Pointer to component</param>
		void addComponent(std::uint32_t entityID, std::shared_ptr<T> component) {
			_componentMap[entityID] = component;
		}

		/// <summary>
		/// Removes component from specific entity
		/// </summary>
		/// <param name="entityID">ID of entity which component should be removed</param>
		void removeComponent(std::uint32_t entityID) override {
			//delete _componentMap[entityID];
			_componentMap.erase(entityID);
		}

		/// <summary>
		/// Getter for full map of components
		/// </summary>
		/// <returns>Reference to <c>std::map</c> of components</returns>
		std::map<std::uint32_t, std::shared_ptr<T>>& getMap() {
			return _componentMap;
		}

	};
}
