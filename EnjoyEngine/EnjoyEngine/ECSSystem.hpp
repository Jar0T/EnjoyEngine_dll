#pragma once

#include "ECSComponent.hpp"
#include "Time.hpp"

namespace EE {
	class BaseECSSystem {
	public:
		enum class Flags : uint32_t {
			NO_FLAG,
			OPTIONAL_COMPONENT
		};

	private:
		std::vector<std::uint32_t> _componentTypes;
		std::vector<std::uint32_t> _componetnFlags;

	protected:
		void addComponentType(uint32_t componetnType, Flags componentFlag = Flags::NO_FLAG) {
			_componentTypes.push_back(componetnType);
			_componetnFlags.push_back((uint32_t)componentFlag);
		}

	public:
		BaseECSSystem() {};

		virtual void updateComponents(BaseECSComponent** components) {};

		const std::vector<std::uint32_t>& getComponentTypes() { return _componentTypes; };
		const std::vector<uint32_t>& getComponentFlags() { return _componetnFlags; };

		bool isValid() {
			for (size_t i = 0; i < _componetnFlags.size(); i++) {
				if ((_componetnFlags[i] & (uint32_t)BaseECSSystem::Flags::OPTIONAL_COMPONENT) == 0) {
					return true;
				}
			}
			return false;
		}

	};
}
