#pragma once

#include "Game.hpp"

#pragma region game_data
#include "GameData.hpp"
#pragma endregion

#pragma region helpers
#include "Vector2D.hpp"
#pragma endregion

#pragma region managers
#include "SoundManager.hpp"
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

#pragma region ecs
#include "ECSComponent.hpp"
#include "ECSSystem.hpp"
#include "ecs.hpp"
#pragma endregion

#pragma region game_object
#include "GameObject.hpp"
#include "Camera.hpp"
#pragma endregion