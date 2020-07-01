#include "pch.h"

#include "CircleCollider2DComponent.hpp"

namespace EE {
	CircleCollider2DComponent::CircleCollider2DComponent() {
		_radius = 0.f;
	}

	CircleCollider2DComponent::~CircleCollider2DComponent() {

	}

	float& CircleCollider2DComponent::radius() {
		return _radius;
	}

}