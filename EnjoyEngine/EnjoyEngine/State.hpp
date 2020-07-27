#pragma once

#include "GameData.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	/// <summary>
	/// <para>Base state class. Pure virtual.</para>
	/// <para>Use this class while creating your own states</para>
	/// </summary>
	class ENJOYENGINE_API State {
	private:

	public:
		State() {};
		virtual ~State();

		/// <summary>
		/// <para>Called every frame. Call your updates here.</para>
		/// <para>Override this method in your state.</para>
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// Displays rendered images. You don't have to override it
		/// </summary>
		virtual void display();
	};
}
