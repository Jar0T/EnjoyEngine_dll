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
	/// <summary>
	/// <para>Main game class</para>
	/// <para>Contains game's main loop</para>
	/// </summary>
	class ENJOYENGINE_API Game {
	private:

	public:
		/// <summary>
		/// <para>Method starting game loop</para>
		/// <para>Before calling this method you need to add state to StateMachine</para>
		/// </summary>
		/// <returns>less than 0 if error</returns>
		int Play();

	};
}