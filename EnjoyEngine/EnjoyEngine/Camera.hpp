#pragma once

#include "Vector2D.hpp"

#include "SFML/Graphics.hpp"

namespace EE {
	/// <summary>
	/// Game Camera class
	/// </summary>
	struct Camera {
		/// <summary>
		/// Camera's view (but you should use Camera's methods to set size and position)
		/// </summary>
		sf::View view = sf::View(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ 1280.f, 720.f });

		/// <summary>
		/// Sets position of camera (center)
		/// </summary>
		/// <param name="x">X offset of camera</param>
		/// <param name="y">Y offset of camera</param>
		void setCenter(float x, float y) {
			view.setCenter(x, y);
		}

		/// <summary>
		/// Sets size of area visible to camera
		/// </summary>
		/// <param name="width">Area's width</param>
		/// <param name="height">Area's height</param>
		void setSize(float width, float height) {
			view.setSize(width * _zoom, height * _zoom);
			_width = width;
			_height = height;
		}

		/// <summary>
		/// Sets camera's zoom
		/// </summary>
		/// <param name="zoom">New zoom value</param>
		void setZoom(float zoom) {
			_zoom = zoom;
			view.setSize(_width * _zoom, _height * _zoom);
		}

		/// <summary>
		/// Getter for camera's zoom
		/// </summary>
		/// <returns>Camera's zoom</returns>
		float getZoom() { return _zoom; }
		/// <summary>
		/// Getter for visible area's width
		/// </summary>
		/// <returns>Width</returns>
		float getWidth() { return _width; }
		/// <summary>
		/// Getter for visible area's height
		/// </summary>
		/// <returns>Height</returns>
		float getHeight() { return _height; }
		/// <summary>
		/// Getter for visible area's size
		/// </summary>
		/// <returns>Vector{ width, height }</returns>
		Vector2D<float> getSize() { return Vector2D<float>{_width, _height}; }
		/// <summary>
		/// Getter for camera's position
		/// </summary>
		/// <returns>Vector{ x, y }</returns>
		Vector2D<float> getCenter() { return Vector2D<float>{view.getCenter().x, view.getCenter().y}; }

	private:
		float _zoom = 1.f;
		float _width = 1280.f;
		float _height = 720.f;
	};
}
