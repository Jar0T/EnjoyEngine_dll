// Precompiled headers
#include "pch.h"

// System headers
#include <iostream>

// My headers
#include "GameData.hpp"

namespace EE {
	GameData* GameData::_gameData = 0;

	GameData::GameData() {
		_window = std::make_shared<sf::RenderWindow>();
		_window->create(sf::VideoMode::getFullscreenModes()[0], "Window", sf::Style::Default);
		_title = "Window";
	}

	GameData::~GameData() {
		
	}

	sf::RenderWindow& GameData::window() {
		if (_gameData == 0)
			_gameData = new GameData();

		return *_gameData->_window;
	}

	void GameData::setWindowSize(int width, int height) {
		if (_gameData == 0)
			_gameData = new GameData();

		_gameData->_window->setSize(sf::Vector2u(width, height));
		_gameData->_window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)width, (float)height)));
	}

	void GameData::setWindowTitle(std::string title) {
		if (_gameData == 0)
			_gameData = new GameData();

		_gameData->_title = title;

		_gameData->_window->setTitle(title);
	}

	void GameData::setWindowFullscreen(bool fullscreen) {
		if (_gameData == 0)
			_gameData = new GameData();

		if (fullscreen)
			_gameData->_window->create(sf::VideoMode::getFullscreenModes()[0], _gameData->_title, sf::Style::Fullscreen);
		else
			_gameData->_window->create(sf::VideoMode::getFullscreenModes()[0], _gameData->_title, sf::Style::Default);
	}

	void GameData::onWindowResize()
	{
		if (_gameData == 0)
			_gameData = new GameData();

		sf::Vector2u size = _gameData->_window->getSize();
		_gameData->_window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)size.x, (float)size.y)));
	}
}