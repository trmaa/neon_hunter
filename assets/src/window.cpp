#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "window.hpp"
#include "entities.hpp"

eng::Window::Window(glm::ivec2 res)
	: m_resolution(res) {
	this->create(sf::VideoMode(res.x, res.y), "Neon Hunter", sf::Style::Default);

	/************
	 * PIPELINE *
	 ************/
	this->m_pipeline.push_back([]() -> sf::Sprite {
		return player.draw();
	});
}

void eng::Window::update() {
	this->clear(sf::Color::Black);
	
	std::vector<sf::Sprite> sorted_sprites;
	for (auto& callback: this->m_pipeline) {
		sorted_sprites.push_back(callback());
	}

	std::sort(sorted_sprites.begin(), sorted_sprites.end(), [](const sf::Sprite& a, const sf::Sprite& b) {
		return a.getPosition().y < b.getPosition().y;
	});

	for (auto& sprite: sorted_sprites) {
		this->draw(sprite);
	}

	this->display();
}
