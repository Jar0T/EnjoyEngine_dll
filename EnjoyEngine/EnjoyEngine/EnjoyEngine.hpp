#pragma once

#include "Game.hpp"

#pragma region components
#include "Component.hpp"
#include "ComponentManager.hpp"
#include "AABBCollider2DComponent.hpp"
#include "CircleCollider2DComponent.hpp"
#include "SpriteComponent.hpp"
#include "Transform2DComponent.hpp"
#pragma endregion

#pragma region systems
#include "System.hpp"
#include "SystemManager.hpp"
#include "AABBvsAABBCollisionSystem.hpp"
#include "AABBvsCircleCollisionSystem.hpp"
#include "CirclevsCircleCollisionSystem.hpp"
#include "SpriteSystem.hpp"
#include "Transform2DSystem.hpp"
#pragma endregion

#pragma region entity
#include "Entity.hpp"
#include "EntityManager.hpp"
#pragma endregion

#pragma region game_data
#include "GameData.hpp"
#pragma endregion

#pragma region helpers
#include "Vector2D.hpp"
#pragma endregion

#pragma region managers
#include "TextureManager.hpp"
#include "InputManager.hpp"
#pragma endregion

#pragma region state_machine
#include "State.hpp"
#include "StateMachine.hpp"
#pragma endregion

#pragma region time
#include "Time.hpp"
#pragma endregion
