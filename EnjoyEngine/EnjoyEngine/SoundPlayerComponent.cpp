#include "pch.h"
//
//#include "SoundPlayerComponent.hpp"
//
//#define SOUND_DISTANCE_SCALING 50.f;
//
//namespace EE {
//	SoundPlayerComponent::SoundPlayerComponent() {}
//
//	SoundPlayerComponent::~SoundPlayerComponent() {}
//
//	void SoundPlayerComponent::addSound(unsigned int soundKey, std::string soundName) {
//		if (_sound[soundName] == nullptr) {
//			_sound[soundName] = std::make_unique<sf::Sound>(SoundManager::getSound(soundKey));
//		}
//	}
//
//	void SoundPlayerComponent::playSound(std::string soundName) {
//		if (_sound[soundName]) {
//			_sound[soundName]->play();
//		}
//	}
//
//	void SoundPlayerComponent::pauseSound(std::string soundName) {
//		if (_sound[soundName]) {
//			_sound[soundName]->pause();
//		}
//	}
//
//	void SoundPlayerComponent::stopSound(std::string soundName) {
//		if (_sound[soundName]) {
//			_sound[soundName]->stop();
//		}
//	}
//
//	void SoundPlayerComponent::setSoundPosition(Vector2D<float> position) {
//		std::map<std::string, std::unique_ptr<sf::Sound>>::iterator sound;
//		position /= SOUND_DISTANCE_SCALING;
//		for (sound = _sound.begin(); sound != _sound.end(); sound++) {
//			sound->second->setPosition(position.x, position.y, 0.f);
//		}
//	}
//
//	void SoundPlayerComponent::setSoundVolume(std::string soundName, float volume) {
//		_sound[soundName]->setVolume(volume);
//	}
//
//	void SoundPlayerComponent::setSoundLoop(std::string soundName, bool loop) {
//		_sound[soundName]->setLoop(loop);
//	}
//
//}