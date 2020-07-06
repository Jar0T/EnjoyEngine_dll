#include "pch.h"

#include "InputManager.hpp"

namespace EE {
	InputManager* InputManager::_inputManager = 0;

	InputManager::InputManager() {
		for (unsigned int i = 0; i < 8; i++) {
			for (unsigned int j = 0; j < 32; j++) {
				_joystickButtonsStates[i][j].first = false;
				_joystickButtonsStates[i][j].second = false;
			}
		}

		for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
			_keyboardKeysStates[(sf::Keyboard::Key)i].first = false;
			_keyboardKeysStates[(sf::Keyboard::Key)i].second = false;
		}

		for (int i = 0; i < sf::Mouse::ButtonCount; i++) {
			_mouseButtonsStates[(sf::Mouse::Button)i].first = false;
			_mouseButtonsStates[(sf::Mouse::Button)i].second = false;
		}
	}

	void InputManager::updateButtonsStates() {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		for (unsigned int i = 0; i < 8; i++) {
			if (sf::Joystick::isConnected(i)) {
				for (unsigned int j = 0; j < sf::Joystick::getButtonCount(i); j++) {
					_inputManager->_joystickButtonsStates.at(i).at(j).second = _inputManager->_joystickButtonsStates.at(i).at(j).first;
					_inputManager->_joystickButtonsStates.at(i).at(j).first = sf::Joystick::isButtonPressed(i, j);
				}
			}
		}

		for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
			_inputManager->_keyboardKeysStates.at((sf::Keyboard::Key)i).second = _inputManager->_keyboardKeysStates.at((sf::Keyboard::Key)i).first;
			_inputManager->_keyboardKeysStates.at((sf::Keyboard::Key)i).first = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);
		}

		for (int i = 0; i < sf::Mouse::ButtonCount; i++) {
			_inputManager->_mouseButtonsStates.at((sf::Mouse::Button)i).second = _inputManager->_mouseButtonsStates.at((sf::Mouse::Button)i).first;
			_inputManager->_mouseButtonsStates.at((sf::Mouse::Button)i).first = sf::Mouse::isButtonPressed((sf::Mouse::Button)i);
		}
	}
	
	InputManager::~InputManager() {

	}

	float InputManager::getAxis(std::string axisName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Joystick joystick = _inputManager->_joystick[axisName];

		if (sf::Joystick::isConnected(joystick.joystick)) {
			if (sf::Joystick::hasAxis(joystick.joystick, joystick.axis)) {
				float axis = sf::Joystick::getAxisPosition(joystick.joystick, joystick.axis);
				axis = (std::abs(axis) < 0.01 ? 0 : axis);
				return axis / 100.f;
			}
		}
		return 0.f;
	}

	bool InputManager::getButtonDown(std::string buttonName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Joystick joystick = _inputManager->_joystick[buttonName];

		return _inputManager->_joystickButtonsStates.at(joystick.joystick).at(joystick.button).first;
	}

	bool InputManager::getButtonUp(std::string buttonName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Joystick joystick = _inputManager->_joystick[buttonName];

		return !(_inputManager->_joystickButtonsStates.at(joystick.joystick).at(joystick.button).first);
	}

	bool InputManager::getButtonPressed(std::string buttonName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Joystick joystick = _inputManager->_joystick[buttonName];

		return (_inputManager->_joystickButtonsStates.at(joystick.joystick).at(joystick.button).first && !(_inputManager->_joystickButtonsStates.at(joystick.joystick).at(joystick.button).second));
	}

	bool InputManager::getButtonReleased(std::string buttonName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Joystick joystick = _inputManager->_joystick[buttonName];

		return (!(_inputManager->_joystickButtonsStates.at(joystick.joystick).at(joystick.button).first) && _inputManager->_joystickButtonsStates.at(joystick.joystick).at(joystick.button).second);
	}

	bool InputManager::getKeyDown(std::string keyName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Keyboard keyboard = _inputManager->_keyboard[keyName];

		return _inputManager->_keyboardKeysStates.at(keyboard.key).first;
	}

	bool InputManager::getKeyUp(std::string keyName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Keyboard keyboard = _inputManager->_keyboard[keyName];

		return !(_inputManager->_keyboardKeysStates.at(keyboard.key).first);
	}

	bool InputManager::getKeyPressed(std::string keyName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Keyboard keyboard = _inputManager->_keyboard[keyName];

		return (_inputManager->_keyboardKeysStates.at(keyboard.key).first && !(_inputManager->_keyboardKeysStates.at(keyboard.key).second));
	}

	bool InputManager::getKeyReleased(std::string keyName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Keyboard keyboard = _inputManager->_keyboard[keyName];

		return (!(_inputManager->_keyboardKeysStates.at(keyboard.key).first) && _inputManager->_keyboardKeysStates.at(keyboard.key).second);
	}

	bool InputManager::getMouseButtonDown(std::string mouseButtonName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Mouse mouse = _inputManager->_mouse[mouseButtonName];

		return _inputManager->_mouseButtonsStates.at(mouse.button).first;
	}

	bool InputManager::getMouseButtonUp(std::string mouseButtonName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Mouse mouse = _inputManager->_mouse[mouseButtonName];

		return !(_inputManager->_mouseButtonsStates.at(mouse.button).first);
	}

	bool InputManager::getMouseButtonPressed(std::string mouseButtonName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Mouse mouse = _inputManager->_mouse[mouseButtonName];

		return (_inputManager->_mouseButtonsStates.at(mouse.button).first && !(_inputManager->_mouseButtonsStates.at(mouse.button).second));
	}

	bool InputManager::getMouseButtonReleased(std::string mouseButtonName) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		Mouse mouse = _inputManager->_mouse[mouseButtonName];

		return (!(_inputManager->_mouseButtonsStates.at(mouse.button).first) && _inputManager->_mouseButtonsStates.at(mouse.button).second);
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

		_inputManager->_joystick[axisName] = Joystick{ joystick, 0, axis };
	}

	void InputManager::setButton(std::string buttonName, unsigned int button, unsigned int joystick) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_joystick[buttonName] = Joystick{ joystick, button };
	}

	void InputManager::setKey(std::string keyName, sf::Keyboard::Key key) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_keyboard[keyName] = Keyboard{ key };
	}

	void InputManager::setMouseButton(std::string mouseButtonName, sf::Mouse::Button button) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_mouse[mouseButtonName] = Mouse{ button };
	}

}