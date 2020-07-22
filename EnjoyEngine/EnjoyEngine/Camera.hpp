#pragma once

#include "Vector2D.hpp"

#include "SFML/Graphics.hpp"

namespace EE {
	/// <summary>
	/// Game Camera class
	/// </summary>
	struct Camera {
		/// <summary>
		/// Camera's view
		/// </summary>
		sf::View view = sf::View(sf::Vector2f{ 400.f, 300.f }, sf::Vector2f{ 800.f, 600.f });
	};
}
