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

	void InputManager::handleEvents() {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		sf::Event e;
		while (GameData::window().pollEvent(e)) {
			switch (e.type)	{
			case sf::Event::Closed:
				for (auto func : _inputManager->_closedEventSubscribers) {
					func();
				}
				break;
			case sf::Event::Resized:
				GameData::onWindowResize();
				for (auto func : _inputManager->_resizedEventSubscribers) {
					func(e.size.width, e.size.height);
				}
				break;
			case sf::Event::TextEntered:
				for (auto func : _inputManager->_textEnteredEventSubscribers) {
					func(e.text.unicode);
				}
				break;
			case sf::Event::GainedFocus:
				for (auto func : _inputManager->_gainedFocusEventSubscribers) {
					func();
				}
				break;
			case sf::Event::LostFocus:
				for (auto func : _inputManager->_lostFocusEventSubscribers) {
					func();
				}
				break;
			case sf::Event::KeyPressed:
				for (auto func : _inputManager->_keyPressedEventSubscribers) {
					func(e.key.code);
				}
				break;
			case sf::Event::KeyReleased:
				for (auto func : _inputManager->_keyReleasedEventSubscribers) {
					func(e.key.code);
				}
				break;
			case sf::Event::MouseButtonPressed:
				for (auto func : _inputManager->_mouseButtonPressedEventSubscribers) {
					func(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
				}
				break;
			case sf::Event::MouseButtonReleased:
				for (auto func : _inputManager->_mouseButtonReleasedEventSubscribers) {
					func(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
				}
				break;
			case sf::Event::MouseWheelScrolled:
				for (auto func : _inputManager->_mouseWheelScrolledEventSubscribers) {
					func(e.mouseWheelScroll.wheel, e.mouseWheelScroll.delta, e.mouseWheelScroll.x, e.mouseWheelScroll.y);
				}
				break;
			case sf::Event::MouseMoved:
				for (auto func : _inputManager->_mouseMovedEventSubscribers) {
					func(e.mouseMove.x, e.mouseMove.y);
				}
				break;
			case sf::Event::MouseEntered:
				for (auto func : _inputManager->_mouseEnteredEventSubscribers) {
					func();
				}
				break;
			case sf::Event::MouseLeft:
				for (auto func : _inputManager->_mouseLeftEventSubscribers) {
					func();
				}
				break;
			case sf::Event::JoystickButtonPressed:
				for (auto func : _inputManager->_joystickButtonPressedEventSubscribers) {
					func(e.joystickButton.joystickId, e.joystickButton.button);
				}
				break;
			case sf::Event::JoystickButtonReleased:
				for (auto func : _inputManager->_joystickButtonReleasedEventSubscribers) {
					func(e.joystickButton.joystickId, e.joystickButton.button);
				}
				break;
			case sf::Event::JoystickMoved:
				for (auto func : _inputManager->_joystickMovedEventSubscribers) {
					func(e.joystickMove.joystickId, e.joystickMove.axis, e.joystickMove.position);
				}
				break;
			case sf::Event::JoystickConnected:
				for (auto func : _inputManager->_joystickConnectedEventSubscribers) {
					func(e.joystickConnect.joystickId);
				}
				break;
			case sf::Event::JoystickDisconnected:
				for (auto func : _inputManager->_joystickDisconnectedEventSubscribers) {
					func(e.joystickConnect.joystickId);
				}
				break;
			default:
				break;
			}
		}
	}
	
	InputManager::~InputManager() {}

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

	void InputManager::subscribeToCloseEvent(std::function<void()> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_closedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToResizeEvent(std::function<void(unsigned int, unsigned int)> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_resizedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToTextEnteredEvent(std::function<void(sf::String)> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_textEnteredEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToGainedFocusEvent(std::function<void()> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_gainedFocusEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToLostFocusEvent(std::function<void()> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_lostFocusEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToKeyPressedEvent(std::function<void(sf::Keyboard::Key)> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_keyPressedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToKeyReleasedEvent(std::function<void(sf::Keyboard::Key)> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_keyReleasedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToMouseButtonPressedEvent(std::function<void(sf::Mouse::Button, int, int)> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_mouseButtonPressedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToMouseButtonReleasedEvent(std::function<void(sf::Mouse::Button, int, int)> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_mouseButtonReleasedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToMouseWheelScrolledEvent(std::function<void(sf::Mouse::Wheel, float, int, int)> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_mouseWheelScrolledEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToMouseMovedEvent(std::function<void(int, int)> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_mouseMovedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToMouseEnteredEvent(std::function<void()> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_mouseEnteredEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToMouseLeftEvent(std::function<void()> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_mouseLeftEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToJoystickButtonPressedEvent(std::function<void(unsigned int, unsigned int)> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_joystickButtonPressedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToJoystickButtonReleasedEvent(std::function<void(unsigned int, unsigned int)> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_joystickButtonReleasedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToJoystickMovedEvent(std::function<void(unsigned int, sf::Joystick::Axis, float)> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_joystickMovedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToJoystickConnectedEvent(std::function<void(unsigned int)> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_joystickConnectedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToJoystickDisconnectedEvent(std::function<void(unsigned int)> subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_joystickDisconnectedEventSubscribers.push_back(subscriber);
	}

}