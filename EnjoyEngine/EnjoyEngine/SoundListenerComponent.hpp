//#pragma once
//
//#include "Component.hpp"
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
//	class ENJOYENGINE_API SoundListenerComponent : public Component {
//	private:
//		sf::Listener _listener;
//
//	public:
//		SoundListenerComponent();
//		~SoundListenerComponent();
//
//		void setPosition(Vector2D<float> position);
//		void setGlobalVolume(float volume);
//
//	};
//}
