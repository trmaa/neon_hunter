#pragma one

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <string>

class Player {
private:
	glm::vec2 m_position;

	sf::Texture m_texture;
	std::string m_texture_path = "build/bin/sprites/player_idle.png";

	sf::Texture m_normalmap;
    std::string m_normalmap_path = "build/bin/sprites/player_idle_normalmap.png";

	sf::RenderTexture m_canvas;

public:
	glm::vec2 get_position() { return this->m_position; }

	const sf::Texture& get_texture() {
		if (m_texture.getSize().x == 0)
			m_texture.loadFromFile(m_texture_path);
		return m_texture;
	}

	const sf::Texture& get_normalmap() {
		if (m_normalmap.getSize().x == 0)
			m_normalmap.loadFromFile(m_normalmap_path);
		return m_normalmap;
	}

	Player();
    ~Player() = default;

	sf::Sprite draw();
};
