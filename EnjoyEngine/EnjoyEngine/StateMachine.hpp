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
	class ENJOYENGINE_API StateMachine {
	private:
		static StateMachine* _stateMachine;
		std::stack<std::shared_ptr<State>> *_states;

		StateMachine();
		StateMachine(const StateMachine&) = delete;
		StateMachine& operator=(const StateMachine&) = delete;

	public:
		~StateMachine();

		static void addState(std::shared_ptr<State> state, bool isReplacing = true);
		static std::shared_ptr<State> getActiveState();

	};
}
