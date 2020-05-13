#pragma once
#include "Entity.hpp"

namespace EE {
	class IComponentMap {
	public:
		virtual ~IComponentMap() = default;
		virtual void removeComponent(EntityID entityID) = 0;
	};
}
