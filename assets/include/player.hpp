#pragma one

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
	const sf::Texture& get_texture() override;

	Player(glm::vec2 pos);
	~Player() = default;

	void control();
};
