#pragma once

#include "ECSComponent.hpp"
#include "Vector2D.hpp"

namespace EE {
	struct Transform2DComponent : public ECSComponent<Transform2DComponent> {
		Vector2D<float> position;
		Vector2D<float> velocity;
		Vector2D<float> acceleration;
	};
}
