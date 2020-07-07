#include "pch.h"

#include "SoundSystem.hpp"

namespace EE {
	SoundSystem::SoundSystem() {}

	SoundSystem::~SoundSystem() {}

	void SoundSystem::update() {
		std::vector<std::uint32_t> entities = EntityManager::getEntities();
		std::shared_ptr<Transform2DComponent> t;
		std::shared_ptr<SoundPlayerComponent> sp;
		std::shared_ptr<SoundListenerComponent> sl;
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