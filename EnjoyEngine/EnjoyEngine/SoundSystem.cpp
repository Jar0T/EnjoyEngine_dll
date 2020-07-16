#include "pch.h"

#include "SoundSystem.hpp"

namespace EE {
	SoundSystem::SoundSystem() {}

	SoundSystem::~SoundSystem() {}

	void SoundSystem::update() {
		std::vector<std::uint32_t> entities = EntityManager::getEntities();
		Transform2DComponent* t;
		SoundPlayerComponent* sp;
		SoundListenerComponent* sl;
		for (auto& entity : entities) {
			t = ComponentManager::getComponent<Transform2DComponent>(entity);
			if (t) {
				sp = ComponentManager::getComponent<SoundPlayerComponent>(entity);
				sl = ComponentManager::getComponent<SoundListenerComponent>(entity);
				if (sp) {
					sp->setSoundPosition(t->position());
				}
				if (sl) {
					sl->setPosition(t->position());
				}
			}
		}
	}

}