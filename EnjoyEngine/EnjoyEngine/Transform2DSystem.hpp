#pragma once

#include "System.hpp"
#include "Transform2DComponent.hpp"
#include "Time.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API Transform2DSystem : public System {
	private:

	public:
		Transform2DSystem();
		~Transform2DSystem();
		
		void update() override;

	};
}
