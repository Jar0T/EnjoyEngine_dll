#pragma once

#include "ECSComponent.hpp"
#include "Vector2D.hpp"

#include "SFML/Audio.hpp"

#define SOUND_DISTANCE_SCALING 50.f;

namespace EE {
	struct SoundListenerComponent : public ECSComponent<SoundListenerComponent>	{
		sf::Listener listener;

		void setPosition(Vector2D<float> position) {
			position /= SOUND_DISTANCE_SCALING;
			listener.setPosition(position.x, position.y, 0.f);
		}
		void setGlobalVolume(float volume) {
			listener.setGlobalVolume(volume);
		}
	};
}
