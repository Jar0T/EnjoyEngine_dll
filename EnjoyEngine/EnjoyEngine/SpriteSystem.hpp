#pragma once

#include <map>

#include "System.hpp"
#include "SpriteComponent.hpp"
#include "Transform2DComponent.hpp"
#include "GameData.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API SpriteSystem : public System {
	public:
		SpriteSystem();
		~SpriteSystem();

		void update() override;
	};
}
