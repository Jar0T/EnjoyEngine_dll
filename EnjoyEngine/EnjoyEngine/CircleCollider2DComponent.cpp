#include "pch.h"
//
//#include "CircleCollider2DComponent.hpp"
//
//namespace EE {
//	CircleCollider2DComponent::CircleCollider2DComponent() {
//		_radius = 0.f;
//	}
//
//	CircleCollider2DComponent::~CircleCollider2DComponent() {
//
//	}
//
//	float& CircleCollider2DComponent::radius() {
//		return _radius;
//	}
//
//	void CircleCollider2DComponent::setHandler(std::function<void(Transform2DComponent, Vector2D<float>)> onCollision) {
//		_onCollision = onCollision;
//	}
//
//	void CircleCollider2DComponent::callHandler(Transform2DComponent otherTransform, Vector2D<float> separationVector) {
//		_onCollision(otherTransform, separationVector);
//	}
//
//}