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

		float cycle_pos = std::fmod(eng::ticks, period);
		int frame = static_cast<int>(cycle_pos / frame_duration);

		return "build/bin/sprites/player_idle" + std::to_string(frame) + ".png";
	}
	if (this->m_state == WALKING) {
		const int frames = 10;
        const float frame_duration = period / frames;

        float cycle_pos = std::fmod(eng::ticks, period);
        int frame = static_cast<int>(cycle_pos / frame_duration);

        return "build/bin/sprites/player_walk" + std::to_string(frame) + ".png";
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
	int number = std::stoi(path.substr(path.size() - 5, 1));
	std::string new_path = path.substr(0, path.size() - 5) + "_normalmap"+std::to_string(number)+".png";

    if (new_path != m_normalmap_path || m_normalmap.getSize().x == 0 || m_flipped) {
        m_normalmap_path = new_path;
        m_normalmap.loadFromFile(m_normalmap_path);
    }

	bool should_be_flipped = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	bool key_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	if (should_be_flipped || g_player.get_flipped()) {
		g_player.set_flipped(true);

		sf::Shader normal_inverter;
		normal_inverter.loadFromFile("build/shaders/normal_inversion.glsl", sf::Shader::Fragment);
		normal_inverter.setUniform("texture", m_normalmap);

		sf::RenderTexture render_texture;
		render_texture.create(m_normalmap.getSize().x, m_normalmap.getSize().y);

		sf::Sprite sprite;
		sprite.setTexture(m_normalmap);

		render_texture.clear(sf::Color::Transparent);
		render_texture.draw(sprite, &normal_inverter);
		render_texture.display();

        m_normalmap = render_texture.getTexture();
	}
	if (key_pressed) {
		g_player.set_flipped(false);
	}

    return m_normalmap;
}

Player::Player(glm::vec3 pos)
	: eng::Entity(pos, "player") {
	this->m_acceleration = 0.1f;
	this->m_max_velocity = 0.7f;
}

void Player::control() {
    glm::vec3 position = this->m_position;
    float fixed_acceleration = this->m_acceleration * eng::delta_time;
	float boost = 2.f;
    float max_vel = this->m_max_velocity;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		max_vel *= boost;	
	}

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        this->m_velocity.x -= fixed_acceleration;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        this->m_velocity.x += fixed_acceleration;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->m_velocity.y -= fixed_acceleration;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->m_velocity.y += fixed_acceleration;
    }

	this->m_velocity *= 0.901f;
	if (glm::length(this->m_velocity) > max_vel) {
        this->m_velocity = glm::normalize(this->m_velocity) * max_vel;
	}
	if (glm::length(this->m_velocity) < 0.01f) {
        this->m_velocity = glm::vec3(0, 0, 0);
	}

    position += this->m_velocity;

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
