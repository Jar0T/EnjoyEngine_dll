#pragma once

#undef min
#undef max

// System headers
#include <limits>

// My headers
#include "SFML/Graphics.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API Game {
	private:
		sf::Clock _clock;

	public:
		int Init();

		int Play();
	};
}