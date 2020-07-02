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
	/// <summary>
	/// Class storing game window
	/// </summary>
	class ENJOYENGINE_API GameData {
	private:
		static GameData* _gameData;

		std::shared_ptr<sf::RenderWindow> _window;
		std::string _title;

		GameData();
		GameData(int width, int height);
		GameData(const GameData&) = delete;
		GameData& operator=(const GameData&) = delete;

	public:
		~GameData();

		/// <summary>
		/// Getter for game window
		/// </summary>
		/// <returns>Reference to <c>sf::RenderWindow</c></returns>
		static sf::RenderWindow& window();

		/// <summary>
		/// Sets window size
		/// </summary>
		/// <param name="width">Window width in pixels</param>
		/// <param name="height">Window height in pixels</param>
		static void setWindowSize(int width, int height);
		/// <summary>
		/// Sets window title
		/// </summary>
		/// <param name="title">New window title</param>
		static void setWindowTitle(std::string title);
		/// <summary>
		/// Sets window fullscreen mode
		/// </summary>
		/// <param name="fullscreen">true if window should be fullscreen, false otherwise</param>
		static void setWindowFullscreen(bool fullscreen);
		/// <summary>
		/// Method called from event handler when window is resized
		/// </summary>
		static void onWindowResize();

	};
}
