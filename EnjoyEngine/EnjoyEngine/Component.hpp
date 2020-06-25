#pragma once
#include <iostream>

namespace EE {
	using ComponentTypeID = std::uint32_t;

	/// <summary>
	/// Function to get ID specific to every derived Component class.
	/// Should never be used
	/// </summary>
	/// <returns>New component type's ID</returns>
	inline ComponentTypeID getComponentTypeID() {
		static ComponentTypeID lastID = 0;
		return lastID++;
	}

	/// <summary>
	/// Function to get ID specific to every derived Component class.
	/// Should never be used
	/// </summary>
	/// <typeparam name="T">Derived component class</typeparam>
	/// <returns>New component type's ID</returns>
	template<typename T>
	inline ComponentTypeID getComponentTypeID() {
		static ComponentTypeID typeID = getComponentTypeID();
		return typeID;
	}

	/// <summary>
	/// Base component class. All components should derive from it.
	/// </summary>
	class Component {
	public:
		Component() {}
		virtual ~Component() {};
	};
}
