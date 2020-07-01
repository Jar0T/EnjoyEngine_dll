#pragma once

#include "System.hpp"
#include "AABBCollider2DComponent.hpp"
#include "CircleCollider2DComponent.hpp"
#include "Transform2DComponent.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API AABBvsCircleCollisionSystem : public System {
	private:
		bool checkCollision(AABBCollider2DComponent* a, CircleCollider2DComponent* b, Vector2D<float> pos1, Vector2D<float> pos2);
	public:
		AABBvsCircleCollisionSystem();
		~AABBvsCircleCollisionSystem();

		void update() override;
	};
}

