#include "pch.h"

#include "TextureManager.hpp"

namespace EE {
	TextureManager* TextureManager::_textureManager = 0;

	TextureManager::TextureManager() {}

	void TextureManager::loadTexture(const char* fileName, unsigned int key) {
		if (_textureManager == 0)
			_textureManager = new TextureManager();

		if (_textureManager->_textureMap[key] == nullptr) {
			_textureManager->_textureMap[key] = new sf::Texture();
			_textureManager->_textureMap[key]->loadFromFile(fileName);
			_textureManager->_textureMap[key]->setSmooth(true);
		}
	}

	void TextureManager::deleteTexture(unsigned int key) {
		if (_textureManager == 0)
			_textureManager = new TextureManager();

		delete _textureManager->_textureMap[key];
		_textureManager->_textureMap.erase(key);
	}

	sf::Texture& TextureManager::getTexture(unsigned int key) {
		if (_textureManager == 0)
			_textureManager = new TextureManager();

		return *_textureManager->_textureMap[key];
	}
}