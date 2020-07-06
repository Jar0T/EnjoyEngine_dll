#include "pch.h"

#include "InputManager.hpp"

namespace EE {
	InputManager* InputManager::_inputManager = 0;

	InputManager::InputManager() {

	}
	
	InputManager::~InputManager() {

	}

	float InputManager::getAxis(std::string axisName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Joystick joystick = _inputManager->_joystick[axisName];

		if(sf::Joystick::isConnected(joystick.joystick))
			if(sf::Joystick::hasAxis(joystick.joystick, joystick.axis))
				return sf::Joystick::getAxisPosition(joystick.joystick, joystick.axis);
		return 0.f;
	}

	Vector2D<int> InputManager::getMousePosition() {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		sf::Vector2i pos = sf::Mouse::getPosition(GameData::window());

		return Vector2D<int>{pos.x, pos.y};
	}

	Vector2D<int> InputManager::getMousePositionRaw() {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		sf::Vector2i pos = sf::Mouse::getPosition();

		return Vector2D<int>{pos.x, pos.y};
	}

	void InputManager::setAxis(std::string axisName, sf::Joystick::Axis axis, unsigned int joystick) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_joystick[axisName] = Joystick{ joystick, -1, axis };
	}

	bool InputManager::getMouseButtonDown(std::string mouseButtonName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Mouse mouse = _inputManager->_mouse[mouseButtonName];

		return _inputManager->_mouseButtonsStates.at(mouse.button)[0];
	}

	bool InputManager::getMouseButtonUp(std::string mouseButtonName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Mouse mouse = _inputManager->_mouse[mouseButtonName];

		return !(_inputManager->_mouseButtonsStates.at(mouse.button)[0]);
	}

	bool InputManager::getMouseButtonPressed(std::string mouseButtonName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Mouse mouse = _inputManager->_mouse[mouseButtonName];

		return (_inputManager->_mouseButtonsStates.at(mouse.button)[0] && !(_inputManager->_mouseButtonsStates.at(mouse.button)[1]));
	}

	bool InputManager::getMouseButtonReleased(std::string mouseButtonName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Mouse mouse = _inputManager->_mouse[mouseButtonName];

		return (!(_inputManager->_mouseButtonsStates.at(mouse.button)[0]) && _inputManager->_mouseButtonsStates.at(mouse.button)[1]);
	}

}