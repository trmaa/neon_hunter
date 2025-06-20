#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "entity.hpp"

class Player: public eng::Entity {
private:
	enum PlayerState {
		IDLE,
		WALKING
	};

    PlayerState m_state;
	float m_speed;

public:
	std::string get_animation_path();
	const sf::Texture& get_texture() override;
	const sf::Texture& get_normalmap() override;

	Player(glm::vec2 pos);
	~Player() = default;

	void control();
};

#endif
