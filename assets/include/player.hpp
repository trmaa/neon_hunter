#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "entity.hpp"

class Player: public eng::Entity {
private:
	enum PlayerState {
		IDLE,
		WALKING,
		ATTACKING,
	};
    PlayerState m_state;
	bool m_flipped;

	float m_acceleration;
	glm::vec3 m_velocity;
	float m_max_velocity;

public:
	bool get_flipped() { return this->m_flipped; }
    void set_flipped(bool flipped) { this->m_flipped = flipped; }

	glm::vec3 get_velocity() { return this->m_velocity; }

	std::string get_animation_path();
	const sf::Texture& get_texture() override;
	const sf::Texture& get_normalmap() override;

	Player(glm::vec3 pos);
	~Player() = default;

	void control();
};

#endif
