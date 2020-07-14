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
	public:
		enum class Flags : uint32_t {
			NO_FLAG,
			OPTIONAL_COMPONENT
		};

	private:
		std::vector<std::uint32_t> _componentTypes;
		std::vector<std::uint32_t> _componetnFlags;

	protected:
		void addComponentType(uint32_t componetnType, Flags componentFlag = Flags::NO_FLAG);

	public:
		BaseECSSystem();

		virtual void updateComponents(BaseECSComponent** components);

		const std::vector<std::uint32_t>& getComponentTypes();
		const std::vector<uint32_t>& getComponentFlags();

		bool isValid();

	};
}
