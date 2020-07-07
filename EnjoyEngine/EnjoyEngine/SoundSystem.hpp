#pragma once

#include "System.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "Transform2DComponent.hpp"
#include "SoundPlayerComponent.hpp"
#include "SoundListenerComponent.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API SoundSystem : public System {
	public:
		SoundSystem();
		~SoundSystem();

		void update() override;

	};
}
