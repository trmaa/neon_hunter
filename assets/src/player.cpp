#include <string>
#include "player.hpp"
#include "globals.hpp"
#include "entities.hpp"

std::string Player::get_animation_path() {
	if (this->m_state == IDLE) {
		const int frames = 2;
		const float period = 6000.0f; 
		const float frame_duration = period / frames;

		float cycle_pos = fmod(g_ticks, period);
		int frame = static_cast<int>(cycle_pos / frame_duration);

		return "build/bin/sprites/player_idle" + std::to_string(frame) + ".png";
	}
	if (this->m_state == WALKING) {
		const int frames = 12;
        const float period = 6000.0f; 
        const float frame_duration = period / frames;

        float cycle_pos = fmod(g_ticks, period);
        int frame = static_cast<int>(cycle_pos / frame_duration);

        return "build/bin/sprites/player_walk" + std::to_string(frame) + ".png";
    }
	return "!!!!!!!!!non player state";
}

const sf::Texture& Player::get_texture() {
	std::string new_path = this->get_animation_path(); 

	if (new_path != m_texture_path || m_texture.getSize().x == 0) {
		m_texture_path = new_path;
	}
	m_texture.loadFromFile(m_texture_path);

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

Player::Player(glm::vec3 pos)
	: eng::Entity(pos, "player") {
	this->m_speed = 0.05f;
}

void Player::control() {
    glm::vec3 position = this->m_position;
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

    const float player_radius = 4.0f;
    bool collided = false;
    
    for (auto entity : g_entities) {
        if (entity == this) {
            continue;
        }

        const float entity_radius = 4.0f; 
        const float min_distance = player_radius + entity_radius;
        
        glm::vec3 distance = entity->get_position() - position;
        float distance_squared = distance.x * distance.x + distance.y * distance.y;
        
        if (distance_squared < min_distance * min_distance) {
            collided = true;
            break;
        }
    }

    if (!collided) {
        this->m_position = position;
    }

    this->m_state = PlayerState::IDLE;
    if (this->m_position != position) {
        this->m_state = PlayerState::WALKING;
    }
}
