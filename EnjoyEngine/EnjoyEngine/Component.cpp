#include "pch.h"

#include "Component.hpp"

namespace EE {
	Component::Component() {
		_stackLayer = -1;
	}

	Component::~Component() {

	}

	int Component::getStackLayer() {
		return _stackLayer;
	}

	void Component::setStackLayer(int stackLayer) {
		_stackLayer = stackLayer;
	}

}