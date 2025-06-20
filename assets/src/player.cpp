#include "player.hpp"
#include "globals.hpp"

std::string Player::get_animation_path() {
	if (this->m_state == IDLE) {
        return "build/bin/sprites/player_idle.png";	
	}
	if (this->m_state == WALKING) {
        return "build/bin/sprites/player_walk.png";
    }
	return "!!!!!!!!!non player state";
}

const sf::Texture& Player::get_texture() {
	std::string new_path = this->get_animation_path(); 

	if (new_path != m_texture_path || m_texture.getSize().x == 0) {
		m_texture_path = new_path;
		m_texture.loadFromFile(m_texture_path);
	}

	return m_texture;
}

const sf::Texture& Player::get_normalmap() {
	std::string path = this->get_animation_path();
	std::string new_path = path.substr(0, path.size() - 4) + "_normalmap.png";

    if (new_path != m_normalmap_path || m_normalmap.getSize().x == 0) {
        m_normalmap_path = new_path;
        m_normalmap.loadFromFile(m_normalmap_path);
    }

    return m_normalmap;
}

Player::Player(glm::vec2 pos)
	: eng::Entity(pos, "player") {
	this->m_speed = 50.f;
}

void Player::control() {
	glm::vec2 position = this->m_position;

	float fixed_speed = this->m_speed * g_delta_time;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        position.x -= fixed_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        position.x += fixed_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        position.y -= fixed_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        position.y += fixed_speed;
    }

    this->m_state = PlayerState::IDLE;
	if (this->m_position != position) {
        this->m_state = PlayerState::WALKING;
    }

	this->m_position = position;
}
