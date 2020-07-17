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
				it1 = _inputManager->_closedEventSubscribers.begin();
				while (it1 != _inputManager->_closedEventSubscribers.end()) {
					if (it1->expired()) {
						it1 = _inputManager->_closedEventSubscribers.erase(it1);
					}
					else {
						(*it1->lock())();
						++it1;
					}
				}
				break;

			case sf::Event::Resized:
				GameData::onWindowResize();
				it2 = _inputManager->_resizedEventSubscribers.begin();
				while (it2 != _inputManager->_resizedEventSubscribers.end()) {
					if (it2->expired()) {
						it2 = _inputManager->_resizedEventSubscribers.erase(it2);
					}
					else {
						(*it2->lock())(e.size.width, e.size.height);
						++it2;
					}
				}
				break;

			case sf::Event::TextEntered:
				it3 = _inputManager->_textEnteredEventSubscribers.begin();
				while (it3 != _inputManager->_textEnteredEventSubscribers.end()) {
					if (it3->expired()) {
						it3 = _inputManager->_textEnteredEventSubscribers.erase(it3);
					}
					else {
						(*it3->lock())(e.text.unicode);
						++it3;
					}
				}
				break;

			case sf::Event::GainedFocus:
				it4 = _inputManager->_gainedFocusEventSubscribers.begin();
				while (it4 != _inputManager->_gainedFocusEventSubscribers.end()) {
					if (it4->expired()) {
						it4 = _inputManager->_gainedFocusEventSubscribers.erase(it4);
					}
					else {
						(*it4->lock())();
						++it4;
					}
				}
				break;

			case sf::Event::LostFocus:
				it5 = _inputManager->_lostFocusEventSubscribers.begin();
				while (it5 != _inputManager->_lostFocusEventSubscribers.end()) {
					if (it5->expired()) {
						it5 = _inputManager->_lostFocusEventSubscribers.erase(it5);
					}
					else {
						(*it5->lock())();
						++it5;
					}
				}
				break;

			case sf::Event::KeyPressed:
				it6 = _inputManager->_keyPressedEventSubscribers.begin();
				while (it6 != _inputManager->_keyPressedEventSubscribers.end()) {
					if (it6->expired()) {
						it6 = _inputManager->_keyPressedEventSubscribers.erase(it6);
					}
					else {
						(*it6->lock())(e.key.code);
						++it6;
					}
				}
				break;

			case sf::Event::KeyReleased:
				it7 = _inputManager->_keyReleasedEventSubscribers.begin();
				while (it7 != _inputManager->_keyReleasedEventSubscribers.end()) {
					if (it7->expired()) {
						it7 = _inputManager->_keyReleasedEventSubscribers.erase(it7);
					}
					else {
						(*it7->lock())(e.key.code);
						++it7;
					}
				}
				break;

			case sf::Event::MouseButtonPressed:
				it8 = _inputManager->_mouseButtonPressedEventSubscribers.begin();
				while (it8 != _inputManager->_mouseButtonPressedEventSubscribers.end()) {
					if (it8->expired()) {
						it8 = _inputManager->_mouseButtonPressedEventSubscribers.erase(it8);
					}
					else {
						(*it8->lock())(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
						++it8;
					}
				}
				break;

			case sf::Event::MouseButtonReleased:
				it9 = _inputManager->_mouseButtonReleasedEventSubscribers.begin();
				while (it9 != _inputManager->_mouseButtonReleasedEventSubscribers.end()) {
					if (it9->expired()) {
						it9 = _inputManager->_mouseButtonReleasedEventSubscribers.erase(it9);
					}
					else {
						(*it9->lock())(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
						++it9;
					}
				}
				break;

			case sf::Event::MouseWheelScrolled:
				it10 = _inputManager->_mouseWheelScrolledEventSubscribers.begin();
				while (it10 != _inputManager->_mouseWheelScrolledEventSubscribers.end()) {
					if (it10->expired()) {
						it10 = _inputManager->_mouseWheelScrolledEventSubscribers.erase(it10);
					}
					else {
						(*it10->lock())(e.mouseWheelScroll.wheel, e.mouseWheelScroll.delta, e.mouseWheelScroll.x, e.mouseWheelScroll.y);
						++it10;
					}
				}
				break;

			case sf::Event::MouseMoved:
				it11 = _inputManager->_mouseMovedEventSubscribers.begin();
				while (it11 != _inputManager->_mouseMovedEventSubscribers.end()) {
					if (it11->expired()) {
						it11 = _inputManager->_mouseMovedEventSubscribers.erase(it11);
					}
					else {
						(*it11->lock())(e.mouseMove.x, e.mouseMove.y);
						++it11;
					}
				}
				break;

			case sf::Event::MouseEntered:
				it12 = _inputManager->_mouseEnteredEventSubscribers.begin();
				while (it12 != _inputManager->_mouseEnteredEventSubscribers.end()) {
					if (it12->expired()) {
						it12 = _inputManager->_mouseEnteredEventSubscribers.erase(it12);
					}
					else {
						(*it12->lock())();
						++it12;
					}
				}
				break;

			case sf::Event::MouseLeft:
				it13 = _inputManager->_mouseLeftEventSubscribers.begin();
				while (it13 != _inputManager->_mouseLeftEventSubscribers.end()) {
					if (it13->expired()) {
						it13 = _inputManager->_mouseLeftEventSubscribers.erase(it13);
					}
					else {
						(*it13->lock())();
						++it13;
					}
				}
				break;

			case sf::Event::JoystickButtonPressed:
				it14 = _inputManager->_joystickButtonPressedEventSubscribers.begin();
				while (it14 != _inputManager->_joystickButtonPressedEventSubscribers.end()) {
					if (it14->expired()) {
						it14 = _inputManager->_joystickButtonPressedEventSubscribers.erase(it14);
					}
					else {
						(*it14->lock())(e.joystickButton.joystickId, e.joystickButton.button);
						++it14;
					}
				}
				break;

			case sf::Event::JoystickButtonReleased:
				it15 = _inputManager->_joystickButtonReleasedEventSubscribers.begin();
				while (it15 != _inputManager->_joystickButtonReleasedEventSubscribers.end()) {
					if (it15->expired()) {
						it15 = _inputManager->_joystickButtonReleasedEventSubscribers.erase(it15);
					}
					else {
						(*it15->lock())(e.joystickButton.joystickId, e.joystickButton.button);
						++it15;
					}
				}
				break;

			case sf::Event::JoystickMoved:
				it16 = _inputManager->_joystickMovedEventSubscribers.begin();
				while (it16 != _inputManager->_joystickMovedEventSubscribers.end()) {
					if (it16->expired()) {
						it16 = _inputManager->_joystickMovedEventSubscribers.erase(it16);
					}
					else {
						(*it16->lock())(e.joystickMove.joystickId, e.joystickMove.axis, e.joystickMove.position);
						++it16;
					}
				}
				break;

			case sf::Event::JoystickConnected:
				it17 = _inputManager->_joystickConnectedEventSubscribers.begin();
				while (it17 != _inputManager->_joystickConnectedEventSubscribers.end()) {
					if (it17->expired()) {
						it17 = _inputManager->_joystickConnectedEventSubscribers.erase(it17);
					}
					else {
						(*it17->lock())(e.joystickConnect.joystickId);
						++it17;
					}
				}
				break;

			case sf::Event::JoystickDisconnected:
				it18 = _inputManager->_joystickDisconnectedEventSubscribers.begin();
				while (it18 != _inputManager->_joystickDisconnectedEventSubscribers.end()) {
					if (it18->expired()) {
						it18 = _inputManager->_joystickDisconnectedEventSubscribers.erase(it18);
					}
					else {
						(*it18->lock())(e.joystickConnect.joystickId);
						++it18;
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

	std::shared_ptr< std::function < void() > > InputManager::subscribeToCloseEvent(std::function < void() > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void() > > f = std::make_shared< std::function < void() > >(subscriber);

		_inputManager->_closedEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void(unsigned int, unsigned int) > > InputManager::subscribeToResizeEvent(std::function < void(unsigned int, unsigned int) > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void(unsigned int, unsigned int) > > f = std::make_shared< std::function < void(unsigned int, unsigned int) > >(subscriber);

		_inputManager->_resizedEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void(sf::String) > > InputManager::subscribeToTextEnteredEvent(std::function < void(sf::String) > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void(sf::String) > > f = std::make_shared< std::function < void(sf::String) > >(subscriber);

		_inputManager->_textEnteredEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void() > > InputManager::subscribeToGainedFocusEvent(std::function < void() > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void() > > f = std::make_shared< std::function < void() > >(subscriber);

		_inputManager->_gainedFocusEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void() > > InputManager::subscribeToLostFocusEvent(std::function < void() > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void() > > f = std::make_shared< std::function < void() > >(subscriber);

		_inputManager->_lostFocusEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void(sf::Keyboard::Key) > > InputManager::subscribeToKeyPressedEvent(std::function < void(sf::Keyboard::Key) > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void(sf::Keyboard::Key) > > f = std::make_shared< std::function < void(sf::Keyboard::Key) > >(subscriber);

		_inputManager->_keyPressedEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void(sf::Keyboard::Key) > > InputManager::subscribeToKeyReleasedEvent(std::function < void(sf::Keyboard::Key) > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void(sf::Keyboard::Key) > > f = std::make_shared< std::function < void(sf::Keyboard::Key) > >(subscriber);

		_inputManager->_keyReleasedEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void(sf::Mouse::Button, int, int) > > InputManager::subscribeToMouseButtonPressedEvent(std::function < void(sf::Mouse::Button, int, int) > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void(sf::Mouse::Button, int, int) > > f = std::make_shared< std::function < void(sf::Mouse::Button, int, int) > >(subscriber);

		_inputManager->_mouseButtonPressedEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void(sf::Mouse::Button, int, int) > > InputManager::subscribeToMouseButtonReleasedEvent(std::function < void(sf::Mouse::Button, int, int) > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void(sf::Mouse::Button, int, int) > > f = std::make_shared< std::function < void(sf::Mouse::Button, int, int) > >(subscriber);

		_inputManager->_mouseButtonReleasedEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void(sf::Mouse::Wheel, float, int, int) > > InputManager::subscribeToMouseWheelScrolledEvent(std::function < void(sf::Mouse::Wheel, float, int, int) > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void(sf::Mouse::Wheel, float, int, int) > > f = std::make_shared< std::function < void(sf::Mouse::Wheel, float, int, int) > >(subscriber);

		_inputManager->_mouseWheelScrolledEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void(int, int) > > InputManager::subscribeToMouseMovedEvent(std::function < void(int, int) > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void(int, int) > > f = std::make_shared< std::function < void(int, int) > >(subscriber);

		_inputManager->_mouseMovedEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void() > > InputManager::subscribeToMouseEnteredEvent(std::function < void() > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void() > > f = std::make_shared< std::function < void() > >(subscriber);

		_inputManager->_mouseEnteredEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void() > > InputManager::subscribeToMouseLeftEvent(std::function < void() > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void() > > f = std::make_shared< std::function < void() > >(subscriber);

		_inputManager->_mouseLeftEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void(unsigned int, unsigned int) > > InputManager::subscribeToJoystickButtonPressedEvent(std::function < void(unsigned int, unsigned int) > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void(unsigned int, unsigned int) > > f = std::make_shared< std::function < void(unsigned int, unsigned int) > >(subscriber);

		_inputManager->_joystickButtonPressedEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void(unsigned int, unsigned int) > > InputManager::subscribeToJoystickButtonReleasedEvent(std::function < void(unsigned int, unsigned int) > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void(unsigned int, unsigned int) > > f = std::make_shared< std::function < void(unsigned int, unsigned int) > >(subscriber);

		_inputManager->_joystickButtonReleasedEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void(unsigned int, sf::Joystick::Axis, float) > > InputManager::subscribeToJoystickMovedEvent(std::function < void(unsigned int, sf::Joystick::Axis, float) > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void(unsigned int, sf::Joystick::Axis, float) > > f = std::make_shared< std::function < void(unsigned int, sf::Joystick::Axis, float) > >(subscriber);

		_inputManager->_joystickMovedEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr< std::function < void(unsigned int) > > InputManager::subscribeToJoystickConnectedEvent(std::function < void(unsigned int) > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr< std::function < void(unsigned int) > > f = std::make_shared< std::function < void(unsigned int) > >(subscriber);

		_inputManager->_joystickConnectedEventSubscribers.push_back(f);

		return f;
	}

	std::shared_ptr<std::function < void(unsigned int) > > InputManager::subscribeToJoystickDisconnectedEvent(std::function < void(unsigned int) > subscriber) {
		if (_inputManager == 0)
			_inputManager = new InputManager();

		std::shared_ptr<std::function < void(unsigned int) > > f = std::make_shared< std::function < void(unsigned int) > >(subscriber);

		_inputManager->_joystickDisconnectedEventSubscribers.push_back(f);

		return f;
	}

}