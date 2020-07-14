#pragma once

#undef min
#undef max

#include <vector>

#include "SFML/Graphics.hpp"

#include "ECSComponent.hpp"
#include "TextureManager.hpp"
#include "Time.hpp"

namespace EE {
	enum class Origin {
		TOP_LEFT,
		TOP_MIDDLE,
		TOP_RIGHT,
		MIDDLE_LEFT,
		MIDDLE,
		MIDDLE_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_MIDDLE,
		BOTTOM_RIGHT
	};

	struct SpriteComponent : public ECSComponent<SpriteComponent> {
		float _FPS;
		float _frameTime;
		float _acctualFrameTime;
		std::vector<std::vector<sf::Sprite>> _animations;
		int _activeAnimationIndex;
		int _activeSpriteIndex;
		int _spriteWidth;
		int _spriteHeight;
		int _textureID;
		int _layer;

		SpriteComponent(int spriteWidth, int spriteHeight) {
			_spriteHeight = spriteHeight;
			_spriteWidth = spriteWidth;
		}

		sf::Sprite* getActiveSprite() {
			if (_activeAnimationIndex > -1 && _activeSpriteIndex > -1)
				return &_animations.at(_activeAnimationIndex).at(_activeSpriteIndex);
			return nullptr;
		}
		void addAnimation(int numberOfFrames, int heightOffset) {
			std::vector<sf::Sprite> animation;
			for (int i = 0; i < numberOfFrames; i++) {
				sf::Sprite sprite;
				sprite.setTexture(TextureManager::getTexture(_textureID));
				sprite.setTextureRect(sf::IntRect(i * _spriteWidth, heightOffset, _spriteWidth, _spriteHeight));
				animation.push_back(sprite);
			}
			_animations.push_back(animation);
			_activeAnimationIndex = 0;
			_activeSpriteIndex = 0;
		}
		void updateFrameTime() {
			_acctualFrameTime += Time::deltaTime();
			if (_acctualFrameTime > _frameTime) {
				_acctualFrameTime -= _frameTime;
				_activeSpriteIndex++;
			}
			if (_activeSpriteIndex >= _animations[_activeAnimationIndex].size())
				_activeSpriteIndex = 0;
		}
		void changeAnimation(int animationIndex) {
			if (animationIndex >= (int)_animations.size())
				_activeAnimationIndex = animationIndex - (int)_animations.size();
			else if (animationIndex < 0)
				_activeAnimationIndex = (int)_animations.size() - 1;
			else
				_activeAnimationIndex = animationIndex;
			_acctualFrameTime = 0.f;
			_activeSpriteIndex = 0;
		}
		void setSpriteOrigin(float x, float y) {
			for (auto& animation : _animations) {
				for (auto& sprite : animation) {
					sprite.setOrigin(x, y);
				}
			}
		}
		void setSpriteOrigin(Origin origin) {
			switch (origin) {
			case Origin::TOP_LEFT:
				setSpriteOrigin(0.f, 0.f);
				break;
			case Origin::TOP_MIDDLE:
				setSpriteOrigin(0.f, (float)_spriteWidth / 2.f);
				break;
			case Origin::TOP_RIGHT:
				setSpriteOrigin(0.f, (float)_spriteWidth);
				break;
			case Origin::MIDDLE_LEFT:
				setSpriteOrigin((float)_spriteHeight / 2.f, 0.f);
				break;
			case Origin::MIDDLE:
				setSpriteOrigin((float)_spriteHeight / 2.f, (float)_spriteWidth / 2.f);
				break;
			case Origin::MIDDLE_RIGHT:
				setSpriteOrigin((float)_spriteHeight / 2.f, (float)_spriteWidth);
				break;
			case Origin::BOTTOM_LEFT:
				setSpriteOrigin((float)_spriteHeight, 0.f);
				break;
			case Origin::BOTTOM_MIDDLE:
				setSpriteOrigin((float)_spriteHeight, (float)_spriteWidth / 2.f);
				break;
			case Origin::BOTTOM_RIGHT:
				setSpriteOrigin((float)_spriteHeight, (float)_spriteWidth);
				break;
			default:
				break;
			}
		}
		void setSpritePosition(float x, float y) {
			for (auto& animation : _animations) {
				for (auto& sprite : animation) {
					sprite.setPosition(x, y);
				}
			}
		}
		void setFPS(float FPS) {
			_FPS = FPS;
			_frameTime = 1.f / FPS;
		}
	};
}