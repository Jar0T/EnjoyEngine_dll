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
	/// <summary>
	/// Class managing time elapsed between frames
	/// </summary>
	class ENJOYENGINE_API Time {
	private:
		static Time* _time;
		float _deltaTime;
		float _elapsedTime;
		sf::Clock _clock;

		Time();
		Time(const Time&) = delete;
		Time& operator=(const Time&) = delete;

		/// <summary>
		/// Method for updating deltaTime. Can only be used by Game class.
		/// </summary>
		static void updateTime();

		friend int Game::Play();

	public:
		~Time();

		/// <summary>
		/// Method for getting deltaTime
		/// </summary>
		/// <returns>Time elapsed from last frame as float</returns>
		static float deltaTime();

	};
}