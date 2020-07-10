//#pragma once
//
//#include <functional>
//
//#include "Component.hpp"
//#include "Vector2D.hpp"
//#include "Transform2DComponent.hpp"
//
//#ifdef ENJOYENGINE_EXPORTS
//#define ENJOYENGINE_API __declspec(dllexport)
//#else
//#define ENJOYENGINE_API __declspec(dllimport)
//#endif
//
//namespace EE {
//	class ENJOYENGINE_API CircleCollider2DComponent : public Component {
//	private:
//		float _radius;
//		std::function<void(Transform2DComponent, Vector2D<float>)> _onCollision;
//
//	public:
//		CircleCollider2DComponent();
//		~CircleCollider2DComponent();
//
//		float& radius();
//		void setHandler(std::function<void(Transform2DComponent, Vector2D<float>)> onCollision);
//		void callHandler(Transform2DComponent otherTransform, Vector2D<float> separationVector);
//
//	};
//}
