#pragma once
#include <iostream>

namespace EE {
	using ComponentTypeID = std::uint32_t;

	inline ComponentTypeID getComponentTypeID() {
		static ComponentTypeID lastID = 0;
		return lastID++;
	}

	template<typename T>
	inline ComponentTypeID getComponentTypeID() {
		static ComponentTypeID typeID = getComponentTypeID();
		return typeID;
	}

	class Component {
	public:
		Component() {}
		virtual ~Component() {};
	};
}
