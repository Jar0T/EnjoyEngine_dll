// Precompiled headers
#include "pch.h"

// System headers

// My headers
#include "Game.hpp"
#include "Time.hpp"

namespace EE {
	int Game::Init() {


		return 0;
	}

	int Game::Play() {
		float lastUpdate = 0.f;
		while (1) {
			Time::setDeltaTime(this->_clock.getElapsedTime().asSeconds() - lastUpdate);
			lastUpdate = this->_clock.getElapsedTime().asSeconds();

			// update
			// handle events
		}

		return 0;
	}
}