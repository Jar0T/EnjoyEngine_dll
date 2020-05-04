#pragma once

// System headers

// My headers
#include "Game.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API Time {
	private:
		static Time* _time;
		float _deltaTime;
		float _elapsedTime;
		sf::Clock _clock;

		Time();
		Time(const Time&) = delete;
		Time& operator=(const Time&) = delete;

		static void updateTime();

		friend int Game::Play();

	public:
		~Time();

		static float deltaTime();

	};
}