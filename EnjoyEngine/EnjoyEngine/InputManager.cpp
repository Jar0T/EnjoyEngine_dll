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

			std::vector< std::weak_ptr< std::function< void() > > >::iterator it1;
			std::vector< std::weak_ptr< std::function< void(unsigned int, unsigned int) > > >::iterator it2;
			std::vector< std::weak_ptr< std::function< void(sf::String) > > >::iterator it3;
			std::vector< std::weak_ptr< std::function< void() > > >::iterator it4;
			std::vector< std::weak_ptr< std::function< void() > > >::iterator it5;
			std::vector< std::weak_ptr< std::function< void(sf::Keyboard::Key) > > >::iterator it6;
			std::vector< std::weak_ptr< std::function< void(sf::Keyboard::Key) > > >::iterator it7;
			std::vector< std::weak_ptr< std::function< void(sf::Mouse::Button, int, int) > > >::iterator it8;
			std::vector< std::weak_ptr< std::function< void(sf::Mouse::Button, int, int) > > >::iterator it9;
			std::vector< std::weak_ptr< std::function< void(sf::Mouse::Wheel, float, int, int) > > >::iterator it10;
			std::vector< std::weak_ptr< std::function< void(int, int) > > >::iterator it11;
			std::vector< std::weak_ptr< std::function< void() > > >::iterator it12;
			std::vector< std::weak_ptr< std::function< void() > > >::iterator it13;
			std::vector< std::weak_ptr< std::function< void(unsigned int, unsigned int) > > >::iterator it14;
			std::vector< std::weak_ptr< std::function< void(unsigned int, unsigned int) > > >::iterator it15;
			std::vector< std::weak_ptr< std::function< void(unsigned int, sf::Joystick::Axis, float) > > >::iterator it16;
			std::vector< std::weak_ptr< std::function< void(unsigned int) > > >::iterator it17;
			std::vector< std::weak_ptr< std::function< void(unsigned int) > > >::iterator it18;

			switch (e.type)	{
			case sf::Event::Closed:
				for (it1 = _inputManager->_closedEventSubscribers.begin(); it1 != _inputManager->_closedEventSubscribers.end(); it1++) {
					if (it1->expired()) {
						_inputManager->_closedEventSubscribers.erase(it1);
					}
					else {
						(*it1->lock())();
					}
				}
				break;

			case sf::Event::Resized:
				GameData::onWindowResize();
				for (it2 = _inputManager->_resizedEventSubscribers.begin(); it2 != _inputManager->_resizedEventSubscribers.end(); it2++) {
					if (it2->expired()) {
						_inputManager->_resizedEventSubscribers.erase(it2);
					}
					else {
						(*it2->lock())(e.size.width, e.size.height);
					}
				}
				break;

			case sf::Event::TextEntered:
				for (it3 = _inputManager->_textEnteredEventSubscribers.begin(); it3 != _inputManager->_textEnteredEventSubscribers.end(); it3++) {
					if (it3->expired()) {
						_inputManager->_textEnteredEventSubscribers.erase(it3);
					}
					else {
						(*it3->lock())(e.text.unicode);
					}
				}
				break;

			case sf::Event::GainedFocus:
				for (it4 = _inputManager->_gainedFocusEventSubscribers.begin(); it4 != _inputManager->_gainedFocusEventSubscribers.end(); it4++) {
					if (it4->expired()) {
						_inputManager->_gainedFocusEventSubscribers.erase(it4);
					}
					else {
						(*it4->lock())();
					}
				}
				break;

			case sf::Event::LostFocus:
				for (it5 = _inputManager->_lostFocusEventSubscribers.begin(); it5 != _inputManager->_lostFocusEventSubscribers.end(); it5++) {
					if (it5->expired()) {
						_inputManager->_lostFocusEventSubscribers.erase(it5);
					}
					else {
						(*it5->lock())();
					}
				}
				break;

			case sf::Event::KeyPressed:
				for (it6 = _inputManager->_keyPressedEventSubscribers.begin(); it6 != _inputManager->_keyPressedEventSubscribers.end(); it6++) {
					if (it6->expired()) {
						_inputManager->_keyPressedEventSubscribers.erase(it6);
					}
					else {
						(*it6->lock())(e.key.code);
					}
				}
				break;

			case sf::Event::KeyReleased:
				for (it7 = _inputManager->_keyReleasedEventSubscribers.begin(); it7 != _inputManager->_keyReleasedEventSubscribers.end(); it7++) {
					if (it7->expired()) {
						_inputManager->_keyReleasedEventSubscribers.erase(it7);
					}
					else {
						(*it7->lock())(e.key.code);
					}
				}
				break;

			case sf::Event::MouseButtonPressed:
				for (it8 = _inputManager->_mouseButtonPressedEventSubscribers.begin(); it8 != _inputManager->_mouseButtonPressedEventSubscribers.end(); it8++) {
					if (it8->expired()) {
						_inputManager->_mouseButtonPressedEventSubscribers.erase(it8);
					}
					else {
						(*it8->lock())(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
					}
				}
				break;

			case sf::Event::MouseButtonReleased:
				for (it9 = _inputManager->_mouseButtonReleasedEventSubscribers.begin(); it9 != _inputManager->_mouseButtonReleasedEventSubscribers.end(); it9++) {
					if (it9->expired()) {
						_inputManager->_mouseButtonReleasedEventSubscribers.erase(it9);
					}
					else {
						(*it9->lock())(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
					}
				}
				break;

			case sf::Event::MouseWheelScrolled:
				for (it10 = _inputManager->_mouseWheelScrolledEventSubscribers.begin(); it10 != _inputManager->_mouseWheelScrolledEventSubscribers.end(); it10++) {
					if (it10->expired()) {
						_inputManager->_mouseWheelScrolledEventSubscribers.erase(it10);
					}
					else {
						(*it10->lock())(e.mouseWheelScroll.wheel, e.mouseWheelScroll.delta, e.mouseWheelScroll.x, e.mouseWheelScroll.y);
					}
				}
				break;

			case sf::Event::MouseMoved:
				for (it11 = _inputManager->_mouseMovedEventSubscribers.begin(); it11 != _inputManager->_mouseMovedEventSubscribers.end(); it11++) {
					if (it11->expired()) {
						_inputManager->_mouseMovedEventSubscribers.erase(it11);
					}
					else {
						(*it11->lock())(e.mouseMove.x, e.mouseMove.y);
					}
				}
				break;

			case sf::Event::MouseEntered:
				for (it12 = _inputManager->_mouseEnteredEventSubscribers.begin(); it12 != _inputManager->_mouseEnteredEventSubscribers.end(); it12++) {
					if (it12->expired()) {
						_inputManager->_mouseEnteredEventSubscribers.erase(it12);
					}
					else {
						(*it12->lock())();
					}
				}
				break;

			case sf::Event::MouseLeft:
				for (it13 = _inputManager->_mouseLeftEventSubscribers.begin(); it13 != _inputManager->_mouseLeftEventSubscribers.end(); it13++) {
					if (it13->expired()) {
						_inputManager->_mouseLeftEventSubscribers.erase(it13);
					}
					else {
						(*it13->lock())();
					}
				}
				break;

			case sf::Event::JoystickButtonPressed:
				for (it14 = _inputManager->_joystickButtonPressedEventSubscribers.begin(); it14 != _inputManager->_joystickButtonPressedEventSubscribers.end(); it14++) {
					if (it14->expired()) {
						_inputManager->_joystickButtonPressedEventSubscribers.erase(it14);
					}
					else {
						(*it14->lock())(e.joystickButton.joystickId, e.joystickButton.button);
					}
				}
				break;

			case sf::Event::JoystickButtonReleased:
				for (it15 = _inputManager->_joystickButtonReleasedEventSubscribers.begin(); it15 != _inputManager->_joystickButtonReleasedEventSubscribers.end(); it15++) {
					if (it15->expired()) {
						_inputManager->_joystickButtonReleasedEventSubscribers.erase(it15);
					}
					else {
						(*it15->lock())(e.joystickButton.joystickId, e.joystickButton.button);
					}
				}
				break;

			case sf::Event::JoystickMoved:
				for (it16 = _inputManager->_joystickMovedEventSubscribers.begin(); it16 != _inputManager->_joystickMovedEventSubscribers.end(); it16++) {
					if (it16->expired()) {
						_inputManager->_joystickMovedEventSubscribers.erase(it16);
					}
					else {
						(*it16->lock())(e.joystickMove.joystickId, e.joystickMove.axis, e.joystickMove.position);
					}
				}
				break;

			case sf::Event::JoystickConnected:
				for (it17 = _inputManager->_joystickConnectedEventSubscribers.begin(); it17 != _inputManager->_joystickConnectedEventSubscribers.end(); it17++) {
					if (it17->expired()) {
						_inputManager->_joystickConnectedEventSubscribers.erase(it17);
					}
					else {
						(*it17->lock())(e.joystickConnect.joystickId);
					}
				}
				break;

			case sf::Event::JoystickDisconnected:
				for (it18 = _inputManager->_joystickDisconnectedEventSubscribers.begin(); it18 != _inputManager->_joystickDisconnectedEventSubscribers.end(); it18++) {
					if (it18->expired()) {
						_inputManager->_joystickDisconnectedEventSubscribers.erase(it18);
					}
					else {
						(*it18->lock())(e.joystickConnect.joystickId);
					}
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

	void InputManager::subscribeToCloseEvent(std::shared_ptr < std::function < void() > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_closedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToResizeEvent(std::shared_ptr < std::function < void(unsigned int, unsigned int) > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_resizedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToTextEnteredEvent(std::shared_ptr < std::function < void(sf::String) > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_textEnteredEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToGainedFocusEvent(std::shared_ptr < std::function < void() > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_gainedFocusEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToLostFocusEvent(std::shared_ptr < std::function < void() > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_lostFocusEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToKeyPressedEvent(std::shared_ptr < std::function < void(sf::Keyboard::Key) > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_keyPressedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToKeyReleasedEvent(std::shared_ptr < std::function < void(sf::Keyboard::Key) > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_keyReleasedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToMouseButtonPressedEvent(std::shared_ptr < std::function < void(sf::Mouse::Button, int, int) > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_mouseButtonPressedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToMouseButtonReleasedEvent(std::shared_ptr < std::function < void(sf::Mouse::Button, int, int) > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_mouseButtonReleasedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToMouseWheelScrolledEvent(std::shared_ptr < std::function < void(sf::Mouse::Wheel, float, int, int) > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_mouseWheelScrolledEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToMouseMovedEvent(std::shared_ptr < std::function < void(int, int) > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_mouseMovedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToMouseEnteredEvent(std::shared_ptr < std::function < void() > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_mouseEnteredEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToMouseLeftEvent(std::shared_ptr < std::function < void() > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_mouseLeftEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToJoystickButtonPressedEvent(std::shared_ptr < std::function < void(unsigned int, unsigned int) > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_joystickButtonPressedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToJoystickButtonReleasedEvent(std::shared_ptr < std::function < void(unsigned int, unsigned int) > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_joystickButtonReleasedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToJoystickMovedEvent(std::shared_ptr < std::function < void(unsigned int, sf::Joystick::Axis, float) > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_joystickMovedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToJoystickConnectedEvent(std::shared_ptr < std::function < void(unsigned int) > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_joystickConnectedEventSubscribers.push_back(subscriber);
	}

	void InputManager::subscribeToJoystickDisconnectedEvent(std::shared_ptr < std::function < void(unsigned int) > > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		_inputManager->_joystickDisconnectedEventSubscribers.push_back(subscriber);
	}

}