//#pragma once
//#include "Component.hpp"
//#include "Vector2D.hpp"
//
//#ifdef ENJOYENGINE_EXPORTS
//#define ENJOYENGINE_API __declspec(dllexport)
//#else
//#define ENJOYENGINE_API __declspec(dllimport)
//#endif
//
//namespace EE {
//	class ENJOYENGINE_API Transform2DComponent : public Component {
//	private:
//		Vector2D<float> _position;
//		Vector2D<float> _velocity;
//		Vector2D<float> _acceleration;
//
//		float _frictionCoefficient;
//		float _mass;
//		bool _grounded;
//		bool _isStatic;
//		bool _affectedByGravity;
//		
//	public:
//		Transform2DComponent();
//		~Transform2DComponent();
//
//		Vector2D<float>& position();
//		Vector2D<float>& velocity();
//		Vector2D<float>& acceleration();
//		float& frictionCoefficient();
//		float& mass();
//		bool& grounded();
//		bool& isStatic();
//		bool& affectedByGravity();
//
//		void applyForce(Vector2D<float> force);
//
//	};
//}