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

		std::map < unsigned int, std::map < unsigned int, bool > > _joystickButtonsStates;
		std::map < sf::Keyboard::Key, bool > _keyboardKeysStates;
		std::map < sf::Mouse::Button, bool > _mouseButtonsStates;

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
		static bool getKeyDown(std::string keyName);
		static bool getKeyUp(std::string keyName);
		static bool getMouseButtonDown(std::string mouseButtonName);
		static bool getMouseButtonUp(std::string mouseButtonName);
		static Vector2D<int> getMousePosition();
		static Vector2D<int> getMousePositionRaw();

		static void setAxis(std::string axisName, sf::Joystick::Axis axis, unsigned int joystick);
		static void setButton(std::string buttonName, unsigned int button, unsigned int joystick);
		static void setKey(std::string keyName, sf::Keyboard::Key key);
		static void setMouseButton(std::string mouseButtonName, sf::Mouse::Button button);

		static std::shared_ptr< std::function < void() > > subscribeToCloseEvent(std::function < void() > subscriber);
		static std::shared_ptr< std::function < void(unsigned int, unsigned int) > > subscribeToResizeEvent(std::function < void(unsigned int, unsigned int) > subscriber);
		static std::shared_ptr< std::function < void(sf::String) > > subscribeToTextEnteredEvent(std::function < void(sf::String) > subscriber);
		static std::shared_ptr< std::function < void() > > subscribeToGainedFocusEvent(std::function < void() > subscriber);
		static std::shared_ptr< std::function < void() > > subscribeToLostFocusEvent(std::function < void() > subscriber);
		static std::shared_ptr< std::function < void(sf::Keyboard::Key) > > subscribeToKeyPressedEvent(std::function < void(sf::Keyboard::Key) > subscriber);
		static std::shared_ptr< std::function < void(sf::Keyboard::Key) > > subscribeToKeyReleasedEvent(std::function < void(sf::Keyboard::Key) > subscriber);
		static std::shared_ptr< std::function < void(sf::Mouse::Button, int, int) > > subscribeToMouseButtonPressedEvent(std::function < void(sf::Mouse::Button, int, int) > subscriber);
		static std::shared_ptr< std::function < void(sf::Mouse::Button, int, int) > > subscribeToMouseButtonReleasedEvent(std::function < void(sf::Mouse::Button, int, int) > subscriber);
		static std::shared_ptr< std::function < void(sf::Mouse::Wheel, float, int, int) > > subscribeToMouseWheelScrolledEvent(std::function < void(sf::Mouse::Wheel, float, int, int) > subscriber);
		static std::shared_ptr< std::function < void(int, int) > > subscribeToMouseMovedEvent(std::function < void(int, int) > subscriber);
		static std::shared_ptr< std::function < void() > > subscribeToMouseEnteredEvent(std::function < void() > subscriber);
		static std::shared_ptr< std::function < void() > > subscribeToMouseLeftEvent(std::function < void() > subscriber);
		static std::shared_ptr< std::function < void(unsigned int, unsigned int) > > subscribeToJoystickButtonPressedEvent(std::function < void(unsigned int, unsigned int) > subscriber);
		static std::shared_ptr< std::function < void(unsigned int, unsigned int) > > subscribeToJoystickButtonReleasedEvent(std::function < void(unsigned int, unsigned int) > subscriber);
		static std::shared_ptr< std::function < void(unsigned int, sf::Joystick::Axis, float) > > subscribeToJoystickMovedEvent(std::function < void(unsigned int, sf::Joystick::Axis, float) > subscriber);
		static std::shared_ptr< std::function < void(unsigned int) > > subscribeToJoystickConnectedEvent(std::function < void(unsigned int) > subscriber);
		static std::shared_ptr<std::function < void(unsigned int) > > subscribeToJoystickDisconnectedEvent(std::function < void(unsigned int) > subscriber);
	};
}
