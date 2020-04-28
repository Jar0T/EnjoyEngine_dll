// Precompiled headers
#include "pch.h"

// System headers

// My headers
#include "Game.hpp"
#include "Time.hpp"
#include "GameData.hpp"
#include "StateMachine.hpp"
#include "State.hpp"

namespace EE {
	int Game::Play() {
		float lastUpdate = 0.f;
		while (GameData::window().isOpen()) {
			Time::setDeltaTime(this->_clock.getElapsedTime().asSeconds() - lastUpdate);
			lastUpdate = this->_clock.getElapsedTime().asSeconds();

			std::shared_ptr<State> state = StateMachine::getActiveState();
			if (state != nullptr) {
				state->update();
				state->handleEvents();
			}
		}

		return 0;
	}
}