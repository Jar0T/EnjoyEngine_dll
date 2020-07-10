//#pragma once
//
//#include <map>
//#include <memory>
//
//#include "Component.hpp"
//#include "SoundManager.hpp"
//#include "Vector2D.hpp"
//
//#include "SFML/Audio.hpp"
//
//#ifdef ENJOYENGINE_EXPORTS
//#define ENJOYENGINE_API __declspec(dllexport)
//#else
//#define ENJOYENGINE_API __declspec(dllimport)
//#endif
//
//namespace EE {
//	class ENJOYENGINE_API SoundPlayerComponent : public Component {
//	private:
//		std::map<std::string, std::unique_ptr<sf::Sound>> _sound;
//
//	public:
//		SoundPlayerComponent();
//		~SoundPlayerComponent();
//		SoundPlayerComponent(const SoundPlayerComponent&) = delete;
//		SoundPlayerComponent& operator=(const SoundPlayerComponent&) = delete;
//
//		void addSound(unsigned int soundKey, std::string soundName);
//
//		void playSound(std::string soundName);
//		void pauseSound(std::string soundName);
//		void stopSound(std::string soundName);
//
//		void setSoundPosition(Vector2D<float> position);
//		void setSoundVolume(std::string soundName, float volume);
//		void setSoundLoop(std::string soundName, bool loop = true);
//	};
//}
