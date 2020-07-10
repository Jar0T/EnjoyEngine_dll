#pragma once

#include "ECSComponent.hpp"
#include "Time.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API BaseECSSystem {
	private:
		std::vector<std::uint32_t> _componentTypes;

	public:
		BaseECSSystem(const std::vector<std::uint32_t>& componentTypes);

		virtual void updateComponents(BaseECSComponent** components);

		const std::vector<std::uint32_t>& getComponentTypes();

	};
}
