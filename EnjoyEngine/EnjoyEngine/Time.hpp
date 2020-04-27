#pragma once

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API Time {
	private:
		static Time* _time;
		float _deltaTime;

		Time();
		Time(const Time&) = delete;
		Time& operator=(const Time&) = delete;

	public:
		~Time();

		static float deltaTime();
		static void setDeltaTime(float deltaTime);

	};
}