#include "pch.h"

#include "Transform2DComponent.hpp"

namespace EE {
	Transform2DComponent::Transform2DComponent() {
		_position = Vector2D<float>{ 0.f, 0.f };
		_velocity = Vector2D<float>{ 0.f, 0.f };
		_acceleration = Vector2D<float>{ 0.f, 0.f };
		_mass = 0.f;
	}

	Transform2DComponent::~Transform2DComponent() {

	}

	Vector2D<float>& Transform2DComponent::position() {
		return _position;
	}

	Vector2D<float>& Transform2DComponent::velocity() {
		return _velocity;
	}

	Vector2D<float>& Transform2DComponent::acceleration() {
		return _acceleration;
	}

	float& Transform2DComponent::mass() {
		return _mass;
	}

	void Transform2DComponent::applyForce(Vector2D<float> force) {
		if (_mass > 0.f)
			_acceleration = force / _mass;
	}

}
