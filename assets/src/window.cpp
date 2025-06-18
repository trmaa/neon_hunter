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

    for (auto& callback: this->m_pipeline) {
        this->draw(callback());
    }

    this->display();
}
