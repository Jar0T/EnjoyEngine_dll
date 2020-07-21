#pragma once

#include "Vector2D.hpp"

#include "SFML/Graphics.hpp"

namespace EE {
	/// <summary>
	/// Game Camera class
	/// </summary>
	struct Camera {
		/// <summary>
		/// Camera's position
		/// </summary>
		Vector2D<float> position = Vector2D<float>{ 0.f, 0.f };
		/// <summary>
		/// Camera's view
		/// </summary>
		sf::View view = sf::View(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ 800.f, 600.f });
	};
}
