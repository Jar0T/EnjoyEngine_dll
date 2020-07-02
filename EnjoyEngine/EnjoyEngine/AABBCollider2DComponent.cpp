#include "pch.h"

#include "AABBCollider2DComponent.hpp"

namespace EE {
	AABBCollider2DComponent::AABBCollider2DComponent() {
		_size = Vector2D<float>{ 0.f, 0.f };
	}

	AABBCollider2DComponent::~AABBCollider2DComponent() {

	}

	Vector2D<float>& AABBCollider2DComponent::size() {
		return _size;
	}

	void AABBCollider2DComponent::setHandler(std::function<void(Transform2DComponent, Vector2D<float>)> onCollision) {
		_onCollision = onCollision;
	}

	void AABBCollider2DComponent::callHandler(Transform2DComponent otherTransform, Vector2D<float> separationVector) {
		_onCollision(otherTransform, separationVector);
	}

}