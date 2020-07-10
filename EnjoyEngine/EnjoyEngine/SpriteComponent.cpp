#include "pch.h"
//
//#include "SpriteComponent.hpp"
//
//namespace EE {
//	SpriteComponent::SpriteComponent(int spriteWidth, int spriteHeight) {
//		_FPS = 1;
//		_frameTime = 1.f;
//		_acctualFrameTime = 0.f;
//		_activeAnimationIndex = -1;
//		_activeSpriteIndex = -1;
//		_spriteWidth = spriteWidth;
//		_spriteHeight = spriteHeight;
//		_textureID = -1;
//		_layer = -1;
//	}
//
//	SpriteComponent::~SpriteComponent() {}
//
//	void SpriteComponent::setFPS(int FPS) {
//		_FPS = FPS;
//		_frameTime = 1.f / (float)FPS;
//	}
//
//	int SpriteComponent::getFPS() {
//		return _FPS;
//	}
//
//	sf::Sprite* SpriteComponent::getActiveSprite() {
//		if(_activeAnimationIndex > -1 && _activeSpriteIndex > -1)
//			return &_animations.at(_activeAnimationIndex).at(_activeSpriteIndex);
//		return nullptr;
//	}
//
//	void SpriteComponent::addAnimation(int numberOfFrames, int heightOffset) {
//		std::vector<sf::Sprite> animation;
//		for (int i = 0; i < numberOfFrames; i++) {
//			sf::Sprite sprite;
//			sprite.setTexture(TextureManager::getTexture(_textureID));
//			sprite.setTextureRect(sf::IntRect(i * _spriteWidth, heightOffset, _spriteWidth, _spriteHeight));
//			animation.push_back(sprite);
//		}
//		_animations.push_back(animation);
//		_activeAnimationIndex = 0;
//		_activeSpriteIndex = 0;
//	}
//
//	void SpriteComponent::setTexture(int textureID) {
//		_textureID = textureID;
//	}
//
//	void SpriteComponent::updateFrameTime() {
//		_acctualFrameTime += Time::deltaTime();
//		if (_acctualFrameTime > _frameTime) {
//			_acctualFrameTime -= _frameTime;
//			_activeSpriteIndex++;
//		}
//		if (_activeSpriteIndex >= _animations[_activeAnimationIndex].size())
//			_activeSpriteIndex = 0;
//	}
//
//	void SpriteComponent::changeAnimation(int animationIndex) {
//		if (animationIndex >= (int)_animations.size())
//			_activeAnimationIndex = animationIndex - (int)_animations.size();
//		else if (animationIndex < 0)
//			_activeAnimationIndex = (int)_animations.size() - 1;
//		else
//			_activeAnimationIndex = animationIndex;
//		_acctualFrameTime = 0.f;
//		_activeSpriteIndex = 0;
//	}
//
//	int SpriteComponent::getActiveAnimationIndex() {
//		return _activeAnimationIndex;
//	}
//
//	int SpriteComponent::getActiveSpriteIndex() {
//		return _activeSpriteIndex;
//	}
//
//	int& SpriteComponent::layer() {
//		return _layer;
//	}
//
//	void SpriteComponent::setSpriteOrigin(float x, float y) {
//		for (auto& animation : _animations) {
//			for (auto& sprite : animation) {
//				sprite.setOrigin(x, y);
//			}
//		}
//	}
//
//	void SpriteComponent::setSpriteOrigin(Origin origin) {
//		switch (origin) {
//		case EE::SpriteComponent::Origin::TOP_LEFT:
//			setSpriteOrigin(0.f, 0.f);
//			break;
//		case EE::SpriteComponent::Origin::TOP_MIDDLE:
//			setSpriteOrigin(0.f, (float)_spriteWidth / 2.f);
//			break;
//		case EE::SpriteComponent::Origin::TOP_RIGHT:
//			setSpriteOrigin(0.f, (float)_spriteWidth);
//			break;
//		case EE::SpriteComponent::Origin::MIDDLE_LEFT:
//			setSpriteOrigin((float)_spriteHeight / 2.f, 0.f);
//			break;
//		case EE::SpriteComponent::Origin::MIDDLE:
//			setSpriteOrigin((float)_spriteHeight / 2.f, (float)_spriteWidth / 2.f);
//			break;
//		case EE::SpriteComponent::Origin::MIDDLE_RIGHT:
//			setSpriteOrigin((float)_spriteHeight / 2.f, (float)_spriteWidth);
//			break;
//		case EE::SpriteComponent::Origin::BOTTOM_LEFT:
//			setSpriteOrigin((float)_spriteHeight, 0.f);
//			break;
//		case EE::SpriteComponent::Origin::BOTTOM_MIDDLE:
//			setSpriteOrigin((float)_spriteHeight, (float)_spriteWidth / 2.f);
//			break;
//		case EE::SpriteComponent::Origin::BOTTOM_RIGHT:
//			setSpriteOrigin((float)_spriteHeight, (float)_spriteWidth);
//			break;
//		default:
//			break;
//		}
//	}
//
//	void SpriteComponent::setSpritePosition(float x, float y) {
//		for (auto& animation : _animations) {
//			for (auto& sprite : animation) {
//				sprite.setPosition(x, y);
//			}
//		}
//	}
//
//}