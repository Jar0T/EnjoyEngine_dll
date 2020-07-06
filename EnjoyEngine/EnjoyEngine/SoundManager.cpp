#include "pch.h"

#include "SoundManager.hpp"

namespace EE {
	SoundManager* SoundManager::_soundManager = 0;

	SoundManager::SoundManager() {}

	SoundManager::~SoundManager() {}

	void SoundManager::loadSound(const char* fileName, unsigned int key) {
		if (_soundManager == 0)
			_soundManager = new SoundManager;

		if (_soundManager->_soundMap[key] == nullptr) {
			_soundManager->_soundMap[key] = std::make_unique<sf::SoundBuffer>();
			_soundManager->_soundMap[key]->loadFromFile(fileName);
		}
	}

	void SoundManager::deleteSound(unsigned int key) {
		if (_soundManager == 0)
			_soundManager = new SoundManager;

		_soundManager->_soundMap[key].reset();
		_soundManager->_soundMap.erase(key);
	}

	sf::SoundBuffer& SoundManager::getSound(unsigned int key) {
		if (_soundManager == 0)
			_soundManager = new SoundManager;

		return *_soundManager->_soundMap[key];
	}

}