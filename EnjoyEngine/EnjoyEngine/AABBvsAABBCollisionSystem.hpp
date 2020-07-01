#pragma once

#include "System.hpp"
#include "AABBCollider2DComponent.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API AABBvsAABBCollisionSystem : public System {
	public:
		AABBvsAABBCollisionSystem();
		~AABBvsAABBCollisionSystem();

		void update() override;

	};
}
