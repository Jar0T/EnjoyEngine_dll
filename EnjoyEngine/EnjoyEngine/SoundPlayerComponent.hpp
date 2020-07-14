#pragma once

#include <map>
#include <memory>

#include "ECSComponent.hpp"
#include "SoundManager.hpp"
#include "Vector2D.hpp"

#include "SFML/Audio.hpp"

#define SOUND_DISTANCE_SCALING 50.f;

namespace EE {
	struct SoundPlayerComponent : public ECSComponent<SoundPlayerComponent>	{
		std::map<std::string, std::shared_ptr<sf::Sound>> sound;

		void addSound(unsigned int soundKey, std::string soundName) {
			if (sound[soundName] == nullptr) {
				sound[soundName] = std::make_unique<sf::Sound>(SoundManager::getSound(soundKey));
			}
		}

		void playSound(std::string soundName) {
			if (sound.find(soundName) != sound.end())
				if (sound[soundName]->getStatus() != sf::Sound::Status::Playing)
					sound[soundName]->play();
		}
		void pauseSound(std::string soundName) {
			if (sound.find(soundName) != sound.end())
				if (sound[soundName]->getStatus() == sf::Sound::Status::Playing)
					sound[soundName]->pause();
		}
		void stopSound(std::string soundName) {
			if (sound.find(soundName) != sound.end())
				if (sound[soundName]->getStatus() != sf::Sound::Status::Stopped)
					sound[soundName]->stop();
		}

		void setSoundPosition(Vector2D<float> position) {
			std::map<std::string, std::shared_ptr<sf::Sound>>::iterator s;
			position /= SOUND_DISTANCE_SCALING;
			for (s = sound.begin(); s != sound.end(); s++) {
				s->second->setPosition(position.x, position.y, 0.f);
			}
		}
		void setSoundVolume(std::string soundName, float volume) {
			if (sound.find(soundName) != sound.end())
				sound[soundName]->setVolume(volume);
		}
		void setSoundLoop(std::string soundName, bool loop = true) {
			if (sound.find(soundName) != sound.end())
				sound[soundName]->setLoop(loop);
		}
	};
}
