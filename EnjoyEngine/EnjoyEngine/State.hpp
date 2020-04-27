#pragma once

namespace EE {
	class State {
	private:

	public:
		State() {};
		virtual ~State();

		virtual void update() = 0;
		virtual void handleEvents() = 0;

	};
}
