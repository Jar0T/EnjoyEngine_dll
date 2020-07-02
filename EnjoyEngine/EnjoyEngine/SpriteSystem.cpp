#include "pch.h"

#include "SpriteSystem.hpp"

namespace EE {
	SpriteSystem::SpriteSystem() {

	}

	SpriteSystem::~SpriteSystem() {

	}

	void SpriteSystem::update() {
		std::vector<std::uint32_t> entities = EntityManager::getEntities();
		std::map<int, std::shared_ptr<sf::RenderTexture>> renderTextures;
		std::vector<int> keys;
		Vector2D<float> position{ 0.f, 0.f };
		std::shared_ptr<SpriteComponent> sprite;
		std::shared_ptr<Transform2DComponent> transform;
		for (auto& entity : entities) {
			sprite = ComponentManager::getComponent<SpriteComponent>(entity);
			transform = ComponentManager::getComponent<Transform2DComponent>(entity);
			if (sprite) {
				if (sprite->getStackLayer() == 0) {
					if (transform)
						position = transform->position();
					int layer = sprite->layer();
					if (!renderTextures[layer]) {
						renderTextures[layer] = std::make_shared<sf::RenderTexture>();
						renderTextures[layer]->create(GameData::window().getSize().x, GameData::window().getSize().y);
						renderTextures[layer]->clear(sf::Color::Transparent);
						keys.push_back(layer);
					}
					sprite->setSpritePosition(position.x, position.y);
					sprite->updateFrameTime();
					renderTextures[layer]->draw(*sprite->getActiveSprite());
				}
			}
		}
		std::sort(keys.begin(), keys.end());
		GameData::window().clear();
		for (auto& key : keys) {
			renderTextures[key]->display();
			sf::Sprite spr(renderTextures[key]->getTexture());
			GameData::window().draw(spr);
		}
		GameData::window().display();
	}

}