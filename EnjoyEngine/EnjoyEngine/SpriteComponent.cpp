#include "pch.h"

#include "SpriteComponent.hpp"

namespace EE {
	SpriteComponent::SpriteComponent(int spriteWidth, int spriteHeight) {
		_FPS = 1;
		_frameTime = 1.f;
		_acctualFrameTime = 0.f;
		_activeAnimationIndex = -1;
		_activeSpriteIndex = -1;
		_spriteWidth = spriteWidth;
		_spriteHeight = spriteHeight;
		_textureID = -1;
	}

	SpriteComponent::~SpriteComponent() {}

	void SpriteComponent::setFPS(int FPS) {
		_FPS = FPS;
		_frameTime = 1.f / (float)FPS;
	}

	int SpriteComponent::getFPS() {
		return _FPS;
	}

	sf::Sprite* SpriteComponent::getActiveSprite() {
		if(_activeAnimationIndex > -1 && _activeSpriteIndex > -1)
			return &_animations.at(_activeAnimationIndex).at(_activeSpriteIndex);
		return nullptr;
	}

	void SpriteComponent::addAnimation(int numberOfFrames, int heightOffset) {
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

	void SpriteComponent::setTexture(int textureID) {
		_textureID = textureID;
	}

	void SpriteComponent::updateFrameTime() {
		_acctualFrameTime += Time::deltaTime();
		if (_acctualFrameTime > _frameTime) {
			_acctualFrameTime -= _frameTime;
			_activeSpriteIndex++;
		}
		if (_activeSpriteIndex >= _animations[_activeAnimationIndex].size())
			_activeSpriteIndex = 0;
	}

	void SpriteComponent::changeAnimation(int animationIndex) {
		if (animationIndex >= (int)_animations.size())
			_activeAnimationIndex = animationIndex - (int)_animations.size();
		else if (animationIndex < 0)
			_activeAnimationIndex = (int)_animations.size() - 1;
		else
			_activeAnimationIndex = animationIndex;
		_acctualFrameTime = 0.f;
		_activeSpriteIndex = 0;
	}

	int SpriteComponent::getActiveAnimationIndex() {
		return _activeAnimationIndex;
	}

	int SpriteComponent::getActiveSpriteIndex() {
		return _activeSpriteIndex;
	}


}