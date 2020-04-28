#pragma once

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	class ENJOYENGINE_API State {
	private:

	public:
		State() {};
		virtual ~State();

		virtual void update() = 0;
		virtual void handleEvents() = 0;

	};
}
