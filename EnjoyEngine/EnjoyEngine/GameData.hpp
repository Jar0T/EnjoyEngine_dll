#pragma once

#undef min
#undef max

// System headers
#include <limits>
#include <string>
#include <vector>
#include <map>

// SFML headers
#include "SFML/Graphics.hpp"

// My headers
#include "ecs.hpp"
#include "Camera.hpp"

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
		std::shared_ptr<ECS> _ecs;
		std::vector< std::shared_ptr< Camera > > _camera;
		std::shared_ptr< std::map< int, std::shared_ptr< sf::RenderTexture > > > _renderLayers;

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

		/// <summary>
		/// Getter for ECS
		/// </summary>
		/// <returns>Reference to ECS</returns>
		static ECS& ecs();

		/// <summary>
		/// Getter fot Camera
		/// </summary>
		/// <param name="index">Index of camera</param>
		/// <returns>Shared pointer to camera</returns>
		static std::shared_ptr<Camera> camera(size_t index);

		/// <summary>
		/// Method for adding new camera
		/// </summary>
		/// <returns>Index of added camera</returns>
		static size_t addCamera();

		/// <summary>
		/// Method for getting map of sf::RenderTextures
		/// </summary>
		/// <returns>shared pointer to map</returns>
		static std::shared_ptr< std::map< int, std::shared_ptr< sf::RenderTexture > > > renderLayers();

		/// <summary>
		/// Getter for render layer's keys sorted ascending
		/// </summary>
		/// <returns>Vector of keys</returns>
		static std::vector< int > getSortedRenderLayersKeys();

	};
}
