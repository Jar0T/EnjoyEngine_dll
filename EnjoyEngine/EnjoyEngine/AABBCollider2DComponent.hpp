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
//	class ENJOYENGINE_API AABBCollider2DComponent : public Component {
//	private:
//		Vector2D<float> _size;
//		std::function<void(Transform2DComponent, Vector2D<float>)> _onCollision;
//
//	public:
//		AABBCollider2DComponent();
//		~AABBCollider2DComponent();
//
//		Vector2D<float>& size();
//		void setHandler(std::function<void(Transform2DComponent, Vector2D<float>)> onCollision);
//		void callHandler(Transform2DComponent otherTransform, Vector2D<float> separationVector);
//
//	};
//}
