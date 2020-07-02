#pragma once

#include <vector>

#include "System.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	/// <summary>
	/// Class managing systems. One instance should be created for every state
	/// </summary>
	class ENJOYENGINE_API SystemManager {
	private:
		std::vector<std::shared_ptr<System>> _systemsVector;

	public:
		SystemManager();
		~SystemManager();

		/// <summary>
		/// Calls every system's update method.
		/// </summary>
		void update();

		/// <summary>
		/// Creates and adds new state to manager.
		/// </summary>
		/// <typeparam name="T">Derived state class</typeparam>
		template<typename T>
		void registerSystem() {
			_systemsVector.push_back(std::make_shared<T>());
		}

	};
}