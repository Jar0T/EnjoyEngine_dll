#pragma once

#include "System.hpp"
#include "CircleCollider2DComponent.hpp"
#include "Transform2DComponent.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API CirclevsCircleCollisionSystem : public System {
	public:
		CirclevsCircleCollisionSystem();
		~CirclevsCircleCollisionSystem();

		void update() override;

	};
}

