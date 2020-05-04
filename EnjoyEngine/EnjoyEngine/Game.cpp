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
		while (GameData::window().isOpen()) {
			Time::updateTime();

			std::shared_ptr<State> state = StateMachine::getActiveState();
			if (state != nullptr) {
				state->update();
				state->handleEvents();
			}
		}

		return 0;
	}
}