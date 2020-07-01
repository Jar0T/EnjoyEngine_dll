#pragma once

#undef min
#undef max

#include <vector>

#include "SFML/Graphics.hpp"

#include "Component.hpp"
#include "TextureManager.hpp"
#include "Time.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API SpriteComponent : public Component {
	private:
		int _FPS;
		float _frameTime;
		float _acctualFrameTime;
		std::vector<std::vector<sf::Sprite>> _animations;
		int _activeAnimationIndex;
		int _activeSpriteIndex;
		int _spriteWidth;
		int _spriteHeight;
		int _textureID;
		int _layer;

	public:
		SpriteComponent(int spriteWidth, int spriteHeight);
		~SpriteComponent();

		void setFPS(int FPS);
		int getFPS();

		sf::Sprite* getActiveSprite();

		void addAnimation(int numberOfFrames, int heightOffset);

		void setTexture(int textureID);

		void updateFrameTime();

		void changeAnimation(int animationIndex);
		int getActiveAnimationIndex();
		int getActiveSpriteIndex();

		int& layer();

	};
}