// Precompiled headers
#include "pch.h"

// System headers

// My headers
#include "StateMachine.hpp"

namespace EE {
	StateMachine* StateMachine::_stateMachine = 0;

	StateMachine::StateMachine() {
		_states = new std::stack<std::shared_ptr<State>>;
	}

	StateMachine::~StateMachine() {
		while (_stateMachine->_states->size() > 0)
			_stateMachine->_states->pop();
		delete _states;
	}

	void StateMachine::addState(std::shared_ptr<State> state, bool isReplacing) {
		if (_stateMachine == 0)
			_stateMachine = new StateMachine();

		if (isReplacing) {
			if (_stateMachine->_states->size() > 0)
				_stateMachine->_states->pop();
			_stateMachine->_states->push(state);
		}
		else {
			_stateMachine->_states->push(state);
		}
	}

	std::shared_ptr<State> StateMachine::getActiveState() {
		if (_stateMachine == 0)
			_stateMachine = new StateMachine();

		if (_stateMachine->_states->size() > 0)
			return _stateMachine->_states->top();
		else
			return nullptr;
	}
}
