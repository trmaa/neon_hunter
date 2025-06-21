#include <string>
#include "player.hpp"
#include "globals.hpp"
#include "entities.hpp"

std::string Player::get_animation_path() {
	float period = 6000.0f; 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		period /= 2.5f;
	}

	if (this->m_state == IDLE) {
		const int frames = 2;
		const float frame_duration = period / frames;

		float cycle_pos = fmod(g_ticks, period);
		int frame = static_cast<int>(cycle_pos / frame_duration);

		return "build/bin/sprites/player_idle" + std::to_string(frame) + ".png";
	}
	if (this->m_state == WALKING) {
		const int frames = 10;
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
	int number = std::stoi(path.substr(path.size() - 5, 1));
	std::string new_path = path.substr(0, path.size() - 5) + "_normalmap"+std::to_string(number)+".png";

    if (new_path != m_normalmap_path || m_normalmap.getSize().x == 0) {
        m_normalmap_path = new_path;
        m_normalmap.loadFromFile(m_normalmap_path);
    }

    return m_normalmap;
}

Player::Player(glm::vec3 pos)
	: eng::Entity(pos, "player") {
	this->m_speed = 0.02f;
}

void Player::control() {
    glm::vec3 position = this->m_position;
    float fixed_speed = this->m_speed * g_delta_time;
	float speed_boost = 2.5f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		fixed_speed *= speed_boost;	
	}

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
        
		bool cond_1 = distance_squared < min_distance * min_distance;
		bool cond_2 = distance.z < min_distance;
        if (cond_1 && cond_2) { 
            collided = true;
            break;
        }
    }

    this->m_state = PlayerState::IDLE;
    if (this->m_position != position) {
        this->m_state = PlayerState::WALKING;
    }

    if (!collided) {
        this->m_position = position;
    }
}
