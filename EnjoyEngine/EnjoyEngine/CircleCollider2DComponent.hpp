#pragma once
#include "Component.hpp"
#include "Vector2D.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API CircleCollider2DComponent : public Component {
	private:
		Vector2D<float> _position;
		float _radius;

	public:
		CircleCollider2DComponent();
		~CircleCollider2DComponent();

		Vector2D<float>& position();
		float& radius();

	};
}
