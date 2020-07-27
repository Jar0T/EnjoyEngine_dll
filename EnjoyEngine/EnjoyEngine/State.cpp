// Precompiled headers
#include "pch.h"

// System headers

// My headers
#include "State.hpp"

namespace EE {
	State::~State() {}
	
	void State::display() {
		GameData::window().clear();

		std::shared_ptr< std::map< int, std::shared_ptr< sf::RenderTexture > > > renderLayers = GameData::renderLayers();
		std::vector<int> keys = GameData::getSortedRenderLayersKeys();

		for (auto& key : keys) {
			(*renderLayers)[key]->display();
			sf::Sprite spr((*renderLayers)[key]->getTexture());
			GameData::window().draw(spr);
		}

		GameData::window().display();
	}
}
