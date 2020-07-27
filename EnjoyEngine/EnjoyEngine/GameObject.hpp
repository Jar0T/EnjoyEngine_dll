#pragma once

#include "ecs.hpp"
#include "GameData.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API GameObject {
	protected:
		EntityHandle _entity;

	public:
		GameObject();
		virtual ~GameObject();

		virtual void update();

		EntityHandle getEntity();
	};
}
