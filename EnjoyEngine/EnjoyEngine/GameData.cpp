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

		_ecs = std::make_shared<ECS>();

		_camera.push_back(std::make_shared<Camera>());
		sf::Vector2u size = _window->getSize();
		_camera[0]->view = sf::View(sf::FloatRect(0.f, 0.f, (float)size.x, (float)size.y));
		_window->setView(_camera[0]->view);
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

	void GameData::onWindowResize() {
		if (_gameData == 0)
			_gameData = new GameData();

		sf::Vector2u size = _gameData->_window->getSize();
		for (auto& camera : _gameData->_camera) {
			camera->view.setSize((float)size.x, (float)size.y);
		}
	}

	ECS& GameData::ecs() {
		if (_gameData == 0)
			_gameData = new GameData();

		return *_gameData->_ecs;
	}
	
	std::shared_ptr<Camera> GameData::camera(size_t index) {
		if (_gameData == 0)
			_gameData = new GameData();

		if (index < _gameData->_camera.size())
			return _gameData->_camera[index];
		return nullptr;
	}

	size_t GameData::addCamera() {
		if (_gameData == 0)
			_gameData = new GameData();

		_gameData->_camera.push_back(std::make_shared<Camera>());
		return _gameData->_camera.size() - 1;
	}
}