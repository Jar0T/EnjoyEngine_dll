#pragma once

#include <stack>
#include <memory>

#include "State.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	/// <summary>
	/// Class managing game states. Created as singletone
	/// </summary>
	class ENJOYENGINE_API StateMachine {
	private:
		static StateMachine* _stateMachine;
		std::stack<std::shared_ptr<State>> *_states;

		StateMachine();
		StateMachine(const StateMachine&) = delete;
		StateMachine& operator=(const StateMachine&) = delete;

	public:
		~StateMachine();

		/// <summary>
		/// Method adding new state to states stack
		/// </summary>
		/// <param name="state"><c>std::shared_ptr</c> to a state</param>
		/// <param name="isReplacing">Tells if previous state should be removed from stack. Default value is true</param>
		static void addState(std::shared_ptr<State> state, bool isReplacing = true);
		/// <summary>
		/// Method for manual removing of states from stack
		/// </summary>
		static void removeState();
		/// <summary>
		/// Method for getting active state from stack
		/// </summary>
		/// <returns><c>std::shared_ptr</c> to active state</returns>
		static std::shared_ptr<State> getActiveState();

	};
}
