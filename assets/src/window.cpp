#include <cstdio>
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "window.hpp"
#include "vectors.hpp"
#include "entities.hpp"

eng::Window::Window(glm::ivec2 res)
	: m_resolution(res) {

	this->create(sf::VideoMode::getDesktopMode(), "Neon Hunter", sf::Style::Fullscreen);
	this->setFramerateLimit(60);

	sf::View stretched_view(sf::FloatRect(0.f, 0.f, res.x, res.y));
	this->setView(stretched_view);
	
	this->reload_pipeline();
}

void eng::Window::reload_pipeline() {
	this->m_pipeline.clear();
	for (auto* entity : g_entities) {
		this->m_pipeline.push_back([entity]() -> sf::Sprite {
			return entity->draw();
		});
		this->m_pipeline_yindex.push_back(entity->get_position().y);
	}
}

void eng::Window::update() {
    this->clear(sf::Color(0,0,0));
    
    std::vector<size_t> indices(m_pipeline.size());
    for (size_t i = 0; i < indices.size(); ++i) {
		this->m_pipeline_yindex[i] = g_entities[i]->get_position().y;
        indices[i] = i;
    }

    std::sort(indices.begin(), indices.end(), [this](size_t a, size_t b) {
        bool ay_by = this->m_pipeline_yindex[a] < this->m_pipeline_yindex[b];
		bool eqy = this->m_pipeline_yindex[a] == this->m_pipeline_yindex[b];

		bool az_bz = g_entities[a]->get_position().z < g_entities[b]->get_position().z;

		return (eqy && az_bz) || ay_by;
    });

    for (auto index: indices) {
		sf::Sprite sprite = m_pipeline[index]();

		/*sf::Sprite shadow = sprite;
		shadow.setColor(sf::Color(0, 10, 20, 120));
		shadow.setPosition(
			sprite.getPosition().x,
			//this puts a shadow on Z = 0 from the object at Z E R, where its sprites Y is their Y - Z
			sprite.getPosition().y + g_entities[index]->get_position().z
		);

		this->draw(shadow);*/

		glm::vec2 player_screen_pos = (glm::vec2)this->get_resolution()/2.f + glm::vec2(-8);
		float distance_to_player = glm::length(player_screen_pos - eng::stg(sprite.getPosition()));

		bool cond_1 = distance_to_player < 10.f;
        bool cond_2 = index != 0;
        bool cond_3a = sprite.getPosition().y > player_screen_pos.y+2;
		bool cond_3b = g_entities[index]->get_position().z > g_player.get_position().z;
		bool bond_3 = cond_3a || cond_3b;
		bool cond = cond_1 && cond_2 && bond_3;

		if (cond) {
            sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, 100));
        }

		if (index == 0) {
			bool should_be_flipped = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
			bool key_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
			if (should_be_flipped || g_player.get_flipped()) {
				g_player.set_flipped(true);
				sprite.setScale(-1.f, 1.f);
				sprite.setOrigin(sprite.getLocalBounds().width, 0.f);
			}
			if (key_pressed) {
				g_player.set_flipped(false);
            }
		}

        this->draw(sprite);
    }

    this->display();
}
