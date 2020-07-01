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

}