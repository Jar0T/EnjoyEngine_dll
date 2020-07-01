#include "pch.h"

#include "CircleCollider2DComponent.hpp"

namespace EE {
	CircleCollider2DComponent::CircleCollider2DComponent() {
		_position = Vector2D<float>{ 0.f, 0.f };
		_radius = 0.f;
	}

	CircleCollider2DComponent::~CircleCollider2DComponent() {

	}

	Vector2D<float>& CircleCollider2DComponent::position() {
		return _position;
	}

	float& CircleCollider2DComponent::radius() {
		return _radius;
	}

}