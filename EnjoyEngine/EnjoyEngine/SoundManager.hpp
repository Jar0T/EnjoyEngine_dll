#pragma once

#include <map>
#include <memory>

#include "SFML/Audio.hpp"

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API SoundManager {
	private:
		static SoundManager* _soundManager;

		SoundManager();
		SoundManager(const SoundManager&) = delete;
		SoundManager& operator=(const SoundManager&) = delete;

		std::map<unsigned int, std::unique_ptr<sf::SoundBuffer>> _soundMap;

	public:
		~SoundManager();

		static void loadSound(const char* fileName, unsigned int key);
		static void deleteSound(unsigned int key);
		static sf::SoundBuffer& getSound(unsigned int key);

	};
}