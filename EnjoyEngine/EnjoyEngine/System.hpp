#pragma once

#include "Time.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	/// <summary>
	/// Base system class. All systems should inherit from it.
	/// </summary>
	class ENJOYENGINE_API System {
	public:
		System();
		virtual ~System();

		/// <summary>
		/// Called from SystemManager's update method
		/// </summary>
		virtual void update() = 0;

	private:

	};
}
