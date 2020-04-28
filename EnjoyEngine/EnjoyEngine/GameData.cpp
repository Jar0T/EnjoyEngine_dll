// Precompiled headers
#include "pch.h"

// System headers
#include <iostream>

// My headers
#include "GameData.hpp"

namespace EE {
	GameData* GameData::_gameData = 0;

	GameData::GameData() {
		_window = new sf::RenderWindow();
		_window->create(sf::VideoMode(800, 600), "Window", sf::Style::Default);
		_title = "Window";
	}

	GameData::~GameData() {
		delete _window;
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
}