#include "player.hpp"

const sf::Texture& Player::get_texture() {
	std::string new_path = (m_state == WALKING)
		? "build/bin/sprites/player_walk.png"
		: "build/bin/sprites/player_idle.png";

	if (new_path != m_texture_path || m_texture.getSize().x == 0) {
		m_texture_path = new_path;
		m_texture.loadFromFile(m_texture_path);
	}

	return m_texture;
}

Player::Player(glm::vec2 pos)
	: eng::Entity(pos, "build/bin/sprites/player_idle.png", "build/bin/sprites/player_idle_normalmap.png") {
	this->m_speed = 0.01f;
}

void Player::control() {
	glm::vec2 position = this->m_position;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        position.x -= this->m_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        position.x += this->m_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        position.y -= this->m_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        position.y += this->m_speed;
    }

    this->m_state = PlayerState::IDLE;
	if (this->m_position != position) {
        this->m_state = PlayerState::WALKING;
    }

	this->m_position = position;
}
