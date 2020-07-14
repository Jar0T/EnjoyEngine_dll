#pragma once

#include <functional>

#include "ECSComponent.hpp"
#include "Vector2D.hpp"
#include "Transform2DComponent.hpp"

namespace EE {
	struct CircleCollider2DComponent : public ECSComponent<CircleCollider2DComponent> {
		float _radius;
		std::function<void(Transform2DComponent, Vector2D<float>)> _onCollision;
		
		void setHandler(std::function<void(Transform2DComponent, Vector2D<float>)> onCollision) {
			_onCollision = onCollision;
		}
		void callHandler(Transform2DComponent otherTransform, Vector2D<float> separationVector) {
			_onCollision(otherTransform, separationVector);
		}
	};
}
