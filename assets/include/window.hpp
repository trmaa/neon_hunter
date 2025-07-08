#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

namespace eng 
{

class Window: public sf::RenderWindow {
private:
	glm::ivec2 m_resolution;
	std::vector<std::function<sf::Sprite()>> m_pipeline;
	std::vector<float> m_pipeline_yindex;

public:
	glm::ivec2 get_resolution() { return this->m_resolution; }

	Window(glm::ivec2 res);
	~Window() = default;

	void update();

	void reload_pipeline();
};

};

#endif
