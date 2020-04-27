#pragma once

namespace EE {
	class State {
	private:

	public:
		State() {};
		virtual ~State() = 0;

		virtual void update() = 0;
		virtual void handleEvents() = 0;

	};
}
