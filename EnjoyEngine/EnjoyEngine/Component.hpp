#pragma once
#include <iostream>

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

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
	class ENJOYENGINE_API Component {
	private:
		int _stackLayer;

	public:
		Component();
		virtual ~Component();

		int getStackLayer();
		void setStackLayer(int stackLayer);
	};
}
