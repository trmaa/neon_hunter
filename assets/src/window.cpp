#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "window.hpp"
#include "entities.hpp"

eng::Window::Window(glm::ivec2 res)
	: m_resolution(res) {

	this->create(sf::VideoMode::getDesktopMode(), "Neon Hunter", sf::Style::Fullscreen);
	this->setFramerateLimit(60);

	sf::View stretched_view(sf::FloatRect(0.f, 0.f, res.x, res.y));
	this->setView(stretched_view);

	for (auto* entity : g_entities) {
		this->m_pipeline.push_back([entity]() -> sf::Sprite {
			return entity->draw();
		});
		this->m_pipeline_yindex.push_back(entity->get_position().y);
	}
}

void eng::Window::update() {
    this->clear(sf::Color(100, 100, 100));
    
    std::vector<size_t> indices(m_pipeline.size());
    for (size_t i = 0; i < indices.size(); ++i) {
		this->m_pipeline_yindex[i] = g_entities[i]->get_position().y;
        indices[i] = i;
    }

    std::sort(indices.begin(), indices.end(), [this](size_t a, size_t b) {
        return this->m_pipeline_yindex[a] < this->m_pipeline_yindex[b];
    });

    for (auto index: indices) {
        this->draw(m_pipeline[index]());
    }

    this->display();
}
