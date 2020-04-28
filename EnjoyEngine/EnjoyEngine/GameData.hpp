#pragma once

#undef min
#undef max

// System headers
#include <limits>
#include <string>

// My headers
#include "SFML/Graphics.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API GameData {
	private:
		static GameData* _gameData;

		sf::RenderWindow* _window;
		std::string _title;

		GameData();
		GameData(int width, int height);
		GameData(const GameData&) = delete;
		GameData& operator=(const GameData&) = delete;

	public:
		~GameData();

		static sf::RenderWindow& window();
		static void setWindowSize(int width, int height);
		static void setWindowTitle(std::string title);
		static void setWindowFullscreen(bool fullscreen);

	};
}
