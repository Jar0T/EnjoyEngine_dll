#pragma once

#undef min
#undef max

#include <map>

#include "SFML/Graphics.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API TextureManager {
	private:
		static TextureManager* _textureManager;

		TextureManager();
		TextureManager(const TextureManager&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;

		std::map<unsigned int, sf::Texture*> _textureMap;

	public:
		static void loadTexture(const char* fileName, unsigned int key);
		static void deleteTexture(unsigned int key);
		static sf::Texture& getTexture(unsigned int key);

	};
}
