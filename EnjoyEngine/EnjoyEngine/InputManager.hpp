#pragma once

#include <memory>
#include <map>
#include <functional>

#include "SFML/Window.hpp"
#include "GameData.hpp"
#include "Vector2D.hpp"
#include "Game.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	struct Joystick {
		unsigned int joystick;
		unsigned int button;
		sf::Joystick::Axis axis;
	};

	struct Keyboard {
		sf::Keyboard::Key key;
	};

	struct Mouse {
		sf::Mouse::Button button;
	};

	class ENJOYENGINE_API InputManager {
	private:
		static InputManager* _inputManager;

		std::map<std::string, Joystick> _joystick;
		std::map<std::string, Keyboard> _keyboard;
		std::map<std::string, Mouse> _mouse;

		std::map<unsigned int, std::map<unsigned int, std::pair<bool, bool>>> _joystickButtonsStates;
		std::map<sf::Keyboard::Key, std::pair<bool, bool>> _keyboardKeysStates;
		std::map<sf::Mouse::Button, std::pair<bool, bool>> _mouseButtonsStates;

		std::vector< std::weak_ptr< std::function< void() > > > _closedEventSubscribers;
		std::vector< std::weak_ptr< std::function< void(unsigned int, unsigned int) > > > _resizedEventSubscribers;
		std::vector< std::weak_ptr< std::function< void(sf::String) > > > _textEnteredEventSubscribers;
		std::vector< std::weak_ptr< std::function< void() > > > _gainedFocusEventSubscribers;
		std::vector< std::weak_ptr< std::function< void() > > > _lostFocusEventSubscribers;
		std::vector< std::weak_ptr< std::function< void(sf::Keyboard::Key) > > > _keyPressedEventSubscribers;
		std::vector< std::weak_ptr< std::function< void(sf::Keyboard::Key) > > > _keyReleasedEventSubscribers;
		std::vector< std::weak_ptr< std::function< void(sf::Mouse::Button, int, int) > > > _mouseButtonPressedEventSubscribers;
		std::vector< std::weak_ptr< std::function< void(sf::Mouse::Button, int, int) > > > _mouseButtonReleasedEventSubscribers;
		std::vector< std::weak_ptr< std::function< void(sf::Mouse::Wheel, float, int, int) > > > _mouseWheelScrolledEventSubscribers;
		std::vector< std::weak_ptr< std::function< void(int, int) > > > _mouseMovedEventSubscribers;
		std::vector< std::weak_ptr< std::function< void() > > > _mouseEnteredEventSubscribers;
		std::vector< std::weak_ptr< std::function< void() > > > _mouseLeftEventSubscribers;
		std::vector< std::weak_ptr< std::function< void(unsigned int, unsigned int) > > > _joystickButtonPressedEventSubscribers;
		std::vector< std::weak_ptr< std::function< void(unsigned int, unsigned int) > > > _joystickButtonReleasedEventSubscribers;
		std::vector< std::weak_ptr< std::function< void(unsigned int, sf::Joystick::Axis, float) > > > _joystickMovedEventSubscribers;
		std::vector< std::weak_ptr< std::function< void(unsigned int) > > > _joystickConnectedEventSubscribers;
		std::vector< std::weak_ptr< std::function< void(unsigned int) > > > _joystickDisconnectedEventSubscribers;

		InputManager();
		InputManager(const InputManager&) = delete;
		InputManager& operator=(const InputManager&) = delete;

		static void updateButtonsStates();
		static void handleEvents();

		friend int Game::Play();

	public:
		~InputManager();

		static float getAxis(std::string axisName);
		static bool getButtonDown(std::string buttonName);
		static bool getButtonUp(std::string buttonName);
		static bool getButtonPressed(std::string buttonName);
		static bool getButtonReleased(std::string buttonName);
		static bool getKeyDown(std::string keyName);
		static bool getKeyUp(std::string keyName);
		static bool getKeyPressed(std::string keyName);
		static bool getKeyReleased(std::string keyName);
		static bool getMouseButtonDown(std::string mouseButtonName);
		static bool getMouseButtonUp(std::string mouseButtonName);
		static bool getMouseButtonPressed(std::string mouseButtonName);
		static bool getMouseButtonReleased(std::string mouseButtonName);
		static Vector2D<int> getMousePosition();
		static Vector2D<int> getMousePositionRaw();

		static void setAxis(std::string axisName, sf::Joystick::Axis axis, unsigned int joystick);
		static void setButton(std::string buttonName, unsigned int button, unsigned int joystick);
		static void setKey(std::string keyName, sf::Keyboard::Key key);
		static void setMouseButton(std::string mouseButtonName, sf::Mouse::Button button);

		static void subscribeToCloseEvent(std::shared_ptr < std::function < void() > > subscriber);
		static void subscribeToResizeEvent(std::shared_ptr < std::function < void(unsigned int, unsigned int) > > subscriber);
		static void subscribeToTextEnteredEvent(std::shared_ptr < std::function < void(sf::String) > > subscriber);
		static void subscribeToGainedFocusEvent(std::shared_ptr < std::function < void() > > subscriber);
		static void subscribeToLostFocusEvent(std::shared_ptr < std::function < void() > > subscriber);
		static void subscribeToKeyPressedEvent(std::shared_ptr < std::function < void(sf::Keyboard::Key) > > subscriber);
		static void subscribeToKeyReleasedEvent(std::shared_ptr < std::function < void(sf::Keyboard::Key) > > subscriber);
		static void subscribeToMouseButtonPressedEvent(std::shared_ptr < std::function < void(sf::Mouse::Button, int, int) > > subscriber);
		static void subscribeToMouseButtonReleasedEvent(std::shared_ptr < std::function < void(sf::Mouse::Button, int, int) > > subscriber);
		static void subscribeToMouseWheelScrolledEvent(std::shared_ptr < std::function < void(sf::Mouse::Wheel, float, int, int) > > subscriber);
		static void subscribeToMouseMovedEvent(std::shared_ptr < std::function < void(int, int) > > subscriber);
		static void subscribeToMouseEnteredEvent(std::shared_ptr < std::function < void() > > subscriber);
		static void subscribeToMouseLeftEvent(std::shared_ptr < std::function < void() > > subscriber);
		static void subscribeToJoystickButtonPressedEvent(std::shared_ptr < std::function < void(unsigned int, unsigned int) > > subscriber);
		static void subscribeToJoystickButtonReleasedEvent(std::shared_ptr < std::function < void(unsigned int, unsigned int) > > subscriber);
		static void subscribeToJoystickMovedEvent(std::shared_ptr < std::function < void(unsigned int, sf::Joystick::Axis, float) > > subscriber);
		static void subscribeToJoystickConnectedEvent(std::shared_ptr < std::function < void(unsigned int) > > subscriber);
		static void subscribeToJoystickDisconnectedEvent(std::shared_ptr < std::function < void(unsigned int) > > subscriber);

	};
}
