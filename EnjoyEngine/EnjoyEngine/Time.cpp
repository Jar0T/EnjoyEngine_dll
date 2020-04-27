// Precompiled headers
#include "pch.h"

// System headers

// My headers
#include "Time.hpp"

namespace EE {
	Time* Time::_time = 0;

	Time::Time() : _deltaTime(0.f) {}

	Time::~Time() {
		if (_time)
			delete _time;
	}

	float Time::deltaTime() {
		if (!_time)
			_time = new Time();
		return _time->_deltaTime;
	}

	void Time::setDeltaTime(float deltaTime) {
		if (!_time)
			_time = new Time();
		_time->_deltaTime = deltaTime;
	}
}
