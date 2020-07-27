#include "pch.h"

#include "GameObject.hpp"

namespace EE {
	GameObject::GameObject() {}

	GameObject::~GameObject() {
		GameData::ecs().destroyEntity(_entity);
		delete _entity;
	}

	void GameObject::update() {}

	EntityHandle GameObject::getEntity() {
		return _entity;
	}


}