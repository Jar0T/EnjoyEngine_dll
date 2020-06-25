#pragma once

namespace EE {
	/// <summary>
	/// Interface for ComponentMap class
	/// </summary>
	class IComponentMap {
	public:
		virtual ~IComponentMap() = default;
		virtual void removeComponent(std::uint32_t entityID) = 0;
	};
}
